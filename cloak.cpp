#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{
  unsigned char c;
  
  cv::Mat frame;

  //キャプチャオブジェクトを作成
  cv::VideoCapture cap(0);

  //バックグラウンドを保存
  cv::Mat background;
  for(int i=0;i<30;i++){
    cap >> background;
  }

  //バックグラウンドを横方向に反転
  cv::flip(background,background,1);

  //キャプチャが成功している間
  while(cap.isOpened()){

    //frameにキャプチャした画面を入れる
    cap >> frame;
    //frameを横方向に反転
    cv::flip(frame,frame,1);

    //bgrをhsvに変換
    cv::Mat hsv;
    cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

    cv::Mat mask,mask2;
    //青の範囲を指定しその範囲でマスクを作成
    inRange(hsv,cv::Scalar(100,80,60),cv::Scalar(126,255,255),mask);

    //morphology処理
    cv::Mat kernel = cv::Mat::ones(3,3,CV_32F);
    morphologyEx(mask,mask,cv::MORPH_OPEN,kernel);
    morphologyEx(mask,mask,cv::MORPH_DILATE,kernel);

    //青部分を隠す
    bitwise_not(mask,mask2);
    
    cv::Mat streamA,streamB,output;
    //青以外の部分
    bitwise_and(frame,frame,streamA,mask2);
    
    //隠した部分のもとの背景をコピー
    bitwise_and(background,background,streamB,mask);
    
    //青以外の部分と、青の部分のもとの背景を足して画面に表示
    cv::addWeighted(streamA,1,streamB,1,0,output);
    cv::imshow("invisibility cloak",output);

    //escapeキーで終了
    c=cv::waitKey (2);
    if(c=='\x1b')
      break;
  }

  cv::destroyWindow("invisibility cloak");

  return 0;
}
