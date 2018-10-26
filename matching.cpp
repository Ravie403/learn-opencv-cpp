#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
/*
  http://ni4muraano.hatenablog.com/entry/2017/01/25/000000
  より。
*/

int main(int argc, char** argv ){
  Mat img1, img2;
  img1 = imread("./photo.jpg", IMREAD_REDUCED_COLOR_2);
  img2 = imread("./seg1.jpg", IMREAD_UNCHANGED);

  vector<KeyPoint> keyPoint1, keyPoint2;
  Ptr<FeatureDetector> keyPointDetector = AKAZE::create();
// Ptr<FeatureDetector> keyPointDetector = ORB::create(80, 2.25f, 4, 7);
  Mat img1_gray,img2_gray;
  cvtColor(img1,img1_gray,COLOR_BGR2GRAY);
  cvtColor(img2,img2_gray,COLOR_BGR2GRAY);

  keyPointDetector->detect(img1_gray, keyPoint1);
  keyPointDetector->detect(img2_gray, keyPoint2);
  Mat descriptor1, descriptor2;

  Ptr<DescriptorExtractor> extractor = AKAZE::create();
  // Ptr<DescriptorExtractor> extractor =ORB::create(80, 2.25f, 4, 7);
  extractor->compute(img1, keyPoint1, descriptor1);
  extractor->compute(img2, keyPoint2, descriptor2);

  Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
  vector<DMatch> forwardMatches;
  matcher->match(descriptor1, descriptor2, forwardMatches);
  vector<DMatch> backwardMatches;
  matcher->match(descriptor2, descriptor1, backwardMatches);
  vector<DMatch> matches;
  for (int i = 0; i < forwardMatches.size(); ++i){
      DMatch forward = forwardMatches[i];
      DMatch backward = backwardMatches[forward.trainIdx];
      if (backward.trainIdx == forward.queryIdx){
          matches.push_back(forward);
      }
  }
  vector<DMatch> better_matches;
  const float th = 1250.0f;
  for (auto itr = matches.begin();itr!=matches.end();itr++){
    if(itr->distance < th) better_matches.push_back(*itr);
  }
  vector<vector<char> >A;
  Mat destination;
  drawMatches(img1, keyPoint1, img2, keyPoint2, better_matches, destination);
  imwrite("./matching.jpg",destination);
  return 0;
}
