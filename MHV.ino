#include "Arduino.h"
#include "Wire.h"
#include "math.h"
//#include "MsTimer2.h"
//#include<SoftwareSerial.h>
//#include<JY901.h>//陀螺仪库
#include "Servo.h"
//舵机库
//#include "U8glib.h"
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

#define MecMIX(X, Y, Z) (x*X+y*Y+z*Z)

#define Motor_PWM_1 2
#define Motor_PWM_2 3
#define Motor_PWM_3 4
#define Motor_PWM_4 5
#define Motor_A1 22
#define Motor_B1 23
#define Motor_A2 24
#define Motor_B2 25
#define Motor_A3 26
#define Motor_B3 27
#define Motor_A4 28
#define Motor_B4 29
#define speed1 100

#define Cam_1L 50
#define Cam_1R 51
#define Cam_2L 52
#define Cam_2R 53
#define Cam_3L 46
#define Cam_3R 47
#define Cam_4L 48
#define Cam_4R 49

#define Servo_1 30
#define Servo_2 31
#define Servo_3 32
#define Servo_4 33
//servo 1 抓取 0
//servo 2 抓取-举起 90-180
//servo 3 抓取准备 0
//servo 4 开 关 20-60

#define INI_Servo_1 90
#define INI_Servo_2 90
#define INI_Servo_3 0
#define INI_Servo_4 20

#define ca1 34
#define ca2 35
#define ca3 36

#define ca4 37
#define ca5 38
#define ca6 39
#define ca7 40
#define ca8 41
#define ca9 42

#define ca10 43

#define Track_1 37
#define Track_2 38
#define Track_3 39
#define Track_4 40
//碰到黑线是1

#define modeee 45
#define tracb 44

//#define ks1031 0xe8>>1
//#define ks1032 0xe8>>1//需更改地址
//#define Reg 0x02
//#define NC 0x72

Servo Hand_Servo_1;
Servo Hand_Servo_2;
Servo Hand_Servo_3;
Servo Hand_Servo_4;

//SoftwareSerial myserial(6,7);

//byte highByte = 0x00, lowByte = 0x00;
int MotorSpeed_1 = 0, MotorSpeed_2 = 0, MotorSpeed_3 = 0, MotorSpeed_4 = 0;
int xxx = 0, yyy = 0, aa, bb, val, val1, val2, val3, i = 0, j = 5, a0, a1, a2, a3, b0, b1, b2, b3, jj = 0, ii, b[4], c[4], u, ooooo;
long int iiii;

//double zzz;


void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);
    Serial3.begin(9600);
    //softSerial.begin(115200);

    while (Serial.read() >= 0) {}
    while (Serial1.read() >= 0) {}
    while (Serial2.read() >= 0) {}
    while (Serial3.read() >= 0) {}

    //MsTimer2::set(1, flash);

    pinMode(Motor_PWM_1, OUTPUT); //定义电机针脚
    pinMode(Motor_PWM_2, OUTPUT);
    pinMode(Motor_PWM_3, OUTPUT);
    pinMode(Motor_PWM_4, OUTPUT);
    pinMode(Motor_A1, OUTPUT);
    pinMode(Motor_B1, OUTPUT);
    pinMode(Motor_A2, OUTPUT);
    pinMode(Motor_B2, OUTPUT);
    pinMode(Motor_A3, OUTPUT);
    pinMode(Motor_B3, OUTPUT);
    pinMode(Motor_A4, OUTPUT);
    pinMode(Motor_B4, OUTPUT);

    pinMode(Cam_1L, INPUT);
    pinMode(Cam_1R, INPUT);
    pinMode(Cam_2L, INPUT);
    pinMode(Cam_2R, INPUT);
    pinMode(Cam_3L, INPUT);
    pinMode(Cam_3R, INPUT);
    pinMode(Cam_4L, INPUT);
    pinMode(Cam_4R, INPUT);
    //movexyz(0, 0, 0);

    pinMode(ca1, OUTPUT);
    pinMode(ca2, OUTPUT);
    pinMode(ca3, OUTPUT);

    pinMode(ca4, INPUT);
    pinMode(ca5, INPUT);
    pinMode(ca6, INPUT);
    pinMode(ca7, INPUT);
    pinMode(ca8, INPUT);
    pinMode(ca9, INPUT);

    pinMode(ca10, OUTPUT);

    Hand_Servo_1.attach(Servo_1);
    Hand_Servo_2.attach(Servo_2);
    Hand_Servo_3.attach(Servo_3);
    Hand_Servo_4.attach(Servo_4);
    Hand_Servo_1.write(INI_Servo_1);//初始化角度
    Hand_Servo_2.write(INI_Servo_2);
    Hand_Servo_3.write(INI_Servo_3);
    Hand_Servo_4.write(INI_Servo_4);


    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(8, OUTPUT);
    digitalWrite(8, HIGH);


}

//loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooop
void loop() {
Auto_Move(1,2);
}

void Auto_Move(int order, int line) {//order:1->前 2->后 3->左 4->右
    i = 1;
    if (order == 1) {
        while (1) {
            if (digitalRead(Track_4)) {
                    i++;
                    if (i > line) {
                        break;
                    }
                }
            Move_speed_adjust(140, 0, 60, 0);
        }
    } else if (order == 2) {
        while (1) {
            if (digitalRead(Track_3)) {
                    i++;
                    if (i > line) {
                        break;
                    }
            }
            Move_speed_adjust(-140, 0, 60, 0);
        }
    } else if (order == 3) {
        while (1) {
            if (digitalRead(Track_2)) {
                    i++;
                    if (i > line) {
                        break;
                    }
            }
            Move_speed_adjust(0, 140, 0, 30);
        }
    } else if (order == 4) {
        while (1) {
            if (digitalRead(Track_1)) {
                    i++;
                    if (i > line) {
                        break;
                    }
            }
            Move_speed_adjust(0, -140, 0, 30);
        }
    }
    stop();
}
void Move_speed_adjust(int x_speed, int y_speed, int x_adjust, int y_adjust) {
    int State[8];
    State[0] = digitalRead(Track_1);//碰到黑线是1
    State[1] = digitalRead(Track_2);
    State[2] = digitalRead(Track_3);
    State[3] = digitalRead(Track_4);
    State[4] = digitalRead(Cam_3L);
    State[5] = digitalRead(Cam_3R);
    State[6] = digitalRead(Cam_4L);
    State[7] = digitalRead(Cam_4R);

    if (x_speed != 0) {
        MotorSpeed_1 = x_speed;
        MotorSpeed_4 = -x_speed;
        MotorSpeed_2 = 0;
        MotorSpeed_3 = 0;
        if (State[0]&&!State[1]) {
            MotorSpeed_4 = -(x_speed + x_adjust);
            MotorSpeed_1 = x_speed - x_adjust;
        }
        if (!State[0]&&State[1]) {
            MotorSpeed_1 = x_speed + x_adjust;
            MotorSpeed_4 = -(x_speed - x_adjust);
        }
    } else if (y_speed != 0) {
        MotorSpeed_2 = -y_speed;
        MotorSpeed_3 = y_speed;
        MotorSpeed_1 = 0;
        MotorSpeed_4 = 0;
        if (State[2]&&!State[3]) {
            MotorSpeed_2 = -(y_speed + y_adjust);
            MotorSpeed_3 = y_speed - y_adjust;
        }
        if (!State[2]&&State[3]) {
            MotorSpeed_2 = -(y_speed - y_adjust);
            MotorSpeed_3 = y_speed + y_adjust;
        }
    }


    Move_4_speed(MotorSpeed_1, MotorSpeed_2, MotorSpeed_3, MotorSpeed_4);

}
void Move_4_speed(int Speed_1, int Speed_2, int Speed_3, int Speed_4) {

    if (Speed_1 > 0)//判断正反转
    {
        digitalWrite(Motor_A1, LOW);
        digitalWrite(Motor_B1, HIGH);
        analogWrite(Motor_PWM_1, abs(Speed_1));
    } else {
        digitalWrite(Motor_A1, HIGH);
        digitalWrite(Motor_B1, LOW);
        analogWrite(Motor_PWM_1, abs(Speed_1));
    }


    if (Speed_2 > 0)//以下三个轮子同理
    {
        digitalWrite(Motor_A2, LOW);
        digitalWrite(Motor_B2, HIGH);
        analogWrite(Motor_PWM_2, abs(Speed_2));
    } else {
        digitalWrite(Motor_A2, HIGH);
        digitalWrite(Motor_B2, LOW);
        analogWrite(Motor_PWM_2, abs(Speed_2));
    }

    if (Speed_3 > 0) {
        digitalWrite(Motor_A3, LOW);
        digitalWrite(Motor_B3, HIGH);
        analogWrite(Motor_PWM_3, abs(Speed_3));
    } else {
        digitalWrite(Motor_A3, HIGH);
        digitalWrite(Motor_B3, LOW);
        analogWrite(Motor_PWM_3, abs(Speed_3));
    }

    if (Speed_4 > 0) {
        digitalWrite(Motor_A4, LOW);
        digitalWrite(Motor_B4, HIGH);
        analogWrite(Motor_PWM_4, abs(Speed_4));
    } else {
        digitalWrite(Motor_A4, HIGH);
        digitalWrite(Motor_B4, LOW);
        analogWrite(Motor_PWM_4, abs(Speed_4));
    }
}
void stop() {

    MotorSpeed_1 = 0;
    MotorSpeed_2 = 0;
    MotorSpeed_3 = 0;
    MotorSpeed_4 = 0;


    if (MotorSpeed_1 > 0)//判断正反转
    {
        digitalWrite(Motor_A1, LOW);
        digitalWrite(Motor_B1, HIGH);
        analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
    } else {
        digitalWrite(Motor_A1, HIGH);
        digitalWrite(Motor_B1, LOW);
        analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
    }


    if (MotorSpeed_2 > 0)//以下三个轮子同理
    {
        digitalWrite(Motor_A2, LOW);
        digitalWrite(Motor_B2, HIGH);
        analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
    } else {
        digitalWrite(Motor_A2, HIGH);
        digitalWrite(Motor_B2, LOW);
        analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
    }

    if (MotorSpeed_3 > 0) {
        digitalWrite(Motor_A3, LOW);
        digitalWrite(Motor_B3, HIGH);
        analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
    } else {
        digitalWrite(Motor_A3, HIGH);
        digitalWrite(Motor_B3, LOW);
        analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
    }

    if (MotorSpeed_4 > 0) {
        digitalWrite(Motor_A4, LOW);
        digitalWrite(Motor_B4, HIGH);
        analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
    } else {
        digitalWrite(Motor_A4, HIGH);
        digitalWrite(Motor_B4, LOW);
        analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
    }
}