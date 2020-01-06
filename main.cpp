#include <iostream>
#include<windows.h>
#include<time.h>
//#include "stdint.h"
#include "Com.h"
#include "windows.h"
#include "time.h"
#include "stdio.h"

//#include "JY901.h"
unsigned char ucComNo[2] ={0,0};
using namespace std;

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef short              int16_t;
typedef uint8_t  u8;
unsigned char  data_to_send[16];
int  start100S=0;
/****The following is the initial data received. If necessary, convert it according to the manual.	****/
int16_t yaw;       //yaw
int16_t pitch;     //pitch
int16_t roll;      //roll
int16_t alt;       //Barometric altitude
int16_t tempr;     //temperature
int32_t press;     //pressure
int16_t default1;  //default

int16_t ax;         //X_acc
int16_t ay;         //Y_acc
int16_t az;         //Z_acc
int16_t gx;         //X_yawrate
int16_t gy;         //Y_yawrate
int16_t gz;         //Z_yawrate
int16_t hx;         //X-axis magnetic strength
int16_t hy;         //Y-axis magnetic strength
int16_t hz;         //Z-axis magnetic strength

uint32_t longitud;     //longitude
uint32_t latitud;      //latitude
int16_t speed;         //GPS_speed
int16_t altitude;      //GPS_height
int16_t direction;     //GPS_direction
uint8_t lctNSWE;       //North-south latitude east-west longitude

uint8_t year;       	 //year
uint8_t month;      	 //month
uint8_t day;        	 //day
uint8_t hour;       	 //hour（UTC）
uint8_t minute;     	 //min
uint8_t second;    	   //sec
uint8_t default2;  	   //default
uint8_t posslnum;  	   //star number
uint8_t gpssta;    	   //position state
uint8_t fixmode;   	   //position type


int main() {
    std::cout << "Hello, World!" << std::endl;
    //get system time ms  https://blog.csdn.net/Xylon_/article/details/81258728
    SYSTEMTIME lpsystime;
    GetLocalTime(&lpsystime);
    cout<<lpsystime.wYear<<"year"<<lpsystime.wMonth<<"month"<<lpsystime.wDay<<"day week"<<lpsystime.wDayOfWeek<<" "<<lpsystime.wHour<<"hour"<<lpsystime.wMinute<<"min"<<lpsystime.wSecond<<"sec"<<lpsystime.wMilliseconds<<"ms"<<endl;

    unsigned char chrBuffer[200];
    unsigned short usLength=0,usCnt=0;
    unsigned long ulBaund=9600,ulComNo=3;
    signed char cResult= 1;
    uint8_t minute;     	 //min
 /*
    printf("请输入串口号:\r\nCom = ");
    scanf("%ld",&ulComNo);
    printf("请输入波特率:(9600、115200或其他)\r\nBaud = ");
    scanf("%ld",&ulBaund);
    printf("等待打开串口%d...\r\n",ucComNo);
*/

    ulComNo = 10;
    ulBaund = 115200;

     while(cResult!=0)
    {
        cResult = OpenCOMDevice(ulComNo,ulBaund);
    }
    // sent config to serial port by sanchiIMU
    data_to_send[0]=0xa5;data_to_send[1]=0x5a;data_to_send[2]=0x04;data_to_send[3]=0x01;data_to_send[4]=0x05;data_to_send[5]=0xaa;   //向100S发送开始指令
    //Usart2_Send(data_to_send,6);
    signed char sendfinish =1;
    sendfinish = SendUARTMessageLength( ulComNo,  data_to_send, 6);
    std::cout<<"sendfinish:";
    printf("send:%d\r\n",sendfinish);

    //read data
    while(1) {

        usLength = CollectUARTData(ulComNo, chrBuffer);
        printf("usLength is %d\r\n",usLength);

        if (usLength > 0) {
            //JY901.CopeSerialData(chrBuffer,usLength);
        }
        GetLocalTime(&lpsystime);
        cout<<lpsystime.wYear<<"year"<<lpsystime.wMonth<<"month"<<lpsystime.wDay<<"day week"<<lpsystime.wDayOfWeek<<" "<<lpsystime.wHour<<"hour"<<lpsystime.wMinute<<"min"<<lpsystime.wSecond<<"sec"<<lpsystime.wMilliseconds<<"ms"<<endl;

        Sleep(10);   //control the frequency,

        printf("charBuff is %x\r\n",chrBuffer[0]);
        if (chrBuffer[0] == 0xa5) {
            yaw = (chrBuffer[4] << 8) + chrBuffer[5];
            pitch = (chrBuffer[6] << 8) + chrBuffer[7];
            roll = (chrBuffer[8] << 8) + chrBuffer[9];
            alt = (chrBuffer[10] << 8) + chrBuffer[11];
            tempr = (chrBuffer[12] << 8) + chrBuffer[13];
            press = (chrBuffer[14] << 24) + (chrBuffer[15] << 16) + (chrBuffer[16] << 8) +
                    chrBuffer[17];
            default1 = (chrBuffer[18] << 8) + chrBuffer[19];

            ax = (chrBuffer[26] << 8) + chrBuffer[27];
            ay = (chrBuffer[28] << 8) + chrBuffer[29];
            az = (chrBuffer[30] << 8) + chrBuffer[31];
            gx = (chrBuffer[32] << 8) + chrBuffer[33];
            gy = (chrBuffer[34] << 8) + chrBuffer[35];
            gz = (chrBuffer[36] << 8) + chrBuffer[37];
            hx = (chrBuffer[38] << 8) + chrBuffer[39];
            hy = (chrBuffer[40] << 8) + chrBuffer[41];
            hz = (chrBuffer[42] << 8) + chrBuffer[43];

            longitud = (chrBuffer[50] << 24) + (chrBuffer[51] << 16) + (chrBuffer[52] << 8) +
                       chrBuffer[53];      //
            latitud = (chrBuffer[54] << 24) + (chrBuffer[55] << 16) + (chrBuffer[56] << 8) +
                      chrBuffer[57];
            speed = (chrBuffer[58] << 8) + chrBuffer[59];
            altitude = (chrBuffer[60] << 8) + chrBuffer[61];
            direction = (chrBuffer[62] << 8) + chrBuffer[63];
            lctNSWE = chrBuffer[64];

            year = chrBuffer[71];
            month = chrBuffer[72];
            day = chrBuffer[73];
            hour = chrBuffer[74];
            minute = chrBuffer[75];
            second = chrBuffer[76];
            default2 = chrBuffer[77];
            posslnum = chrBuffer[78];
            gpssta = chrBuffer[79];
            fixmode = chrBuffer[80];
            printf("minute is %d\r\n",minute);
            printf("yaw is %d\r\n",yaw);
            std::cout<<minute;
        }

/*
        if (usCnt++>=0)
        {
            usCnt=0;
            printf("Time:20%d-%d-%d %d:%d:%.3f\r\n",(short)JY901.stcTime.ucYear,(short)JY901.stcTime.ucMonth,
                   (short)JY901.stcTime.ucDay,(short)JY901.stcTime.ucHour,(short)JY901.stcTime.ucMinute,(float)JY901.stcTime.ucSecond+(float)JY901.stcTime.usMiliSecond/1000);

            printf("Acc:%.3f %.3f %.3f\r\n",(float)JY901.stcAcc.a[0]/32768*16,(float)JY901.stcAcc.a[1]/32768*16,(float)JY901.stcAcc.a[2]/32768*16);

            printf("Gyro:%.3f %.3f %.3f\r\n",(float)JY901.stcGyro.w[0]/32768*2000,(float)JY901.stcGyro.w[1]/32768*2000,(float)JY901.stcGyro.w[2]/32768*2000);

            printf("Angle:%.3f %.3f %.3f\r\n",(float)JY901.stcAngle.Angle[0]/32768*180,(float)JY901.stcAngle.Angle[1]/32768*180,(float)JY901.stcAngle.Angle[2]/32768*180);

            printf("Mag:%d %d %d\r\n",JY901.stcMag.h[0],JY901.stcMag.h[1],JY901.stcMag.h[2]);

            printf("Pressure:%lx Height%.2f\r\n",JY901.stcPress.lPressure,(float)JY901.stcPress.lAltitude/100);

            printf("DStatus:%d %d %d %d\r\n",JY901.stcDStatus.sDStatus[0],JY901.stcDStatus.sDStatus[1],JY901.stcDStatus.sDStatus[2],JY901.stcDStatus.sDStatus[3]);

            printf("Longitude:%ldDeg%.5fm Lattitude:%ldDeg%.5fm\r\n",JY901.stcLonLat.lLon/10000000,(double)(JY901.stcLonLat.lLon % 10000000)/1e5,JY901.stcLonLat.lLat/10000000,(double)(JY901.stcLonLat.lLat % 10000000)/1e5);

            printf("GPSHeight:%.1fm GPSYaw:%.1fDeg GPSV:%.3fkm/h\r\n\r\n",(float)JY901.stcGPSV.sGPSHeight/10,(float)JY901.stcGPSV.sGPSYaw/10,(float)JY901.stcGPSV.lGPSVelocity/1000);
        }
*/
    }
    return 0;
}


