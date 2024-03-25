#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
#include <stdint.h>

using namespace cv;
using namespace std;

typedef std::vector< std::vector< float >> kernel;


Mat resample (int scale_div , Mat img ) 
{
    for(uint r=0 ; r < (img.rows) ; r+=scale_div)
    {
        for(uint c=0 ; c < (img.cols) ; c+=scale_div)
        {
            uint val = 0;

            for (uint i=0 ; i < scale_div ; i++)
            {
                for (uint j=0 ; j < scale_div ; j++)
                {
                    val +=  img.at<uint8_t>(r+i,c+j);
                }
            }
            
            img.at<uint8_t>(r/scale_div,c/scale_div) = val /scale_div/scale_div;

        }
    }
    return img;
}

Mat brigtMult ( float mult , Mat img ) 
{
    for(int r=0 ; r < img.rows ; r++)      // x from left
    {
        for(int c=0 ; c < img.cols ; c++)  // Y from bottom
        {
            uint val = (img.at<uint8_t>(r,c) * 2) ;
            if(val >255) {val=255;}
            img.at<uint8_t>(r,c) = val ;
        }    
    }
    return img;
}

kernel kernel_resize ( kernel filter, uint i, uint j)
{
    filter.resize(i);
	for(uint k=0; k<i ; k++)
    {
		filter[k].resize(j);
	}
return filter;
}

Mat myresize (float scale_div , Mat img ) 
{
    for(uint r=0 ; r < (img.rows) ; r+= ceil(scale_div))
    {
        for(uint c=0 ; c < (img.cols) ; c+=ceil(scale_div))
        {
            uint val = 0;
            //Mat newimg = cvCreateImage(cvSize(img.rows,img.cols),img.depth(),img.channels());

            for (uint i=0 ; i < floor(scale_div) ; i++)
            {
                for (uint j=0 ; j < floor(scale_div) ; j++)
                {
                    val +=  img.at<uint8_t>(r+i,c+j);
                }
            }
            
            img.at<uint8_t>(r/scale_div,c/scale_div) = val /scale_div/scale_div;

        }
    }
    return img;
}


void neigbour_check (Mat img)
{
	uint sizeCheck = 2;
	uint sum;
    for(uint r=0 ; r < img.rows -sizeCheck; ++r)
    {
        for(uint c=0 ; c < img.cols -sizeCheck; ++c)
        {   
			sum=0;
			for(uint i=0 ; i < sizeCheck; ++i)
        	{   
				for(uint j=0 ; j < sizeCheck; ++j)
        		{    
           	 		sum += img.at<uint8_t>(r+i,c+j)  ;
				} 
			}
			if  (sum < 250) { img.at<uint8_t>(r,c) =   (float) img.at<uint8_t>(r,c) / 3.0; }
        }
    }
    return ;
}

void thresholding (Mat img)
{
	uint sizeCheck = 2;
	uint sum;
    for(uint r=0 ; r < img.rows -sizeCheck; ++r)
    {
        for(uint c=0 ; c < img.cols -sizeCheck; ++c)
        {   
			
			if  ( img.at<uint8_t>(r,c) > 40)
			{ 
				img.at<uint8_t>(r,c) = 250;
			}
			else
			{ 
				img.at<uint8_t>(r,c) = 0;
			}  
        }
    }
    return ;
}


Mat img_sum (Mat img1,Mat img2 )
{
    Mat sum ;
    cv::resize(img1,sum, cv::Size(img1.cols,img1.rows));
	for(uint r=0 ; r < img1.rows ; ++r)
    {
        for(uint c=0 ; c < img1.cols ; ++c)
        {         	
            sum.at<uint8_t>(r,c) = img1.at<uint8_t>(r,c) + img2.at<uint8_t>(r,c)  ;
        }
    }
    return sum;
}


Mat my_convolution (Mat img , kernel  filter ) 
{
    Mat cpy ;
    cv::resize(img,cpy, cv::Size(img.cols,img.rows));
	uint8_t aux;
	uint8_t filt_x = filter.size() ,filt_y = filter[0].size();
    float sum;
	for(uint r=0 ; r < (img.rows - filt_x +1) ; ++r)
    {
        for(uint c=0 ; c < (img.cols - filt_y + 1) ; ++c)
        {
            sum = 0 ;
            for(uint i=0 ; i < filt_x ; ++i)
            {
                for(uint j=0 ; j < filt_y ; ++j)
                {        
                    sum +=  ((float) img.at< Vec3b> (r+i,c+j)[0] - 128) * filter[i][j]  ;
                }
            }
			if(sum < 1){sum = -sum;}	//NO NEGATIVE ALOWED they goto 255
			sum /= (float)(filt_x*filt_y) ;
            img.at< Vec3b>(r,c) =  sum ;
        }
    }
    return cpy;
}




int main (int argc, char** argv)
{
    Mat original = imread ("sample.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    
 //   Mat modified ;
 //   modified = my_brigtnesMult(1.5f , original  );
    
    
    // Mat redu = imread ("sample.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //redu = myresize (1.5,redu);
    //cv::resize(original,redu, cv::Size(1500,1500));

    kernel filter; 
    filter = kernel_resize(filter ,3,3);

    filter[0][0] =  0.0f;    filter[0][1] = -1.0f; 	 filter[0][2] =  -2.0f;
    filter[1][0] =  1.0f;    filter[1][1] =  0.0f;   filter[1][2] =  -1.0f;
    filter[2][0] =  2.0f;    filter[2][1] =  1.0f;   filter[2][2] =   0.0f;
    
    Mat img1 = my_convolution ( original,filter );
	img1 = brigtMult(20,img1);
	//neigbour_check(img1);
	// thresholding(img1);

	//filter = kernel_resize (filter,3,3);

    filter[0][0] = -2.0f;	filter[0][1] = -1.0f; 	filter[0][2] =  0.0f;
    filter[1][0] = -1.0f;	filter[1][1] =  0.0f;   filter[1][2] =  1.0f;
    filter[2][0] =  0.0f;  	filter[2][1] =  1.0f;   filter[2][2] =  2.0f;

    Mat img2 = my_convolution ( original,filter );
	img2 = brigtMult(20 ,img2);
	//neigbour_check(img2);
	//thresholding(img2);
	

	Mat img3 = img_sum ( img1 , img2 );
	neigbour_check(img1);	
	neigbour_check(img2);  
	thresholding(img3);

    imshow("original",original);
    imshow("img1",img1);    
    imshow("img2",img2);    
    imshow("img3",img3);    
    //imshow("reduced",redu);    
    waitKey();
    return 0;
}
