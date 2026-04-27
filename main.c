#include <reg51.h>

#define LCD_DATA P2
sbit RS = P3^0;
sbit EN = P3^1;
sbit BUZZER = P1^3;
sbit S1 = P1^0;
sbit S2 = P1^1;
sbit S3 = P1^2;

unsigned char hh=12, mm=0, ss=0;
unsigned char ah=0, am=0;
unsigned char mode=0;
unsigned char alarm_on=0;
unsigned char t=0;
unsigned int i;

// Stopwatch variables
unsigned char sw_hh=0, sw_mm=0, sw_ss=0;
unsigned char sw_run=0;   // 0=stopped 1=running
unsigned char sw_tick=0;

void delay(unsigned int x){
    unsigned int i,j;
    for(i=0;i<x;i++)
        for(j=0;j<120;j++);
}

void cmd(unsigned char c){
    RS=0;
    LCD_DATA=c;
    EN=1; delay(1);
    EN=0; delay(2);
}

void ch(unsigned char c){
    RS=1;
    LCD_DATA=c;
    EN=1; delay(1);
    EN=0; delay(2);
}

void lcd_init(){
    delay(20);
    cmd(0x38);
    cmd(0x0C);
    cmd(0x06);
    cmd(0x01);
    delay(5);
}

void pos(unsigned char r, unsigned char c){
    if(r==0) cmd(0x80+c);
    else     cmd(0xC0+c);
}

void num(unsigned char n){
    ch((n/10)+'0');
    ch((n%10)+'0');
}

void timer_init(){
    TMOD=0x01;
    TH0=0x3C;
    TL0=0xB0;
    ET0=1;
    EA=1;
    TR0=1;
}

void timer0_isr() interrupt 1{
    TH0=0x3C;
    TL0=0xB0;

    t++;
    if(t<20) return;
    t=0;

    // Clock counting
    if(mode==0){
        ss++;
        if(ss==60){ ss=0; mm++; }
        if(mm==60){ mm=0; hh++; }
        if(hh==24){ hh=0;       }
    }

    // Alarm check
    if(mode==0){
        if(hh==ah && mm==am && ss==0){
            alarm_on=1;
        }
    }

    // Stopwatch counting
    if(sw_run==1){
        sw_ss++;
        if(sw_ss==60){ sw_ss=0; sw_mm++; }
        if(sw_mm==60){ sw_mm=0; sw_hh++; }
        if(sw_hh==24){ sw_hh=0;          }
    }
}

void main(){
    BUZZER=0;
    P1=0xFF;
    lcd_init();
    timer_init();

    while(1){

        // S1 = change mode
        if(S1==0){
            delay(50);
            if(S1==0){
                alarm_on=0;
                BUZZER=0;
                mode++;
                if(mode>5) mode=0;
                cmd(0x01);
                while(S1==0);
            }
        }

        // S2 = increment or stopwatch start
        if(S2==0){
            delay(50);
            if(S2==0){
                if(mode==1){ hh++; if(hh>=24) hh=0; }
                if(mode==2){ mm++; if(mm>=60) mm=0; }
                if(mode==3){ ah++; if(ah>=24) ah=0; }
                if(mode==4){ am++; if(am>=60) am=0; }
                // Stopwatch START
                if(mode==5){
                    sw_run=1;
                }
                while(S2==0);
            }
        }

        // S3 = stop buzzer or stopwatch stop/reset
        if(S3==0){
            delay(50);
            if(S3==0){
                alarm_on=0;
                BUZZER=0;
                // Stopwatch STOP and RESET
                if(mode==5){
                    sw_run=0;
                    sw_hh=0;
                    sw_mm=0;
                    sw_ss=0;
                }
                while(S3==0);
            }
        }

        // ALARM BEEPING
        if(alarm_on){
            pos(0,0);
            num(hh); ch(':'); num(mm); ch(':'); num(ss);
            pos(1,0);
            ch('S'); ch('T'); ch('O'); ch('P');
            ch('='); ch('S'); ch('3');

            for(i=0; i<50; i++){
                BUZZER=1;
                delay(5);
                BUZZER=0;
                delay(5);
                if(S3==0){
                    alarm_on=0;
                    BUZZER=0;
                    break;
                }
            }
        }

        // MODE 0 = normal clock
        else if(mode==0){
            pos(0,0);
            num(hh); ch(':'); num(mm); ch(':'); num(ss);
            pos(1,0);
            ch('A'); ch(':');
            num(ah); ch(':'); num(am);
        }

        // MODE 1 = set clock hour
        else if(mode==1){
            pos(0,0);
            ch('H'); ch('='); num(hh);
            pos(1,0);
            ch('S'); ch('1'); ch('-'); ch('>');
        }

        // MODE 2 = set clock minute
        else if(mode==2){
            pos(0,0);
            ch('M'); ch('='); num(mm);
            pos(1,0);
            ch('S'); ch('1'); ch('-'); ch('>');
        }

        // MODE 3 = set alarm hour
        else if(mode==3){
            pos(0,0);
            ch('A'); ch('H'); ch('='); num(ah);
            pos(1,0);
            ch('S'); ch('1'); ch('-'); ch('>');
        }

        // MODE 4 = set alarm minute
        else if(mode==4){
            pos(0,0);
            ch('A'); ch('M'); ch('='); num(am);
            pos(1,0);
            ch('S'); ch('1'); ch('-'); ch('>');
        }

        // MODE 5 = STOPWATCH
        else if(mode==5){
            pos(0,0);
            ch('S'); ch('W'); ch(':');
            num(sw_hh); ch(':'); num(sw_mm); ch(':'); num(sw_ss);
            pos(1,0);
            if(sw_run==1){
                // Showing running
                ch('R'); ch('U'); ch('N');
                ch(' ');
                ch('S'); ch('3'); ch('='); ch('R'); ch('S'); ch('T');
            } else {
                // Showing stopped
                ch('S'); ch('2'); ch('='); ch('G'); ch('O');
                ch(' ');
                ch('S'); ch('3'); ch('='); ch('R'); ch('S'); ch('T');
            }
        }

        delay(100);
    }
}
