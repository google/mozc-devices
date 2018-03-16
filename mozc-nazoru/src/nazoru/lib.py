# -*- coding: utf-8 -*-
#
# Copyright 2018 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""Nazoru input library.
This is a collection of methods to preprocess input stroke data before any
training starts.
"""

import time
import random
import cairocffi as cairo
import numpy as np
from PIL import Image
from io import BytesIO
from enum import Enum

SCOPE = 'Nazorunet'
INPUT_NODE_NAME = 'inputs'
OUTPUT_NODE_NAME = SCOPE + '/Predictions/Reshape_1'
KANAS = (u'あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほ'
         u'まみむめもやゆよらりるれろわゐんゑを'
         u'abcdefghijklmnopqrstuvwxyz1234567890'
         u'♡ーずぐ')
KEYS = ('a', 'i', 'u', 'e', 'o',
        'ka', 'ki', 'ku', 'ke', 'ko',
        'sa', 'si', 'su', 'se', 'so',
        'ta', 'ti', 'tu', 'te', 'to',
        'na', 'ni', 'nu', 'ne', 'no',
        'ha', 'hi', 'hu', 'he', 'ho',
        'ma', 'mi', 'mu', 'me', 'mo',
        'ya',       'yu',       'yo',
        'ra', 'ri', 'ru', 're', 'ro',
        'wa', 'wi', 'nn', 'we', 'wo',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        'ha-to', '-', 'zu', 'gu')

class KeyboardArrangement(Enum):
  """Enum for keyboard arrangements.
  """
  qwerty_jis = [
      u'1234567890-^¥',
      u'qwertyuiop@[',
      u'asdfghjkl;:]',
      u'zxcvbnm,./_',
  ]


def key2pos(key, arrangement=KeyboardArrangement.qwerty_jis.value, offset=0.5):
  """Returns the key position.

  Args:
    key (string): Key to get position.
    arrangement (list): Keyboard arrangement.
    offset (number): How much the keys are shifting by row.

  Returns:
    position (tuple(number, number)): Position (x, y).

  """

  for i, row in enumerate(arrangement):
    if key in row:
      y = i
      x = row.index(key) + i * offset
      return (x, y)
  return None


def keydowns2points(keydowns):
  """Translates keydowns to points.

  Args:
    keydowns: [(key, t), ...] List of keydowns.

  Returns:
    points: [(x, y, t), ...] List of points.
  """

  points = []
  for keydown in keydowns:
    pos = key2pos(keydown[0])
    if pos:
      points.append((pos[0], pos[1], keydown[1]))
  return points


def normalize_x(x):
  """Normalizes position.

  Args:
    x (list): [[x, y, t], ...] List of points to normalize the position (x, y)
    into 0-1 range.

  Returns:
    x (list): [[x', y', t], ...] List of points with the normalized potision
    (x', y').
  """

  x = np.array(x)
  max_ = np.max(x[:, :2], axis=0)
  min_ = np.min(x[:, :2], axis=0)
  x[:, :2] = (x[:, :2] - min_) / (max_ - min_)
  return x


def pendown_encode(x_diff, sigma=1.6):
  """Encodes time difference into pendown state.

  Args:
    x_diff (list): [[dx, dy, dt], ...] List of diffs to encode.

  Returns:
    x_diff_encoded (list): [[dx, dy, dt, pendown], ...] Encoded list of diffs.
  """

  thres = np.mean(x_diff[:,2]) + sigma * np.std(x_diff[:,2])
  x_diff_encoded = np.concatenate((
    x_diff,
    [[0] if dt_i > thres else [1] for dt_i in x_diff[:, 2]]
    ), axis=1)
  return x_diff_encoded


def surface_to_array(surface):
  """Returns image array from cairo surface.

  Args:
    surface: Cairo surface to translate.
  """
  buf = BytesIO()
  surface.write_to_png(buf)
  png_string = buf.getvalue()
  im = Image.open(BytesIO(png_string))
  imdata = np.asarray(im.convert('L'))
  return imdata


def get_direction(diff):
  """Returns directions and weights for 8-directional features.

  For more detail, see

  - Bai, Zhen-Long, and Qiang Huo. "A study on the use of 8-directional features
    for online handwritten Chinese character recognition."
  - Liu, Cheng-Lin, and Xiang-Dong Zhou. "Online Japanese character recognition
    using trajectory-based normalization and direction feature extraction."

  Weight is halved for pen-up states.

  Args:
    diff (numpy.array): Encoded diff vector (dx, dy, dt, pendown).

  Returns:
    First direction (Right (0), Down, (2), Left (4), Up (6)) and its weight, and
    Second direction (Bottom right (1), Bottom left (3), Up left (5), Up right
    (7)) and its weight.

  """

  if np.abs(diff[0]) >= np.abs(diff[1]):
    if diff[0] >= 0:
      direction1 = 0
    else:
      direction1 = 4
  else:
    if diff[1] >= 0:
      direction1 = 2
    else:
      direction1 = 6

  if diff[0] >= 0:
    if diff [1] >= 0:
      direction2 = 1
    else:
      direction2 = 7
  else:
    if diff [1] >= 0:
      direction2 = 3
    else:
      direction2 = 5
  length = np.linalg.norm(diff[:2])
  if length == 0: return 0, 0, 1, 0
  weight1 = np.abs(np.abs(diff[0]) - np.abs(diff[1])) / length
  weight2 = np.sqrt(2) * min(np.abs(diff[0]), np.abs(diff[1])) / length
  if diff[3] == 0:
    weight1 /= 2
    weight2 /= 2
  return direction1, weight1, direction2, weight2


def generate_images(x_norm, x_diff_encoded, directional_feature,
    temporal_feature, scale, stroke_width):
  """Generates image array from strokes.

  Args:
    x_norm: [(x', y', t), ...] Normalized points.
    x_diff_encoded: [(dx, dy, dt, pendown), ...] Normalized diffs.
    directional_feature (boolean): True when using direcitonal feature.
    temporal_feature (boolean): True when using temporal feature.
    scale (int): Scale of the image.
    stroke_width (int): Brush thickness to draw.

  Returns:
    images (numpy.array): An array of images. Each image should have a shape of
      (scale, scale). Eight images will be added into the returned array if
      |directional_feature| is True, otherwise one original image will be
      added. Also, two images will be generated if |temporal_feature| is True.
      For example, the shape of |images| will be (scale, scale, 10) when both of
      options are True.
  """

  if directional_feature:
    images = generate_image_direct_decomp(
        x_norm, x_diff_encoded, scale, stroke_width)
  else:
    images = generate_image_plain(x_norm, x_diff_encoded, scale, stroke_width)
  if temporal_feature:
    image =  generate_image_temporal(
          x_norm, x_diff_encoded, scale, stroke_width, inversed=False)
    images = np.concatenate((images, image), axis=-1)
    image =  generate_image_temporal(
          x_norm, x_diff_encoded, scale, stroke_width, inversed=True)
    images = np.concatenate((images, image), axis=-1)

  return images


def generate_image_direct_decomp(x_norm, x_diff_encoded, scale, stroke_width):
  """Generates image array from strokes using direction feature.

  Args:
    x_norm: [(x', y', t), ...] Normalized points.
    x_diff_encoded: [(dx, dy, dt, pendown), ...] Normalized diffs.
    scale (int): scale of the image.
    stroke_width (int): Brush thickness to draw.

  Returns:
    image (numpy.array): Image array with a shape of (scale, scale, 8).
  """

  surfaces = [cairo.ImageSurface(cairo.FORMAT_A8, scale, scale)
      for _ in range(8)]

  curr_x = x_norm[0][0]
  curr_y = x_norm[0][1]

  for i, diff in enumerate(x_diff_encoded):
    direction1, weight1, direction2, weight2 = get_direction(diff)

    ctx = cairo.Context(surfaces[direction1])
    ctx.move_to(curr_x * scale, curr_y * scale)
    ctx.set_line_width(stroke_width)
    ctx.set_source_rgba(1, 1, 1, weight1)
    ctx.line_to((curr_x + diff[0]) * scale, (curr_y + diff[1]) * scale)
    ctx.stroke()

    ctx = cairo.Context(surfaces[direction2])
    ctx.move_to(curr_x * scale, curr_y * scale)
    ctx.set_line_width(stroke_width)
    ctx.set_source_rgba(1, 1, 1, weight2)
    ctx.line_to((curr_x + diff[0]) * scale, (curr_y + diff[1]) * scale)
    ctx.stroke()

    curr_x += diff[0]
    curr_y += diff[1]

  return np.array([
    surface_to_array(surface) for surface in surfaces]).transpose(1, 2, 0)


def generate_image_plain(x_norm, x_diff_encoded, scale, stroke_width):
  """Generates image array from strokes without direction feature.

  Args:
    x_norm: [(x', y', t), ...] Normalized points.
    x_diff_encoded: [(dx, dy, dt, pendown), ...] Normalized diffs.
    scale (int): scale of the image.
    stroke_width (int): Brush thickness to draw.

  Returns:
    image (numpy.array): Image array with a shape of (scale, scale, 1).
  """

  surface = cairo.ImageSurface(cairo.FORMAT_A8, scale, scale)

  curr_x = x_norm[0][0]
  curr_y = x_norm[0][1]

  for i, diff in enumerate(x_diff_encoded):
    ctx = cairo.Context(surface)
    ctx.move_to(curr_x * scale, curr_y * scale)
    ctx.set_line_width(stroke_width)
    if diff[3] == 1:
      ctx.set_source_rgba(1, 1, 1, 1)
    else:
      ctx.set_source_rgba(1, 1, 1, 0.5)
    ctx.line_to((curr_x + diff[0]) * scale, (curr_y + diff[1]) * scale)
    ctx.stroke()

    curr_x += diff[0]
    curr_y += diff[1]

  return surface_to_array(surface).reshape(scale, scale, 1)


def generate_image_temporal(x_norm, x_diff_encoded, scale, stroke_width,
    steepness=2, inversed=False):
  surface = cairo.ImageSurface(cairo.FORMAT_A8, scale, scale)

  curr_x = x_norm[0][0]
  curr_y = x_norm[0][1]
  spent_t = 0

  for i, diff in enumerate(x_diff_encoded):
      ctx = cairo.Context(surface)
      ctx.move_to(curr_x * scale, curr_y * scale)
      ctx.set_line_width(stroke_width)
      weight = 1 - spent_t / x_norm[-1][2]
      if inversed: weight = 1 - weight
      weight = max(weight, 0) ** steepness
      if diff[3] == 0: weight /= 2
      ctx.set_source_rgba(1, 1, 1, weight)
      ctx.line_to((curr_x + diff[0]) * scale, (curr_y + diff[1]) * scale)
      ctx.stroke()

      curr_x += diff[0]
      curr_y += diff[1]
      spent_t += diff[2]
  return surface_to_array(surface).reshape(scale, scale, 1)


def split_data(x, t, val_rate, test_rate):
  """Splits data into training, validation, and testing data.

  Args:
    x: Data to split.
    t: Label to split.
    val_rate: What percentage of data to use as a validation set.
    test_rate: What percentage of data to use as a testing set.

  Returns:
    train_x: Training inputs.
    train_t: Training labels.
    val_x: Validation inputs.
    val_t: Validation labels.
    test_x: Testing inputs.
    test_t: Testing labels.
  """

  n = x.shape[0]
  train_x = x[:int(n * (1 - val_rate - test_rate))]
  train_t = t[:int(n * (1 - val_rate - test_rate))]
  val_x= x[int(n * (1 - val_rate -  test_rate)):int(n * (1 - test_rate))]
  val_t = t[int(n * (1 - val_rate -  test_rate)):int(n * (1 - test_rate))]
  test_x = x[int(n * (1 - test_rate)):]
  test_t = t[int(n * (1 - test_rate)):]
  return train_x, train_t, val_x, val_t, test_x, test_t


def keydowns2image(keydowns, directional_feature, temporal_feature, scale=16,
    stroke_width=2):
  """Converts a list of keydowns into image.

  Args:
    keydowns: [(key, t), ...] Training data as a list of keydowns.
    directional_feature (boolean): True when using directional feature.
    temporal_feature (boolean): True when using temporal feature.
    scale (int): Scale of the image.
    stroke_width (int): Brush thickness to draw.

  Returns:
    X_im: Image dataset in numpy array format. The shape differs by used
    features.
    (directional=True, temporal=True)   => (scale, scale, 10)
    (directional=True, temporal=False)  => (scale, scale, 8)
    (directional=False, temporal=True)  => (scale, scale, 3)
    (directional=False, temporal=False) => (scale, scale, 1)
    """

  # Translate keys to 2D points. {(key, t), ...} -> {(x, y, t), ...}
  X = keydowns2points(keydowns)

  # 0-1 normalization
  X_norm = normalize_x(X)

  # Take difference. {(x, y, t), ...} -> {(dx, dy, dt), ...}.
  X_diff = np.diff(X_norm, axis=0)

  # Encode pendown state. {(dx, dy, dt), ...} -> {(dx, dy, dt, pendown), ...}
  X_diff_encoded = pendown_encode(X_diff)

  # Render into images.
  X_im = generate_images(X_norm, X_diff_encoded, directional_feature,
      temporal_feature, scale, stroke_width) / 255.

  return X_im
