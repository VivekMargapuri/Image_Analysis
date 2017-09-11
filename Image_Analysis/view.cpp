#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <queue>
#include <bits/stdc++.h>
#include <sstream>
#include <iostream>
#include <string>
#include "ffill.h"
#include "perimeter.h"
#include "displays.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    	
	if (argc != 7) {
        	printf("usage: Opencv_Test <Image_Path> <X> <Y> <Region_Path> <Perimeter_Path> <Smooth_perimeter_path>\n");
        	return -1;
        }  
    
   	Mat image,image1,image2;
	image = imread(argv[1], 1);

	if (!image.data) {
        	printf("No image data.\n");
        	return -1;
	}
	Ffill f;
	Perimeter p;
	Displays d;
	d.display_img(image, "Input");
	Point pts; 	
        String s1 = argv[2];
	String s2 = argv[3];
	std::stringstream ss1(s1);
      	int a = 0;
      	ss1 >> a;				
      	
      	std::stringstream ss2(s2);
      	int b = 0;
      	ss2 >> b;
	pts.x = a;	
	pts.y = b;
	Mat image3 = image;
	int x;
	cout<<"Press 1 to find region: ";
	cin>>x;
	if(x==1) {     
		image = f.ffutil(image,pts);		
    		image = (image);
		d.display_img(image,"Region");
		imwrite(argv[4],image);
		int y;
		cout<<"Press 2 to find perimeter: ";
		cin>>y;
		if(y==2){
			image2 = p.perimeter(image);
			image2 = (image2);
			d.display_img(image2,"Perimeter");
			imwrite(argv[5], image2);
			
			
			int z;
			cout<<"Press 3 to view smooth image: ";
			cin>>z;
			if(z == 3) {
				image3 = f.ffutil(image3,pts);
				image3 = (image3);
				Mat image4 = p.smooth(image3);
				image4 = (image4);
				d.display_img(image4,"Smooth_Perimeter");
				imwrite(argv[6], image4);
				return 0;
			
			}
			else {
				cout<<"Invalid entry";
				return -1;
			}
		}
		else {
			cout<<"Invalid entry";
			return -1;
	
		}
	}
	else {
		cout<<"Invalid entry";
		return -1;

	}					
	
    	return 0;
}

//Flood fill function 
Mat Ffill::ffutil(Mat mat,Point pt) {
	
	int channels = mat.channels();
	int mrows = mat.rows;
	int mcols = mat.cols;
	Mat mat2(mrows,mcols,CV_8UC3, Scalar(0,0,0));
	
	Vec3b color;
	color[0] = 0;
	color[1] = 0;
	color[2] = 255;
	
	
	if(pt.x < 0 || pt.x > mrows || pt.y < 0 || pt.y > mcols) {
		
		std::cout<<"Error";
		return mat2;
	}	

	Vec3b pc = mat.at<Vec3b>(pt);	

	if(mat.at<Vec3b>(pt) == pc) {
		queue<Point> pq;
		pq.push(pt);
		while(!pq.empty()) {
		
			Point temp;
			temp = pq.front();	
			pq.pop();
			if((temp.x >= 0) && (temp.x < mat.size().width) && (temp.y >= 0) && (temp.y < mat.size().height)) {
				Vec3b t = mat.at<Vec3b>(temp);
				if(t[0] > pc[0]-70 && t[0]<=pc[0]+70 && t[1]> pc[1]-70 && t[1]<pc[1]+70 && t[2] > pc[2] -70 && t[2] < pc[2]+70)                            {       
					if(t == color) {
						color[0]++;
					}
					mat.at<Vec3b>(temp) = color;
					mat2.at<Vec3b>(temp) = mat.at<Vec3b>(temp);
					pq.push(Point(temp.x+1,temp.y));
					pq.push(Point(temp.x-1,temp.y));
					pq.push(Point(temp.x,temp.y+1));
					pq.push(Point(temp.x,temp.y-1));
				}
			}
		}
	}
	
	return mat2;
}

//Perimeter function

Mat Perimeter:: perimeter(Mat mat) {
	
    int channels = mat.channels();
    int nRows = mat.rows;
    int nCols = mat.cols;
    //border will be drawn with green
    Vec3b color; 
    color[0] = 0;
    color[1] = 255;
    color[2] = 0;			
    for (int i = 0; i < nRows; ++i) {
     
                for (int j = 0; j < nCols; ++j) {

                   Vec3b m = mat.at<Vec3b>(i,j);
		   //black pixels that are around any red pixels will be colored green
		   if(m[2]==0) {

		   	Vec3b m1,m2,m3,m4;
	                m1 = mat.at<Vec3b>(i+1,j);
			m2 = mat.at<Vec3b>(i-1,j);
			m3 = mat.at<Vec3b>(i,j+1);
			m4 = mat.at<Vec3b>(i,j-1);

			if(m1[2]==255||m2[2]==255||m3[2]==255||m4[2]==255) {

				mat.at<Vec3b>(i,j) = color;
				
			}
		    }
		}	
   
    }

   return mat;
	
}

//Function to create a smooth perimeter


Mat Perimeter:: smooth(Mat mat) {
    	
    int channels = mat.channels();
    int nRows = mat.rows;
    int nCols = mat.cols;
    Vec3b color;
    color[0] = 0;
    color[1] = 255;
    color[2] = 0;
    Vec3b black;
    black[0] = 0;
    black[1] = 0;
    black[2] = 0;

    //Initially smoothen the image output from floodfill function
    //Box smoothening is done such that any red pixel that is isolated or do not have many red pixels around are colored black
    for (int i = 0; i < nRows; ++i) {
               
                for (int j = 0; j < nCols; ++j) {
			Vec3b t = mat.at<Vec3b>(i,j);

			if(t[2] == 255) {
				int flag = 0;
  				for(int k = 1; k <= 2; k++){
					
					Vec3b t1,t2,t3,t4;
 					t1 = mat.at<Vec3b>(i+k,j);
					t2 = mat.at<Vec3b>(i-k,j);
					t3 = mat.at<Vec3b>(i,j+k);
					t4 = mat.at<Vec3b>(i,j-k);
					if(t1[2]== 0 ) {
					
						flag++;
					}
					if(t2[2]== 0 ) {
					
						flag++;
					}
					if(t3[2]== 0 ) {
					
						flag++;
					}
					if(t4[2]== 0 ) {
					
						flag++;
					}
					
				}
				if(flag > 5) {
					mat.at<Vec3b>(i,j) = black;
				}

			}
    		}
    }

    //draw border around the remianing red pixels			 
						
    for (int i = 0; i < nRows; ++i) {
             
                for (int j = 0; j < nCols; ++j) {
                	Vec3b m = mat.at<Vec3b>(i,j);
		   	
		   		if(m[2]==0 && m[1] == 0) {
		   			Vec3b m1,m2,m3,m4;
	                		m1 = mat.at<Vec3b>(i+1,j);
					m2 = mat.at<Vec3b>(i-1,j);
					m3 = mat.at<Vec3b>(i,j+1);
					m4 = mat.at<Vec3b>(i,j-1);

					if(m1[2]==255||m2[2]==255||m3[2]==255||m4[2]==255) {
						
							mat.at<Vec3b>(i,j) = color;
							mat.at<Vec3b>(i-1,j-1) = color;
									
					}
		    		}
		   	

		}	
   
    }

   return mat;
	
}

//Display RGB image function
void Displays :: display_img(const Mat &image, string const &win_name) {
    namedWindow(win_name, WINDOW_AUTOSIZE);
    imshow(win_name, image);
    waitKey(0);
}


//Display pixel function (curently not being unused, but its fully functional)
void Displays :: display_pix(const Mat &image, string const &win_name,Point pt) {

    Ffill f;
    Perimeter p;
    Mat image1;
	
    image1 = f.ffutil(image,pt);
    namedWindow(win_name, WINDOW_AUTOSIZE);
    image1 = (image1);
    imshow(win_name, image1);
    imwrite(win_name,image1);
    Mat image2 = p.perimeter(image1);
    image2 = (image2);	
    namedWindow(win_name + "_Perimeter", WINDOW_AUTOSIZE);
    imshow(win_name + "_Perimeter", image2);	
    imwrite(win_name+ "_Perimeter", image2); 	 		
    waitKey(0);
}
