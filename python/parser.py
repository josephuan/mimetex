# -*- coding: utf-8 -*-
import ctypes
import os
import sys
import numpy as np
cur_path = os.path.abspath(os.path.dirname(__file__))

libfile = os.path.join(cur_path, "../lib_mimetex.so")
sys.path.append(os.path.join(cur_path))



class Parser(object):
    '''the entry of mimetex'''

    def __init__(self):
        self.lib = ctypes.cdll.LoadLibrary(libfile)
        self.lib.CreateGifFromEq.restype = ctypes.c_char_p

    # by huanwang
    def parse(self, data):
        '''call the mimetex'''
        return self.lib.CreateGifFromEq(data, './mimetex_render_img.gif');


if __name__ == '__main__':
    parser = Parser()

    print parser.parse('a+b=c')

