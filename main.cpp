#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
 
int main(int argc, char** argv )

{    
    Mat image;
    Mat grey;
   	Mat hsv;
	Mat blur;
	Mat imagecanny;
	Mat dila;
	Mat kernel;
	Mat mask;
	
    image = imread("Input path of image: C:/Users/Name of user/directory/name of image.jpg ", IMREAD_COLOR);
	
	resize(image,image,Size(512 ,512));
    cvtColor(image, grey, COLOR_BGR2GRAY);
	GaussianBlur( image, blur, Size( 9, 9 ), 1.0);
	cvtColor(image, hsv, COLOR_BGR2HSV);

	Canny(blur, imagecanny, 50,  75 ); // change up the number to see what is the best fit in outline wise
	kernel = getStructuringElement(MORPH_RECT, Size(5,2)); // also can change up number
	dilate(imagecanny, dila, kernel );

    threshold(grey, dila, 0, 255, THRESH_BINARY | THRESH_OTSU);
 
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

    findContours(imagecanny, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); 
	drawContours(image, contours, -5, Scalar(255,255, 0), 2);

	int h =contours.size();


    cout<<"***************************************"<< endl; 


    if( contours.size() <= 11)
    {
        cout<<"It is a Sunny Day/Clear Night. "<< endl;        
    }
        if (12 <= contours.size() && contours.size() < 160 )
        {
            cout<<"It is a Mostly Sunny Day/ Mostly Fair Night. "<< endl; 
        }
            if (161 < contours.size() && contours.size() < 400 )
        {
            cout<<"It is a Partly Sunny/ Partly Cloudy Night. "<< endl; 
        }
            if (401 < contours.size() && contours.size() < 1000  )
        {
            cout<<"It is a Mostly Cloudy Day/Night. "<< endl; 
        }

    cout<<"***************************************"<< endl; 
    
    
    //cout<<"\n The number of contours are: "<<h<<"\n\n";  if u would like to see the number of contours there are in the image
    
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
	
    //if would like to see certain filters and contours applied to the image. Uncomment the lines below.
    imshow("Display Image", image);
    //imshow("Grayscale Image", grey);
	//imshow("HSV Image", hsv);
	//imshow("GaussianBlur", blur);
	//imshow("Canny", imagecanny);
	//imshow("dilate", dila);

    waitKey(0);

    return(0);
    
 } 

 