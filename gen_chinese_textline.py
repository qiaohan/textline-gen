# -*- coding: utf-8 -*-

import os
from PIL import Image,ImageFont,ImageDraw
import random
import numpy as np

words = []
word2idx = {}
cnt=0
for line in open('word_dict.txt'):
    cnt+=1
    w = line.split()[1].decode('utf-8').strip()
    words.append(w)
    word2idx[w] = cnt

bgs = []
bgroot = "BGS/"
for f in os.listdir(bgroot): 
    im = Image.open(bgroot+f)
    bgs.append(np.asarray(im))
outdir = "../dataset_nocorpus_imgcolor/"
fonts_root = "chinese_fonts/"
#corpusfile = "/data1/hzqiaohan/yidun/gen_ad_img/corpus/yuliao_sel_final.txt"
corpusfile = "random_corpus.txt"
for fontname in os.listdir(fonts_root):
#for fontname in ["STXIHEI.TTF","MSYH.TTF"]:
	#print(fontname)
	iter = 0
	if fontname=="STXIHEI.TTF" or fontname=="STZHONGJ.TTF" or fontname=="MSYH.TTF" or fontname=="MSYHBD.TTC":
		fontsize = 25
	else: 
		fontsize = 25
	for line in open(corpusfile):
            if random.randint(0,20) !=3:
                continue
            iter += 1
            line = line.decode('utf-8').strip()
            #cr = random.randint(0,255)
            #cg = random.randint(0,255)
            #cb = random.randint(0,255)
            #im = Image.new("RGB", (26*len(line),32), (cr,cg,cb))
            im = bgs[random.randint(0,len(bgs))%len(bgs)]
            imgw = 26*len(line)
            if imgw > im.shape[1]:
                im = cv2.resize(im,(imgw,32))
            else:
                im = im[:32,:imgw,:]
            im = Image.fromarray(im) 
            label = " ".join([str(word2idx[w]) for w in line])
            #s = strs[0:textlen]
            '''
            for i in range(textlen):
                #ix = random.randint(0,12)
                ix = random.randint(0,len(strs)-1)
                textline += strs[ix]
                fname.append(str(ix))
                #s[i] = strs[ix]
            '''
            try:
	        dr = ImageDraw.Draw(im)
	        font = ImageFont.truetype(os.path.join(fonts_root, fontname), fontsize)
                cr = random.randint(0,255)
                cg = random.randint(0,255)
                cb = random.randint(0,255)
	        dr.text((1,1), line, font=font, fill=(cg,cb,cr) )#"#000000")
	        #dr.text((5,5), textline, font=font, fill="#000000")

	        #out_file = "textline_4char/%s.jpg"%('_'.join(fname))
                out_file = fontname+str(iter)+".jpg"
                print out_file,label
	        im.save(outdir+out_file)
                #break
            except Exception,e:
                continue
