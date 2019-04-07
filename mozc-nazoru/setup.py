#!/usr/bin/env python
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

import codecs
import os
from setuptools import setup, find_packages

def read_file(name):
  with codecs.open(
      os.path.join(os.path.dirname(__file__), name), 'r', 'utf-8') as f:
    return f.read().strip()

setup(
    name='nazoru-input',
    version='0.1.2',
    author='Makoto Shimazu',
    author_email='shimazu@google.com',
    url='https://landing.google.com/tegaki',
    description='Package for Gboard Physical Handwriting Version',
    long_description=read_file('README.rst'),
    license='Apache',
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Environment :: Console',
        'Environment :: No Input/Output (Daemon)',
        'Operating System :: OS Independent',
        'Programming Language :: Python',
        'License :: OSI Approved :: Apache Software License',
        'Topic :: Scientific/Engineering :: Artificial Intelligence',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Topic :: Utilities',
    ],
    packages=find_packages('src'),
    package_dir={'': 'src'},
    package_data={
        'nazoru': ['data/optimized_nazoru.pb']
    },
    scripts=[
        'bin/nazoru-input',
        'bin/nazoru-training'
    ],

    # For installing the nazoru_input as a service of systemd. Please uncomment
    # the following |data_files| if you want to install nazoru.service.
    # data_files=[('/etc/systemd/system', ['data/nazoru.service'])],

    install_requires=[
        'np_utils',
        'cairocffi',
        'numpy',
        'h5py',
        'pillow',
        'tensorflow',
        'enum34;python_version<"3.4"',
        'pyserial',
        'evdev;platform_system=="Linux"',
        'wiringpi;platform_system=="Linux"'
    ]
  )
