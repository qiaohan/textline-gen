# -*- coding: utf-8 -*-

import os
from PIL import Image,ImageFont,ImageDraw
import numpy as np
from random import randint

import pygame

word2idx = {}
words=[]
idx = 0
for line in open('word_dict.txt', 'r'):
#for line in open('all_class_long.txt', 'r'):
    #str = f.read().decode("utf-8")
    idx += 1
    w = line.split()[1]
    w = w.decode("utf-8").strip()
    if len(w)!=1:
        print idx,w
    words.append(w)
    word2idx[w] = idx
#print words[4721]
#print [words[4733]]
#print [words[4734]]

def render_pil(k_c,fontname):
    fontsize = 40
    fontsize = int(0.55*fontsize) 
    im = Image.new("RGB", (48,48), (255,255,255))
    dr = ImageDraw.Draw(im)
    font = ImageFont.truetype(os.path.join(fonts_root, fontname), fontsize + randint(3,10))

    dr.text((5,5), k_c, font=font, fill="#000000")
    out_file = "font_chars_3850/"+str(word2idx[k_c])+"_%s.jpg"%(fontname[:-4])
    im.save(out_file)


fonts_root = "chinese_fonts/"
for fontname in os.listdir(fonts_root):
    print(fontname)
    for k_c in words:
        render_pil(k_c,fontname) 
