#!/usr/bin/env python

# --------------------------------------------------------
# Faster R-CNN
# Copyright (c) 2015 Microsoft
# Licensed under The MIT License [see LICENSE for details]
# Written by Ross Girshick
# --------------------------------------------------------

"""
Demo script showing detections in sample images.

See README.md for installation instructions before running.
"""

import matplotlib.pyplot as plt
import cv2
from parser import *
import Image

def vis_symbols(im, symbols_data):

    im = im[:, :, (2, 1, 0)]
    fig, ax = plt.subplots(figsize=(12, 12))
    ax.imshow(im, aspect='equal')

    for symbol_item in symbols_data:
        bbox=[]
        bbox.append(symbol_item[0])
        bbox.append(symbol_item[1])
        bbox.append(symbol_item[2])
        bbox.append(symbol_item[3])

        ax.add_patch(
            plt.Rectangle((bbox[0], bbox[1]),
                          bbox[2],
                          bbox[3], fill=False,
                          edgecolor='red', linewidth=3.5)
            )

    plt.axis('off')
    plt.tight_layout()
    plt.draw()

    plt.savefig('./_res.jpg')
    

def demo(image_name, symbols_data):
    # Load the demo image
    im = cv2.imread(image_name)

    # Visualize symbols in formula
    vis_symbols(im, symbols_data)


if __name__ == '__main__':

    parser = Parser()

    symbols_render_str=parser.parse('\int^{a}_{-a}a+b=0')

    '''load data as a list'''
    symbol_infos = symbols_render_str.split(';')
    bboxes_ = []
    for i, symbol_info in enumerate(symbol_infos):


        symbol_info_ = symbol_info.split(',')

        try:
            bbox=symbol_info_[1]
            left, top, width, height, Box_width, Box_height = bbox.split(' ')
        except:
            continue;

        bbox_ = [int(left), int(top),int(width), int(height),int(Box_width), int(Box_height)]
        bboxes_.append(bbox_)

    im_name = './blank.jpg'

    demo(im_name, bboxes_)

    plt.show()
