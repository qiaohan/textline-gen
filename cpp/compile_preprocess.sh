#########################################################################
# File Name: compile_preprocess.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Thu 22 Dec 2016 09:59:38 AM CST
#########################################################################
#!/bin/bash
g++ preprocess.cpp -o preprocess `pkg-config opencv --libs --cflags` && g++ genblank.cpp -o genblank `pkg-config opencv --libs --cflags`
