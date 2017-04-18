/*************************************************************************
    > File Name: preprocess.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Thu 22 Dec 2016 09:38:03 AM CST
 ************************************************************************/

#include <iostream>
#include <dirent.h>
#include <sstream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int cnt = 0;

Mat getCharRect(Mat img,int pad){
	Mat binaryimg;
	int thre = 125;
	Mat img_g;
	cvtColor(img,img_g,CV_RGB2GRAY);
	//equalizeHist(img,img);
	//imwrite("tmp/g.jpg",img);
	threshold(img_g,binaryimg,thre,255,THRESH_BINARY_INV);
	//imwrite("bi/b.jpg",binaryimg);
	int thre_acc = 1;
	vector<int> verproj(binaryimg.rows);
	int top = -1;
	int bottom = -1;
	for(int j=0; j<verproj.size(); j++){
		verproj[j] = 0;
		for(int i=0; i<binaryimg.cols; i++){
			if(binaryimg.at<uchar>(j,i)>1)
				verproj[j]++;
		}
	}
	for(int j=1; j<verproj.size(); j++){
		if(verproj[j]>=thre_acc&&verproj[j-1]<thre_acc)
		{
			top = j;
			break;
		}
	}
	for(int j=verproj.size()-2; j>0; j--){
		if(verproj[j]>=thre_acc&&verproj[j+1]<thre_acc)
		{
			bottom = j;
			break;
		}
	}
	if(-1==top||-1==bottom){
		for(int i = 0; i<verproj.size(); i++)
			cout<<verproj[i]<<',';
		cout<<endl;
		if(-1==top)
			top=0;
		if(-1==bottom)
			bottom = verproj.size() -1;
	}
	
	vector<int> horproj(binaryimg.cols);
	int left = -1;
	int right = -1;
	for(int j=0; j<horproj.size(); j++){
		horproj[j] = 0;
		for(int i=0; i<binaryimg.rows; i++){
			if(binaryimg.at<uchar>(i,j)>1)
				horproj[j]++;
		}
	}
	for(int j=1; j<horproj.size(); j++){
		if(horproj[j]>=thre_acc&&horproj[j-1]<thre_acc)
		{
			left = j;
			break;
		}
	}
	for(int j=horproj.size()-2; j>0; j--){
		if(horproj[j]>=thre_acc&&horproj[j+1]<thre_acc)
		{
			right = j;
			break;
		}
	}
	if(-1==left||-1==right){
		for(int i = 0; i<horproj.size(); i++)
			cout<<horproj[i]<<',';
		cout<<endl;
		if(-1==left)
			left = 0;
		if(-1==right)
			right = horproj.size()-1;
	}
	int len;
	if(right-left>bottom-top){
		len = right-left;
		top -= ( (right-left) - (bottom-top) )/2;
		top = top>0?top:0;
	}
	else{
		len = bottom-top;
		left -= ( (bottom-top) - (right-left) )/2;
		left = left>0?left:0;
	}
	int l = left,r = left+len, t = top, b = top+len;
	//int pad = 5;
	l = l-pad<0?0:l-pad;
	t = t-pad<0?0:t-pad;
	r = r+pad>=img.cols?img.cols-1:r+pad;
	b = b+pad>=img.rows?img.rows-1:b+pad;
	return img( Rect(l,t,r-l,b-t) );

	//return img(rt);
}

vector<pair<int,int> > getPartial(Mat im){

}

vector<Mat> process(Mat im_t, vector<Mat> PTmat, vector<Mat> bg){
	vector<Mat> res;

	Mat img = getCharRect(im_t,0);
	vector<pair<int,int> > partial_w = getPartial(img);
	if(partial_w.size()>1){

	}
	return res;	
}

int main(int argc, char** argv){
	if(argc!=3){
		cout<<"usage: genpartial inputdir outputdir"<<endl;
		return 0;
	}
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(argv[1])) == NULL){
		cout << argv[1] << endl;
		cout << "not found" << endl;
		return 0;
	}
	while ((dirp = readdir(dp)) != NULL){
		if ((strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0))
			continue;
		string inpath(argv[1]);
		string outpath(argv[2]);
		string fname(dirp->d_name);
		cout<<inpath+fname<<endl;
		Mat im = imread(inpath+fname);
		fname = fname.substr(0,fname.size()-4);
		cout<<fname<<endl;
		//im = im(Rect(0,5,40,40));
		//resize(im,im,Size(64,64));
		if(im.empty())
			return 0;
		try{
			vector<Mat> imgs = process(im);
			for(int i=0; i<imgs.size(); i++){
				stringstream ss;
				ss<<i;
				string numstr=ss.str();
				imwrite(outpath+fname+numstr+".png",imgs[i]);
			}
		}
		catch(Exception e){

		}
	}
}
