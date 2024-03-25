 #define OLC_PGE_APPLICATION

// g++ -o demo2 olcExampleProgram.cpp  -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

//#include "/home/ariel/Escritorio/OLC/olcPixelGameEngine.h"  
#include "olcPixelGameEngine.h"

#include <iostream>
#include <string>
#include <algorithm>

#define screenW 1366
#define screenH 720 //768
#define Npix 1

using namespace std;

class Asteroids : public olc::PixelGameEngine
{
private:
    
    typedef struct space_obj
    {
        float x;
        float y;
        float dx;
        float dy;
        int nSize;
    } space_obj;
    
    vector < space_obj > vecAsteroids;    
    
public:

    Asteroids()
	{
		sAppName = "Example";
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
        //vecAsteroids.resize(0);
        FillRect(0,0, screenW/Npix, screenH/Npix,  {50,10,0});
        vecAsteroids.push_back( {30.0f, 30.0f, 180.0f, -150.0f,(int)16} );
        vecAsteroids.push_back( {30.0f, 30.0f, 18.0f, 15.0f,(int)16} );
		//vecAsteroids.push_back( {20.0f, 20.0f, -120.0f, -100.0f,(int)16} );
        //vecAsteroids.push_back( {20.0f, 20.0f, -120.0f, 100.0f,(int)16} );
        return true;
	}

	bool OnUserUpdate(float fElapsedTime) override  // called once per frame
	{
		// FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = olc::WHITE);
		FillRect(0,0, screenW/Npix, screenH/Npix,  {50,10,0});
        
        for (auto &a : vecAsteroids)
        {
            a.x += a.dx * fElapsedTime;
            a.y += a.dy * fElapsedTime;
            
            wrap_coordintes( a.x , a.y) ;
            
            for (int x=0; x < a.nSize ; ++x)
            {
                for (int y=0; y <a.nSize ; ++y)
                {
                     Draw(a.x +x, a.y + y, olc::Pixel(17*x,6*y,17*y ));   
                }
            }
            //FillRect(a.x , a.y , a.x + a.nSize, a.y + a.nSize ,  {0,0,0});
        }
		return true;
	}
	
    void wrap_coordintes( float& ox, float& oy)
    {
        float ix = ox;
        float iy = oy;
        if( ix < 0.0f )             { ox = ix + (float) screenW/Npix; }
        if ( ix >= screenW/Npix)    { ox = ix - (float) screenW/Npix; }     
        if( iy < 0.0f )             { oy = iy + (float) screenH/Npix; }
        if ( iy >= screenH/Npix)    { oy = iy - (float) screenH/Npix; }     
    }

};


int main()
{
	Asteroids demo;
	if (demo.Construct( screenW/Npix,  screenH/Npix, Npix, Npix))
		demo.Start();

	return 0;
}
