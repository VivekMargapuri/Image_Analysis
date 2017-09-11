//displays.h
#ifndef displays_H
#define displays_H

#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

class Displays {

       	

public:	

	void display_img(const Mat &image, string const &win_name);
	void display_pix(const Mat &image, string const &win_name,Point pt);
};

#endif
