#include <wiringPi.h>
#include <stdio.h>

/*
https://github.com/OsandaMalith/
*/

#define   SDI   0
#define   RCLK  1
#define   SRCLK 2

unsigned char SegCode[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x80};

void init(void){
        pinMode(SDI, OUTPUT);
        pinMode(RCLK, OUTPUT);
        pinMode(SRCLK, OUTPUT);

        digitalWrite(SDI, 0);
        digitalWrite(RCLK, 0);
        digitalWrite(SRCLK, 0);
}

void shift(unsigned char dat){
        int i;

        for(i=0;i<8;i++){
                digitalWrite(SDI, 0x80 & (dat << i));
                digitalWrite(SRCLK, 1);
                delay(1);
                digitalWrite(SRCLK, 0);
        }       digitalWrite(RCLK, 1);
                delay(1);
                digitalWrite(RCLK, 0);
}

int main(void){
        int i;

        if(!wiringPiSetup()) printf("Error Occured");
        init();
        printf("http://osandamalith.wordpress.com");
        while(1) for(i=0;i<17;i++){
                shift(SegCode[i]);
                delay(500);
        }

        return 0;
}


