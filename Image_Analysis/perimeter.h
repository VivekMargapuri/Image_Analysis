//perimeter.h
#ifndef perimeter_H
#define perimeter_H

#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

class Perimeter {

       int thickness;
       Vec3b b_color;	

public:	

	Mat perimeter(Mat mat);
	Mat smooth(Mat mat);
};

#endif
