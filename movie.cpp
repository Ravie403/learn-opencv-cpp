#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
/*
  動画の読みこみを行う。
*/

int main(int argc, char** argv ){
    VideoCapture cap("./sample.mp4");
    if (!cap.isOpened()){ return -1; }
    Mat img;
    VideoWriter writer("./result_movie.avi",CV_FOURCC_DEFAULT,30,Size(1280,720));
    if (!writer.isOpened()){ return -1; }
    int mframe=cap.get(CV_CAP_PROP_FRAME_COUNT);
    int width=cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height=cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    Mat channels[3],img_hsv,img_res;
    uchar sat,hue;
    for(int i=0;i<150;i++){
      cap >> img;
      cvtColor(img,img_hsv,COLOR_BGR2HSV);
      split(img_hsv,channels);
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
      merge(channels,3,img_hsv);
      cvtColor(img_hsv,img_res,COLOR_HSV2BGR);
      writer << img_res;
    }
    return 0;
}
