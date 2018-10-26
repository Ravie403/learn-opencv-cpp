#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
/*
  BGR<=>HSVの変換を行う。

*/

int main(int argc, char** argv ){
    if ( argc != 2 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image,image_hsv;
    image = imread( argv[1], IMREAD_REDUCED_COLOR_2);
    if ( !image.data ){
        printf("No image data \n");
        return -1;
    }
    cvtColor(image,image_hsv,COLOR_BGR2HSV);
    Mat channels[3];
    split(image_hsv,channels);
    int width = image.cols;
    int height = image.rows;
    uchar sat,hue;
    for (int x=0;x<width;x++){
      for (int y=0;y<height;y++){
        hue = channels[0].at<uchar>(y,x);
        sat = channels[0].at<uchar>(y,x);
        if(hue < 10 || 170 < hue){
          continue;
        }
        channels[1].at<uchar>(y,x) = 0;
      }
    }
    merge(channels,3,image_hsv);
    Mat image_result;
    cvtColor(image_hsv,image_result,COLOR_HSV2BGR);
    imwrite( "./result.jpg", image_result );
    return 0;
}
