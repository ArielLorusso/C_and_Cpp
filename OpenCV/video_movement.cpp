#include "opencv2/opencv.hpp"
#include <cmath>
#include <vector>
#include <stdio.h>
#include <iostream>



using namespace std;
using namespace cv;
 
typedef std::vector< std::vector< float >> kernel;

typedef struct my_rgb
{
    uint16_t R;
    uint16_t G;
    uint16_t B;
} my_pixel ;

kernel kernel_resize ( kernel filter, uint i, uint j)
{
    filter.resize(i);
	for(uint k=0; k<i ; k++)
    {
		filter[k].resize(j);
	}
return filter;
}

Mat my_convolution (Mat img , kernel  filter ) 
{
    Mat cpy ;
    cv::resize(img,cpy, cv::Size(img.cols,img.rows));
	uint8_t aux;
	uint8_t filt_x = filter.size() ,filt_y = filter[0].size();
    float sumR,sumB,sumG;
	for(uint r=0 ; r < (img.rows - filt_x +1) ; ++r)
    {
        for(uint c=0 ; c < (img.cols - filt_y + 1) ; ++c)
        {
            
            sumR = 0 ;
            sumG = 0 ;
            sumB = 0 ;
            for(uint i=0 ; i < filt_x ; ++i)
            {
                for(uint j=0 ; j < filt_y ; ++j)
                {        
                    sumR +=   (float)img.at< Vec3b>(r+i,c+j)[0] * filter[i][j]  ;
                    sumG +=   (float)img.at< Vec3b>(r+i,c+j)[1] * filter[i][j]  ;
                    sumB +=   (float)img.at< Vec3b>(r+i,c+j)[2] * filter[i][j]  ;
                }
            }
			//if(sum < 1)  {sum = -sum;}	//NO NEGATIVE ALOWED they goto 255
            //sum /= (float)(filt_x*filt_y) ;
            cpy.at< Vec3b>(r,c)[0] =  sumR ;
            cpy.at< Vec3b>(r,c)[1] =  sumG ;
            cpy.at< Vec3b>(r,c)[2] =  sumB ;
        }
    }
    return cpy;
}

void blackspace( my_pixel & RGB )
{
    RGB.R = 0;
    RGB.G = 0;
    RGB.B = 0;
}


void flip_GRB( my_pixel & RGB )
{
    uint8_t aux = RGB.R;
    RGB.R = RGB.G;
    RGB.G = RGB.B;
    RGB.B = aux;
}

void movement( my_pixel & RGB_now , my_pixel & RGB2 )
{
    uint16_t mod = (abs(RGB_now.R - RGB2.R)
                +  abs(RGB_now.G - RGB2.G)
                +  abs(RGB_now.B - RGB2.G )  )/2;

    // mod*=2; 
    if (mod >200)
        mod=200;
    
  //  RGB_now.R /= 5;
  //  RGB_now.G /= 5;
  //  RGB_now.B /= 5;
    
    RGB_now.R = mod;//`255.0f * RGB_now.R ;
    RGB_now.G = mod;//255.0f * RGB_now.G ;
    RGB_now.B = mod;//255.0f * RGB_now.B ;
}


void img_compare (Mat & img_now, Mat & img_prev)
{
   // cv::Vec3b* now, prev;
    my_pixel   RGB_now ,RGB_prev ;
    for( uint r = 0 ; r < img_now.rows ; ++r)
    {
        cv::Vec3b* now  = img_now.ptr<cv::Vec3b>(r);
        cv::Vec3b* prev = img_prev.ptr<cv::Vec3b>(r);
        for( uint c = 0 ; c < img_now.cols ; ++c)
        {
            RGB_now.R = now[c][0];
            RGB_now.G = now[c][1];
            RGB_now.B = now[c][2];
            
            RGB_prev.R = prev[c][0];
            RGB_prev.G = prev[c][1];
            RGB_prev.B = prev[c][2];
          
            movement(RGB_now, RGB_prev);
            
            now [c] = cv::Vec3b(RGB_now.R , RGB_now.G, RGB_now.B);
        }
    }
}


void LoadColor(Mat & img)
{
    my_pixel RGB ;
    for( uint r = 0 ; r < img.rows ; ++r)
    {
        for( uint c = 0 ; c < img.cols ; ++c)
        {
       
            cv::Vec3b* ptr = img.ptr<cv::Vec3b>(r);
            RGB.R = ptr[c][0];
            RGB.G = ptr[c][1];
            RGB.B = ptr[c][2];
            
            if(  c > img.cols/2 )
            {   flip_GRB(RGB);   }
            
            
            ptr[c] = cv::Vec3b(RGB.R, RGB.G, RGB.B);
        }
    }
}


std::string GetMatDepth(const cv::Mat& mat)
{
    const int depth = mat.depth();

    switch (depth)
    {
    case CV_8U:  return "CV_8U";
    case CV_8S:  return "CV_8S";
    case CV_16U: return "CV_16U";
    case CV_16S: return "CV_16S";
    case CV_32S: return "CV_32S";
    case CV_32F: return "CV_32F";
    case CV_64F: return "CV_64F";
    default:
        return "Invalid depth type of matrix!";
    }
}

std::string GetMatType(const cv::Mat& mat)
{
    const int mtype = mat.type();

    switch (mtype)
    {
    case CV_8UC1:  return "CV_8UC1";
    case CV_8UC2:  return "CV_8UC2";
    case CV_8UC3:  return "CV_8UC3";
    case CV_8UC4:  return "CV_8UC4";

    case CV_8SC1:  return "CV_8SC1";
    case CV_8SC2:  return "CV_8SC2";
    case CV_8SC3:  return "CV_8SC3";
    case CV_8SC4:  return "CV_8SC4";

    case CV_16UC1: return "CV_16UC1";
    case CV_16UC2: return "CV_16UC2";
    case CV_16UC3: return "CV_16UC3";
    case CV_16UC4: return "CV_16UC4";

    case CV_16SC1: return "CV_16SC1";
    case CV_16SC2: return "CV_16SC2";
    case CV_16SC3: return "CV_16SC3";
    case CV_16SC4: return "CV_16SC4";

    case CV_32SC1: return "CV_32SC1";
    case CV_32SC2: return "CV_32SC2";
    case CV_32SC3: return "CV_32SC3";
    case CV_32SC4: return "CV_32SC4";

    case CV_32FC1: return "CV_32FC1";
    case CV_32FC2: return "CV_32FC2";
    case CV_32FC3: return "CV_32FC3";
    case CV_32FC4: return "CV_32FC4";

    case CV_64FC1: return "CV_64FC1";
    case CV_64FC2: return "CV_64FC2";
    case CV_64FC3: return "CV_64FC3";
    case CV_64FC4: return "CV_64FC4";

    default:
        return "Invalid type of matrix!";
    }
}



int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap("/home/ariel/Vídeos/video3.mp4"); 
    
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
    
    kernel filter; 
    filter = kernel_resize(filter ,1,1);

    filter[0][0] =  1.f;    //filter[0][1] =  0.25f;  //  filter[0][2] =  0.21f;
//    filter[1][0] =  0.25f;    filter[1][1] =  0.25f;  //  filter[1][2] =  0.21f;
//    filter[2][0] =  0.11f;    filter[2][1] =  0.11f;  //  filter[2][2] =  0.21f;
    
    
    Mat img_prev,  frame,trash;
    

    uint i =0;
    
    while(1)
    {
        
        // Capture frame-by-frame
        cap >> img_prev ;
        cap >>trash;
        cap >> frame;
        imshow( "orig ", frame );
        
        //frame    = my_convolution ( frame ,filter )   ;
        //img_prev = my_convolution ( img_prev ,filter );
        //erode(frame, frame, getStructuringElement(MORPH_RECT, Size(7, 7)));
        //erode(img_prev, img_prev, getStructuringElement(MORPH_RECT, Size(7, 7)));
        
        // If the frame is empty, break immediately
        if (frame.empty())
        { break;}

        //LoadColor(frame);
        imshow( "prev ", frame );
        img_compare(frame, img_prev);
        imshow( "post", frame );
        if(i%2)
        {
             
            // LoadColor(frame);
            
            // cout << frame.type << frame.deph() ; 
           // cout << GetMatDepth(frame)<< "\t" << GetMatType(frame)<< "|||" ;
        }
        else
        {
            // img2 = frame;
        }
          
        // Display the resulting frame
        
        
        // Press  waitKey(25); ESC on keyboard to exit
         char c=(char)waitKey(50);
        if(c==27)
        {    break;}
        i++;
    }
  
  // When everything done, release the video capture object
  cap.release();
 
  // Closes all the frames
  destroyAllWindows();
   
  return 0;
}
