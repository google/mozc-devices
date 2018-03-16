# -*- coding: utf-8 -*-

def get_default_graph_path():
  import os
  script_dir = os.path.dirname(os.path.abspath(__file__))
  return os.path.join(script_dir, 'data', 'optimized_nazoru.pb')
