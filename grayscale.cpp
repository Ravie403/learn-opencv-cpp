#include <opencv2/opencv.hpp>

using namespace cv;
/*
  https://docs.opencv.org/master/db/d64/tutorial_load_save_image.html
  http://tessy.org/wiki/index.php?%B2%E8%C1%FC%A4%CE%C6%C9%A4%DF%B9%FE%A4%DF を参考
  imread(file,color_mode)
  color_modeは()内の数値かIMREAD_XXXXで記述
  IMREAD_UNCHANGED (-1):8bit画像として読み込む、
  IMREAD_GRAYSCALE (0):グレースケールで読み込む
  IMREAD_COLOR (1):デフォルト、BGR形式で読み込む
  IMREAD_ANYDEPTH (2):画像のbit数は自動判別、チャンネルは未指定
  IMREAD_ANYCOLOR (4):画像のbit数は未指定、チャンネルは自動判別
  IMREAD_REDUCED_{color:GRAYSCALE|COLOR}_{size:2|4|8} (16,17, 32,33, 64,65)
    1/sizeの大きさで読み込む

  このプログラムは明示的にBGRで読み込んだ画像をgrayscaleに変換し、出力する
*/

int main(int argc, char** argv ){
    if ( argc != 2 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], IMREAD_COLOR );
    if ( !image.data ){
        printf("No image data \n");
        return -1;
    }
    Mat gray_image;
    cvtColor( image, gray_image, COLOR_BGR2GRAY );
    imwrite( "./Gray_Image.jpg", gray_image );
    return 0;
}
