//g++  `pkg-config  --cflags opencv` -o 2D_colorspace  2D_colorspace.cpp  `pkg-config --libs opencv`


#include <opencv2/core.hpp>
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
    
    float re_get () { return (float) this->real;   }
    float im_get () { return (float) this->imag;   }
    
    void re_set (const float& in) { this->real = in;   }
    void im_set (const float& in) { this->imag = in;   }
    void operator=  (const complex_f& in)
    {
        this->real =  in.real ;
        this->imag =  in.imag ;
    }

    void operator+= (const complex_f& in)
    {
        this->real = this->real + in.real ;
        this->imag = this->imag + in.imag ;
    }
    void operator*= (const complex_f& in)
    {
        this->real = this->real * in.real ;
        this->imag = this->imag * in.imag ;
    }
    void operator+= (const float& in)
    {
        this->real = this->real + in ;
        this->imag = this->imag + in ;
    } 
    void operator*= (const float& in)
    {
        this->real = this->real * in ;
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


complex_f rgb_to_cplx ( uint8_t r, uint8_t g , uint8_t b) // maps   RGB  -> Re,Im  
{
    complex_f vec1 , vec2 ,aux, res;
    if( g >= r && g >= b)     // GREEN BIGGEST
    {
        vec1 = G_VEC;
        vec1 *= ( g / 255.0f);
        if( b >= r )                        // blue 2nd biggest
        {
            vec2  = {-220.0f , -127.0f };
            vec2 *= ( b / 255.0f);
            res = vec1 + vec2;
           // aux = res * (r/255.0f);
           // res += aux;
            return res;
        }             
        else                               // red 2nd
        {
            vec2  = { 220.0f , -127.0f };
            vec2 *= ( r / 255.0f); 
            res = vec1 + vec2;
          //  aux = res * (b/255.0f);
           // res += aux;
            return res;
        }                 
    }

    if( r >= g && r >= b)        // RED BIGGEST
    {
        vec1 =  { 220.0f , -127.0f } ; 
        vec1 *=  ( r / 255.0f ) ;
        if( g >= b)                           // green 2nd
        {
        vec2 =  G_VEC;
        vec2 *= (g/255.0f);
            res = vec1 + vec2;
     //       aux = res * (b/255.0f);
     //       res += aux;
            return res;
        }
        else                                // blue 2nd
        {
           vec2  = {-220.0f , -127.0f };
           vec2 *= ( r / 255.0f);
           res = vec1 + vec2;
       //    aux = res * (g/255.0f);
       //    res += aux;
           return res;
        }                          
    }

    if( b >= g && b >= r)     // BLUE BIGGEST
    {
        vec1  ={-220.0f , -127.0f };
        vec1 *= ( b / 255.0f);
        if( g >= r)                        //  green 2d
        {
            vec2 = G_VEC;
            vec2 *=(g/255.0f);
         //  aux = res * (r/255.0f);
         //  res += aux;
           return res;
        }
        else                            // red 2nd
        {
            vec2  = R_VEC;
            vec2 *= ( r / 255.0f);
            res = vec1 + vec2;
           // aux = res * (g/255.0f);
          //  res += aux;
            return res;
        }
    }
    return res;
}

void resize_complex_mat ( uint img_rows, uint img_cols, std::vector< std::vector< complex_f>> & comp_img )
{
    comp_img.resize( img_rows );
    for (uint r=0 ; r< img_rows ; ++r)
    {
            comp_img[r].resize( img_cols );
    }
}


using namespace cv;
using namespace std;

typedef struct my_rgb
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} my_pixel ;

void cplx_to_rgb ( my_pixel & BGR , complex_f  cplx ) // maps   Re,Im -> RGB
{
    float re = cplx.re_get() , im = cplx.re_get();

    if(re >= 0 )     // G R
    {
        if( im >= 0 || ( (float)re/abs(im) > 2.0f ) )  // G (0,255) + R (220,-127) = (Re, im)    
        {
            //BGR.G = trunk255(im);
            //BGR.R = trunk255(re);
            
            BGR.G = trunk255(im/2);
            BGR.R = trunk255((220*re-127*im)/(500.0f));

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
            
            BGR.G = trunk255(im/2);
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
            BGR.B = trunk255((-220*re-127*im)/(500));

            //BGR.B = trunk255((-im-2*re)/2.0f);  // re = 220 R
            //BGR.R = trunk255((-im+2*re)/2.0f);
            
            uint8_t w = trunk255(sqrt(re*re + im*im)-(255));
            trunk255Add( BGR.R,w);
            trunk255Add( BGR.G,w);
            trunk255Add( BGR.B,w);
}


void load_cplx_to_rgb (Mat & img, std::vector< std::vector< complex_f>> & comp_img)
{

    my_pixel RGB;
    for( uint r = 0 ; r < img.rows ; ++r)
    {   
        for( uint c = 0 ; c < img.cols ; ++c)
        {
//            float i = comp_img[r][c].re_get;
 //           float j = comp_img[r][c].im_get;
            cplx_to_rgb (RGB  , comp_img[r][c]);

            img.at< Vec3b>(r,c)[2] = RGB.R;
            img.at< Vec3b>(r,c)[1] = RGB.G;
            img.at< Vec3b>(r,c)[0] = RGB.B;
            
//            img.at< Vec3b>(r,c)[2] = 0;
//          img.at< Vec3b>(r,c)[1] = 0;
//            img.at< Vec3b>(r,c)[0] = 0;
            
            
        }
    }
}


void load_rgb_to_cplx (Mat & img, vector< vector <complex_f>> &comp_img)
{
    uint x_center = img.rows/2;
    uint y_center = img.cols/2;
    my_pixel BGR ;
    for( uint r = 0 ; r < img.rows ; ++r)
    {
        for( uint c = 0 ; c < img.cols ; ++c)
        {
            BGR.B = img.at <Vec3b> (r,c) [0] ;
            BGR.G = img.at <Vec3b> (r,c) [1] ;
            BGR.R = img.at <Vec3b> (r,c) [2] ;
            
            comp_img[r][c] = rgb_to_cplx ( BGR.R, BGR.G ,BGR.B);
            
        }
    }
}

#define filename   "./Edge/sample.jpg"
#define filename2  "./samplecolor"


typedef vector< vector< float >> kernel;

int main ()
{
    Mat img = imread(filename2,IMREAD_COLOR);
    imshow("img", img);
    //waitKey(300);
    std::vector< std::vector< complex_f >> comp_img ;
    resize_complex_mat(img.rows, img.cols, comp_img);
    load_rgb_to_cplx(img, comp_img);
    load_cplx_to_rgb(img, comp_img);

    while (1)
    {
        
        img = imread( filename ,IMREAD_COLOR);
        imshow("img", img);
        waitKey(1000);
        std::vector< std::vector< complex_f >> comp_img ;
        resize_complex_mat(img.rows, img.cols, comp_img);
        load_rgb_to_cplx(img, comp_img);
        load_cplx_to_rgb(img, comp_img);
        imshow("img", img);
        char c = waitKey(1000);
        if (c == 'q'){break;}
    }
    
    return 0;
}

