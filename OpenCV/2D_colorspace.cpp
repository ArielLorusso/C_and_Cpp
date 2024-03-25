//g++  `pkg-config  --cflags opencv` -o 2D_colorspace  2D_colorspace.cpp  `pkg-config --libs opencv`


#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
#include <stdint.h>



uint8_t trunk255(int  in)
{ 
    if (in > 255)  {in =255;}
    if (in < 0)    {in=0;} 
    return in;
}

void trunk255Add ( uint8_t & in, uint8_t b)
{ 
    uint i = in + b;
    if (i > 255)  {in =255;}
    else{ in = i;}
    //if (i < 0)    {in=0;} 
}



class complex_f  
{
    private:
    float real;
    float imag;

    public:                        
    complex_f() : real( 0.0f ) , imag(0.0f) { }
    complex_f ( float r, float i ) : real(r), imag(i) { }
    
    float re_get () { return this->real;   }
    float im_get () { return this->imag;   }
    
    void re_set (const float& in) { this->real = in;   }
    void im_set (const float& in) { this->imag = in;   }
    void operator=  (const complex_f& in)
    {
        this->real  =  in.real ;
        this->imag =  in.imag ;
    }

    void operator+= (const complex_f& in)
    {
        this->real = this->real + in.real ;
        this->imag = this->imag + in.imag ;
    }
    void operator*= (const complex_f& in)
    {
        this->real  = this->real * in.real ;
        this->imag = this->imag * in.imag ;
    }
    void operator+= (const float& in)
    {
        this->real  = this->real + in ;
        this->imag  = this->imag + in ;
    } 
    void operator*= (const float& in)
    {
        this->real  = this->real * in ;
        this->imag = this->imag * in ;
    }

    const complex_f operator* (const complex_f& in)    // (a+bI) (c+dI) = (ac-bd) + (ad+bc)
    {
        complex_f out;
        out.real  =  this->real * in.real  -  this->imag * in.imag  ;
        out.imag =  this->real * in.imag  +  this->imag * in.real  ;
        return out ;
    }
    const complex_f operator* (float  in)    /// (a+bI) (c+dI) = (ac-bd) + (ad+bc)
    {
        complex_f out;
        out.real  =  this->real * in  ;
        out.imag =  this->imag * in  ;
        return out ;
    }

    const complex_f operator+ (const complex_f& c)
    {
        complex_f out;
        out.real  = this->real + c.real  ;
        out.imag = this->imag + c.imag  ;
        return out ;
    }
    const complex_f operator- (const complex_f& c)
    {
        complex_f out;
        out.real  = this->real - c.real  ;
        out.imag = this->imag - c.imag  ;
        return out ;
    }
};


typedef std::complex < uint> complex_u;

static complex_f  R_VEC ( 220.0f , -127.0f ) ;
static complex_f  G_VEC (   0.0f ,  255.0f ) ;
static complex_f  B_VEC (-220.0f , -127.0f ) ;


complex_f rgb_to_hl_cmplx ( uint r, uint g , uint b) // maps   RGB  -> Re,Im  
{
    complex_f vec1 , vec2 ,aux, res;
    if( g > r && g > b)     // GREEN BIGGEST
    {
        vec1.im_set( (float) g );         // blue 2nd biggest
        if( b > r ) 
        {
            vec2  = B_VEC;
            vec2 *= ( b / 255.0f);
            res = vec1 + vec2;
            aux = res * (r/255.0f);
            res += aux;
            return res;
        }             
        else                               // red 2nd
        {
            vec2  = R_VEC;
            vec2 *= ( r / 255.0f); 
            res = vec1 + vec2;
            aux = res * (b/255.0f);
            res += aux;
            return res;
        }                 
    }

    if( r > g && r > b)        // RED BIGGEST
    {
        vec1 = R_VEC  ; 
        vec1 *=  ( r / 255.0f ) ;
        if( g > b)                           // green 2nd
        {
            vec2.re_set( (float) g ); 
            res = vec1 + vec2;
            aux = res * (b/255.0f);
            res += aux;
            return res;
        }
        else                                // blue 2nd
        {
           vec2  = G_VEC;
           vec2 *= ( r / 255.0f);
           res = vec1 + vec2;
           aux = res * (g/255.0f);
           res += aux;
           return res;
        }                          
    }

    if( b > g && b > r)     // BLUE BIGGEST
    {
        vec1  = B_VEC;
        vec1 *= ( b / 255.0f);
        if( g>r)                        //  green 2d
        {
           vec2  = G_VEC;
           vec2 *= ( r / 255.0f);
           res = vec1 + vec2;
           aux = res * (r/255.0f);
           res += aux;
           return res;
        }
        else                            // red 2nd
        {
            vec2  = B_VEC;
            vec2 *= ( b / 255.0f);
            res = vec1 + vec2;
            aux = res * (b/255.0f);
            res += aux;
            return res;
        }
    }
    return res;
}




using namespace cv;
using namespace std;

typedef struct my_rgb
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} my_pixel ;


//greenByPosition();

void TestLoad(Mat & img)
{
    uint x_center = img.rows/2;
    uint y_center = img.cols/2;
    my_pixel RGB;
    for( uint r = 0 ; r < img.rows ; ++r)
    {
        RGB.R = r;
        RGB.G = r/4;
        RGB.B = 0;
        for( uint c = 0 ; c < img.cols ; ++c)
        {
            RGB.G = RGB.G + c/500;
            RGB.B  = c;
            if((r+c)==0 ) { RGB.R=255;RGB.G=0;RGB.B=255;
                cout << "0 ";
            }
            img.at< Vec3b>(r,c)[2]= RGB.R;
            img.at< Vec3b>(r,c)[1]= RGB.G;
            img.at< Vec3b>(r,c)[0]= RGB.B;
            
//            cv::Vec3b* ptr = img.ptr<cv::Vec3b>(r);
//           ptr[c] = cv::Vec3b(RGB.R, RGB.G, RGB.B);
        }
    }
}

void blackspace( my_pixel & BGR )
{
    BGR.R = 0;
    BGR.G = 0;
    BGR.B = 0;
}


void Colorspace( my_pixel & BGR , int re, int im) // maps   Re,Im -> RGB
{
    re -= 500 ; im -=400;

    if(re >= 0 )     // G R
    {
        if( im >= 0 || ( (float)re/abs(im) > 2.0f ) )  // G (0,255) + R (220,-127) = (Re, im)    
        {
            //BGR.G = trunk255(im);
            //BGR.R = trunk255(re);
            
            BGR.G = trunk255(im);
            BGR.R = trunk255((220*re-127*im)/(255.0f));

            //BGR.R = trunk255((re/220.0f)*255);  // re = 220 R
            //BGR.G = trunk255(im )  ;            // G 255  -127 R = im  
            uint8_t w = trunk255(sqrt(re*re + im*im)-(255));
            trunk255Add( BGR.R,w);
            trunk255Add( BGR.G,w);
            trunk255Add( BGR.B,w);
            return;
        }
    }
    if(re <0)       
    {
        if(im >= 0 || ( (float)re/im) > 2.0f )         // G (0,255,) + B (-220,-127) = (Re, im)
        {
            //BGR.G = trunk255(im);
            //BGR.B = trunk255(-re);
            
            BGR.G = trunk255(im);
            BGR.B = trunk255((-220*re-127*im)/(255.0f));
            
            //BGR.B = trunk255((-re/220.0f)*255);  // re = 220 R
            //BGR.G = trunk255(im )  ;            // G 255  -127 R = im  
            uint8_t w = trunk255(sqrt(re*re + im*im)-(255));
            trunk255Add( BGR.R,w);
            trunk255Add( BGR.G,w);
            trunk255Add( BGR.B,w);
            return;
        }
    }
              //  R B // R (-127,-220) + B (-127,-220) = (Re, im)
    
            BGR.R = trunk255((220*re-127*im)/(255));    BGR.B = trunk255(re);
            BGR.B = trunk255((-220*re-127*im)/(255));

            //BGR.B = trunk255((-im-2*re)/2.0f);  // re = 220 R
            //BGR.R = trunk255((-im+2*re)/2.0f);
            
            uint8_t w = trunk255(sqrt(re*re + im*im)-(255));
            trunk255Add( BGR.R,w);
            trunk255Add( BGR.G,w);
            trunk255Add( BGR.B,w);
}

void LoadColor(Mat & img)
{
    uint x_center = img.rows/2;
    uint y_center = img.cols/2;
    my_pixel BGR ;
    for( uint r = 0 ; r < img.rows ; ++r)
    {
        for( uint c = 0 ; c < img.cols ; ++c)
        {
            Colorspace(BGR,c,r);
            img.at <Vec3b> (r,c) [0] = BGR.B;
            img.at <Vec3b> (r,c) [1] = BGR.G;
            img.at <Vec3b> (r,c) [2] = BGR.R;
            blackspace(BGR);
//            cv::Vec3b* ptr = img.ptr<cv::Vec3b>(r);
//            ptr[c+10] = cv::Vec3b(RGB.R, RGB.G, RGB.B);
        }
    }
}

typedef vector< vector< float >> kernel;

int main ()
{
    Mat img (1000, 1000, CV_8UC3, Scalar(0,10, 0));
    
    while (1)
    {
        
//        TestLoad(img);
        imshow("img", img);
        waitKey();
        LoadColor(img);
        imshow("img", img);
        char c = waitKey();
        if (c == 'q'){break;}
    }
    
    return 0;
}

