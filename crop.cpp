#include <opencv2/opencv.hpp>

using namespace cv;
/*
  cv::Rect で画像を切り出すことができる
  このプログラムは２点間を対角線とする長方形で画像を切り出す。
*/

Mat crop(Mat image, int x1,int y1,int x2 = 0,int y2 = 0){
  Rect rect(Point(min(x1,x2),min(y1,y2)),Size(abs(x2-x1),abs(y2-y1)));
  Mat c = image(rect);
  return c;
}

int main(int argc, char** argv ){
    if ( argc != 2 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    Rect rect(Point(0,0),Size(100,100));
    image = imread( argv[1], IMREAD_COLOR );
    if ( !image.data ){
        printf("No image data \n");
        return -1;
    }
    Mat cropped = crop(image,200,200,100,100);
    imwrite( "./cropped.jpg", cropped );
    return 0;
}
