# -*- coding: utf-8 -*-

import os
from PIL import Image,ImageFont,ImageDraw
import random

with open('CH3754.txt', 'r') as f:
	strs = f.read().decode("utf-8")

fonts_root = "chinese_fonts/"
for fontname in os.listdir(fonts_root):
	#print(fontname)
	iter = 1
	if fontname=="STXIHEI.TTF" or fontname=="STZHONGJ.TTF" or fontname=="MSYH.TTF" or fontname=="MSYHBD.TTC":
		fontsize = 40
	else: 
		fontsize = 45
	for _ in range(1000):
            textlen = random.randint(3,15)
            textline = ''
            fname = []
            im = Image.new("RGB", (60*textlen,60), (255,255,255))
            #s = strs[0:textlen]
            dr = ImageDraw.Draw(im)
	    font = ImageFont.truetype(os.path.join(fonts_root, fontname), fontsize)
	    segpt = [5]
            for i in range(textlen):
                ss = random.randint(5,20)
                ix = random.randint(0,len(strs)-1)
                textsize = dr.textsize(strs[ix],font)
                #print textsize
                segpt.append(segpt[-1]+textsize[0])
                segpt.append(segpt[-1]+ss)
                #textline += strs[ix]
                fname.append(str(ix))
                #s[i] = strs[ix]
                spt = (segpt[-3],5)
	        dr.text(spt, strs[ix], font=font, fill="#000000")

	    out_file = "/data1/hzqiaohan/textline_words/gen1/%s.jpg"%('_'.join(fname))
	    #out_file = "test/%s.png"%('_'.join(fname))
            s = [str(k) for k in segpt[:-1]]
            print out_file,' '.join(s)
	    im.save(out_file)

	    iter += 1
