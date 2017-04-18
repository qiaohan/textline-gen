# -*- coding: utf-8 -*-
import codecs
import os

fout = codecs.open("gt_random.lst","w","utf-8")

corpusfile = "random_corpus.txt"#"/data1/hzqiaohan/yidun/gen_ad_img/corpus/yuliao_sel_final.txt"
#for fontname in os.listdir(fonts_root):
for fontname in ["STXIHEI.TTF","MSYH.TTF"]:
	iter = 0
	for line in open(corpusfile):
	    iter += 1
            line = line.decode('utf-8').strip()
            try:
	        #out_file = "textline_4char/%s.jpg"%('_'.join(fname))
                out_file = fontname.split('.')[0]+str(iter)+".jpg"
                print out_file+" "+line
                fout.write(out_file+" "+line+'\n')
            except Exception,e:
                continue
fout.close()
