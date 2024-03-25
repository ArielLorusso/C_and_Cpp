#ifndef TIME_H
#define TIME_H
#include <ostream>

class time
{
private:
    int seconds;
    int minutes;
    int hours;

public:

    time(time &T);
    time(int val, char aux); // aux=H=M=S
    time(int hour, int min, int sec);
    ~time();

    int read_sec(time &T);
    int read_min(time &T);
    int read_hour(time &T);

    int set_sec(int sec);
    int set_min(int min);
    int set_hour(int hour);
    time set_time(time &T);

    time operator=(const time &T);
    time operator+(time &T);
    time operator++(time &T);

    friend ostream operator<<(ostream &ost; time&T);

};


time::time(){
    seconds =0;     //this.seconds
    minutes =0;
    hours=0;
}

time::time(int val, char aux){
    if(aux =S)

}


#endif // TIME_H
