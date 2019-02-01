#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <sys/timeb.h>
#include <windows.h>
#include "PIDImpl.h"


using namespace std;
//https://gist.github.com/bradley219/5373998
//PID 控制器實作 數字追逐賽
int main()
{
    PID pid = PID(0.1, 100, -100, 0.1, 0.01, 0.5);//0.1s=10Hz,outmax=100,outmin=-100,P=0.1,I=0.01,D=0.5
    double val = 10.0;
    double setpoint = 50.0;
    double inc=0.0;
    long i=1;

    time_t t01 = time(NULL);
	struct tm tm01 = *localtime(&t01);
    printf("start: %4d-%02d-%02d %02d:%02d:%02d\n", tm01.tm_year + 1900, tm01.tm_mon + 1, tm01.tm_mday, tm01.tm_hour, tm01.tm_min, tm01.tm_sec);
    while(1)
    {
        Sleep( 100 );//100ms=0.1s
        inc = pid.calculate(setpoint, val);//setpoint(目標[期望]),input(輸入)
        //printf("i=%d,val:% 7.5f inc:% 7.5f\n",i, val, inc);//顯示小數點五位
        if(fabs(val-setpoint)<0.0001)//小數點四位
        {
            break;
        }
        val += inc;
        i++;
    }

    printf("i=%d,val:% 7.5f inc:% 7.5f\n",i, val, inc);//顯示小數點五位

	time_t t02 = time(NULL);
	struct tm tm02 = *localtime(&t02);
    printf("end: %4d-%02d-%02d %02d:%02d:%02d\n", tm02.tm_year + 1900, tm02.tm_mon + 1, tm02.tm_mday, tm02.tm_hour, tm02.tm_min, tm02.tm_sec);
    return 0;
}
