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

vector<Mat> getBGimg(Size sz){
	vector<Mat> res;
	DIR *dp;
	struct dirent *dirp;
	string bgpath = "bg/";
	if ((dp = opendir("bg/")) == NULL){
		cout << "not found" << endl;
		return res;
	}
	while ((dirp = readdir(dp)) != NULL){
		if ((strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0))
			continue;
		Mat img = imread(bgpath+string(dirp->d_name));
		resize(img,img,sz);
		res.push_back(img);
	}
	return res;
}

vector<Mat> getPTmat(){
	vector<Mat> res;
	vector<Point2f> origin;
	vector<Point2f> ed;
	float kk = 0.2;
	origin.push_back(Point2f(1-kk,1-kk));
	origin.push_back(Point2f(1-kk,2+kk));
	origin.push_back(Point2f(2+kk,2+kk));
	origin.push_back(Point2f(2+kk,1-kk));
	for(int d1 = 0; d1<3; d1++)
	for(int d2 = 0; d2<3; d2++)
	for(int d3 = 0; d3<3; d3++){
		float dd1 = (d1-0.5)*0.005;
		float dd2 = (d2-0.5)*0.005;
		float dd3 = (d3-0.5)*0.005;
		ed.clear();
		ed.push_back(Point2f(1+dd1,1+dd1));
		ed.push_back(Point2f(1+dd2,2+dd2));
		ed.push_back(Point2f(2+dd3,2+dd3));
		ed.push_back(Point2f(2,1));
		Mat tt = getPerspectiveTransform(origin.data(),ed.data());
		res.push_back(tt);
	}
	return res;
}

Mat DrawBG(Mat bg_im,Mat char_im){
	Mat res;
	int bg_dim = bg_im.cols;
	int char_dim = char_im.cols;
	int margin = bg_dim-char_dim - 1;
	if(margin<0)
		return res;
	res = bg_im.clone();
	int start_x = rand()%margin;
	int start_y = rand()%margin;
	//cout<<char_im.type()<<','<<bg_im.type()<<endl;	
	for(int i=0; i<char_dim; i++)
		for(int j=0; j<char_dim; j++){
			/*
			if(char_im.data[(i*char_dim+j)*3]<150){
				res.data[(char_dim*(i+start_x)+j+start_y)*3] = char_im.data[(i*char_dim+j)*3];
				res.data[(char_dim*(i+start_x)+j+start_y)*3+1] = char_im.data[(i*char_dim+j)*3+1];
				res.data[(char_dim*(i+start_x)+j+start_y)*3+2] = char_im.data[(i*char_dim+j)*3+2];
			}*/
			if(char_im.at<uchar>(i,j*3)<150){
				res.at<uchar>(start_y+i,(start_x+j)*3) = char_im.at<uchar>(i,j*3);
				res.at<uchar>(start_y+i,(start_x+j)*3+1) = char_im.at<uchar>(i,j*3+1);
				res.at<uchar>(start_y+i,(start_x+j)*3+2) = char_im.at<uchar>(i,j*3+2);
			}
			else if(char_im.at<uchar>(i,j*3)<200){
				res.at<uchar>(start_y+i,(start_x+j)*3) = ( char_im.at<uchar>(i,j*3)+0 )/2;
				res.at<uchar>(start_y+i,(start_x+j)*3+1) = ( char_im.at<uchar>(i,j*3+1)+0 )/2;
				res.at<uchar>(start_y+i,(start_x+j)*3+2) = ( char_im.at<uchar>(i,j*3+2)+0 )/2;
			}
		}
	
	//char_im.copyTo(res(Rect(start_x,start_y,char_im.cols,char_im.rows)));	
}

Mat salt(Mat im,int n)
{
	Mat img = im.clone();
	for(int k=0;k<n;k++)
	{
		int i=rand()%img.cols ;
		int j=rand()%img.rows;
		if(img.channels()==1)
		{
			img.at<uchar>(j,i)=255;
		}else if(img.channels()==3){
			img.at<Vec3b>(j,i)[0]=50;
			img.at<Vec3b>(j,i)[1]=50;
		    img.at<Vec3b>(j,i)[2]=50;
		}
	}
	return img;
}

vector<Mat> process(Mat im_t, vector<Mat> PTmat, vector<Mat> bg){
	vector<Mat> res;

	Mat img = getCharRect(im_t,5);
	//Mat img = im_t(rt);
	for(int i=0; i<PTmat.size()+1; i++){
		for(int j=0; j<bg.size(); j++){
			Mat img_p;
			if(i!=PTmat.size())
				warpPerspective(img,img_p,PTmat[i],Size(img.cols,img.rows),INTER_LINEAR,BORDER_CONSTANT,Scalar(255,255,255));
			else
				img_p = img;
			img_p = getCharRect(img_p,0);
			resize(img_p,img_p,Size(56,56));
			int idx = j;//rand()%bg.size();
			Mat im_b = DrawBG(bg[idx],img_p);
			Mat im_b1,im_b2;
			GaussianBlur(im_b,im_b1,Size(11,11),11);
			GaussianBlur(im_b,im_b2,Size(5,5),5);
			res.push_back(im_b1);
			res.push_back(im_b2);
			Mat im_b3;
			GaussianBlur(im_b,im_b3,Size(15,15),15);
			res.push_back(im_b3);
		}
	}
	return res;	
	/*
	vector<Mat> finalres;
	for(int i=0; i<res.size(); i++){
		for(int j=0;j<3;j++)
		{
			Mat aaa = salt(res[i],5); 
			finalres.push_back(aaa);
		}
	}
	return finalres;
	*/
}

int main(int argc, char** argv){
	if(argc!=3){
		cout<<"usage: preprocess inputdir outputdir"<<endl;
		return 0;
	}
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(argv[1])) == NULL){
		cout << argv[1] << endl;
		cout << "not found" << endl;
		return 0;
	}
	vector<Mat>	PTmat = getPTmat();	
	vector<Mat> bg = getBGimg(Size(64,64));
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
			vector<Mat> imgs = process(im,PTmat,bg);
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
