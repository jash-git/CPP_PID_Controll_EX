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
//PID �����@ �Ʀr�l�v��
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
        inc = pid.calculate(setpoint, val);//setpoint(�ؼ�[����]),input(��J)
        //printf("i=%d,val:% 7.5f inc:% 7.5f\n",i, val, inc);//��ܤp���I����
        if(fabs(val-setpoint)<0.0001)//�p���I�|��
        {
            break;
        }
        val += inc;
        i++;
    }

    printf("i=%d,val:% 7.5f inc:% 7.5f\n",i, val, inc);//��ܤp���I����

	time_t t02 = time(NULL);
	struct tm tm02 = *localtime(&t02);
    printf("end: %4d-%02d-%02d %02d:%02d:%02d\n", tm02.tm_year + 1900, tm02.tm_mon + 1, tm02.tm_mday, tm02.tm_hour, tm02.tm_min, tm02.tm_sec);
    return 0;
}
