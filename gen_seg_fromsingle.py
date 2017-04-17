# -*- coding: utf-8 -*-

import os
from PIL import Image,ImageFont,ImageDraw
import random
import numpy as np
import cv2

labels = {}
singlefname = [f for f in os.listdir("single")]
for f in singlefname:
    s = f.split('.')[0]
    s = s.split('_')[0]
    labels[f] = s
iter = 1
for _ in range(20000):
            textlen = 4#random.randint(3,15)
            #textline = ''
            fname = []
            #im = Image.new("RGB", (60*textlen,60), (255,255,255))
            #s = strs[0:textlen]
            im = np.ones([60,100*textlen])*255
            segpt = [0]
            for i in range(textlen):
                #ix = random.randint(0,12)
                ix = random.randint(0,len(singlefname)-1)
                imchar = cv2.imread('single/'+singlefname[ix],cv2.IMREAD_GRAYSCALE)
                h,w = imchar.shape
                if w>80:
                    continue
                #print i,singlefname[ix]
                im[:,segpt[-1]:w+segpt[-1]] = imchar
                segpt.append(w+segpt[-1])
                segpt.append(segpt[-1]+random.randint(1,10))
                #segpt.append(segpt[-1])
                #textline += strs[ix]
                fname.append(labels[singlefname[ix]])
                #s[i] = strs[ix]

	    out_file = "textlineseg_eval/%s.png"%('_'.join(fname))
            s = [str(k) for k in segpt[:-1]]
            print out_file,' '.join(s)
            cv2.imwrite(out_file,im[:,:segpt[-1]])

	    iter += 1
