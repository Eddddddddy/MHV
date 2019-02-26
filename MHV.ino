#include "Arduino.h"
#include "Wire.h"
#include "math.h"
//#include "MsTimer2.h"
//#include<SoftwareSerial.h>
//#include<JY901.h>//陀螺仪库
#include "Servo.h"
#include "../../../../Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/USBAPI.h"
//舵机库
#include "U8glib.h"
#include "../../../../Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/HardwareSerial.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI

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

#define Cam_1_Write_1 40
#define Cam_1_Write_2 41
#define Cam_1_Read_1 42
#define Cam_1_Read_2 43
#define Cam_1_Read_3 44
#define Cam_2_Write_1 45
#define Cam_2_Read_1 46
#define Cam_2_Read_2 47

#define Servo_1 6
#define Servo_2 7
#define Servo_3 8
#define Servo_4 9
//servo 1 抓取 0
//servo 2 抓取-举起 90-180
//servo 3 抓取准备 0
//servo 4 开 关 20-60

#define INI_Servo_1 90
#define INI_Servo_2 90
#define INI_Servo_3 0
#define INI_Servo_4 20


#define Track_1 30
#define Track_2 31
#define Track_3 32
#define Track_4 33
#define Track_5 34
#define Track_6 35
#define Track_7 36
#define Track_8 37
#define Track_9 38
//碰到黑线是1


Servo Hand_Servo_1;
Servo Hand_Servo_2;
Servo Hand_Servo_3;
Servo Hand_Servo_4;

//SoftwareSerial myserial(6,7);

//byte highByte = 0x00, lowByte = 0x00;
int MotorSpeed_1 = 0, MotorSpeed_2 = 0, MotorSpeed_3 = 0, MotorSpeed_4 = 0;
int val, p[4], c[4], q[4];
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

    INI_QR();

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

    pinMode(Track_1, INPUT);
    pinMode(Track_2, INPUT);
    pinMode(Track_3, INPUT);
    pinMode(Track_4, INPUT);
    pinMode(Track_5, INPUT);
    pinMode(Track_6, INPUT);
    pinMode(Track_7, INPUT);
    pinMode(Track_8, INPUT);
    pinMode(Track_9, INPUT);

    pinMode(Cam_1_Write_1, OUTPUT);
    pinMode(Cam_1_Write_2, OUTPUT);
    pinMode(Cam_1_Read_1, INPUT);
    pinMode(Cam_1_Read_2, INPUT);
    pinMode(Cam_1_Read_3, INPUT);
    pinMode(Cam_2_Write_1, OUTPUT);
    pinMode(Cam_2_Read_1, INPUT);
    pinMode(Cam_2_Read_2, INPUT);

    Hand_Servo_1.attach(Servo_1);
    Hand_Servo_2.attach(Servo_2);
    Hand_Servo_3.attach(Servo_3);
    Hand_Servo_4.attach(Servo_4);
    Hand_Servo_1.write(INI_Servo_1);//初始化角度
    Hand_Servo_2.write(INI_Servo_2);
    Hand_Servo_3.write(INI_Servo_3);
    Hand_Servo_4.write(INI_Servo_4);

}

//loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooop
void loop() {
    Auto_Move(1, 3, 3);
    Auto_Move(3, 2, 2);
    Auto_Move(2, 3, 4);
    Auto_Move(4, 2, 1);

}

void Auto_Move(int order, int line, int track) {//order:1->前 2->后 3->左 4->右
    int i = 1;
    if (order == 1) {
        while (1) {
            if (track == 3) {
                if (digitalRead(Track_8)) {
                    delay(50);
                    while (1) {
                        if (digitalRead(Track_8) == 0) {
                            break;
                        }
                    }
                    i++;
                }
            } else if (track == 4) {
                if (digitalRead(Track_3)) {
                    delay(50);
                    while (1) {
                        if (digitalRead(Track_3) == 0) {
                            break;
                        }
                    }
                    i++;
                }
            }
            if (i > line) {
                break;
            }
            Move_speed_adjust(140, 0, 80, 0);
        }
    } else if (order == 2) {
        while (1) {
            if (track == 3) {
                if (digitalRead(Track_7)) {
                    delay(50);
                    while (1) {
                        if (digitalRead(Track_7) == 0) {
                            break;
                        }
                    }
                    i++;
                }
            } else if (track == 4) {
                if (digitalRead(Track_4)) {
                    delay(50);
                    while (1) {
                        if (digitalRead(Track_4) == 0) {
                            break;
                        }
                    }
                    i++;
                }
            }
            if (i > line) {
                break;
            }
            Move_speed_adjust(-140, 0, 80, 0);
        }
    } else if (order == 3) {
        while (1) {
            if (track == 1) {
                if (digitalRead(Track_1)) {
                    delay(50);
                    while (1) {
                        if (digitalRead(Track_1) == 0) {
                            break;
                        }
                    }
                    i++;
                }
            } else if (track == 2) {
                if (digitalRead(Track_6)) {
                    delay(50);
                    while (1) {
                        if (digitalRead(Track_6) == 0) {
                            break;
                        }
                    }
                    i++;
                }
            }
            if (i > line) {
                break;
            }
            Move_speed_adjust(0, 140, 0, 60);
        }
    } else if (order == 4) {
        while (1) {
            if (track == 1) {
                if (digitalRead(Track_2)) {
                    delay(50);
                    while (1) {
                        if (digitalRead(Track_2) == 0) {
                            break;
                        }
                    }
                    i++;
                }
            } else if (track == 2) {
                if (digitalRead(Track_5)) {
                    delay(50);
                    while (1) {
                        if (digitalRead(Track_5) == 0) {
                            break;
                        }
                    }
                    i++;
                }
            }
            if (i > line) {
                break;
            }
            Move_speed_adjust(0, -140, 0, 60);
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
    State[4] = digitalRead(Track_5);
    State[5] = digitalRead(Track_6);
    State[6] = digitalRead(Track_7);
    State[7] = digitalRead(Track_8);
    if (x_speed >= 0) {
        MotorSpeed_1 = x_speed;
        MotorSpeed_4 = -x_speed;
        MotorSpeed_2 = 0;
        MotorSpeed_3 = 0;
        if (State[0] && !State[1]) {
            MotorSpeed_4 = -(x_speed - x_adjust);
            MotorSpeed_1 = x_speed + x_adjust;
        }
        if (!State[0] && State[1]) {
            MotorSpeed_4 = -(x_speed + x_adjust);
            MotorSpeed_1 = x_speed - x_adjust;
        }
    } else if (x_speed <= 0) {
        MotorSpeed_1 = x_speed;
        MotorSpeed_4 = -x_speed;
        MotorSpeed_2 = 0;
        MotorSpeed_3 = 0;
        if (State[5] && !State[6]) {
            MotorSpeed_4 = -(x_speed - x_adjust);
            MotorSpeed_1 = x_speed + x_adjust;
        }
        if (!State[5] && State[6]) {
            MotorSpeed_4 = -(x_speed + x_adjust);
            MotorSpeed_1 = x_speed - x_adjust;
        }
    } else if (y_speed >= 0) {
        MotorSpeed_2 = -y_speed;
        MotorSpeed_3 = y_speed;
        MotorSpeed_1 = 0;
        MotorSpeed_4 = 0;
        if (State[2] && !State[3]) {
            MotorSpeed_2 = -(y_speed - y_adjust);
            MotorSpeed_3 = y_speed + y_adjust;
        }
        if (!State[2] && State[3]) {
            MotorSpeed_2 = -(y_speed + y_adjust);
            MotorSpeed_3 = y_speed - y_adjust;
        }
    } else if (y_speed <= 0) {
        MotorSpeed_2 = -y_speed;
        MotorSpeed_3 = y_speed;
        MotorSpeed_1 = 0;
        MotorSpeed_4 = 0;
        if (State[7] && !State[8]) {
            MotorSpeed_2 = -(y_speed - y_adjust);
            MotorSpeed_3 = y_speed + y_adjust;
        }
        if (!State[7] && State[8]) {
            MotorSpeed_2 = -(y_speed + y_adjust);
            MotorSpeed_3 = y_speed - y_adjust;
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

void c1_p1() {
    Auto_Move(2, 1);
    Auto_Move(3, 3);
}

void c1_p2() {
    Auto_Move(1, 1);
    Auto_Move(3, 3);
}

void c1_p3() {
    Auto_Move(1, 2);
    Auto_Move(3, 3);
}

void c2_p1() {
    Auto_Move(2, 1);
    Auto_Move(3, 3);
}

void c2_p2() {
    Auto_Move(3, 3);
}

void c2_p3() {
    Auto_Move(1, 1);
    Auto_Move(3, 3);
}

void c3_p1() {
    Auto_Move(2, 2);
    Auto_Move(3, 3);
}

void c3_p2() {
    Auto_Move(2, 1);
    Auto_Move(3, 3);
}

void c3_p3() {
    Auto_Move(1, 1);
    Auto_Move(3, 3);
}

void Auto_put() {
    Move_noTrack(3, 300);
    Put_Ball_a();
    Put_Ball_b();
}

void Put_Ball_a() {
    Hand_Servo_1.write(90);
    Hand_Servo_2.write(120);
    Hand_Servo_3.write(0);
    Hand_Servo_4.write(60);
    delay(1000);
    Hand_Servo_1.write(179);
    delay(2000);
    Hand_Servo_2.write(0);
    delay(1000);
    Hand_Servo_4.write(20);
    delay(1000);
}

void Put_Ball_b() {
    Hand_Servo_2.write(120);
    delay(1000);
    Hand_Servo_1.write(90);
    delay(1000);
    Hand_Servo_2.write(90);
}

void Auto_Catch(int dir, int color) {//dir为l为左，r为右
    if (color == 1) {//红
        digitalWrite(Cam_1_Write_1, LOW);//cam_1_write_1 40
        digitalWrite(Cam_1_Write_2, HIGH);//41
    } else if (color == 2) {//绿
        digitalWrite(Cam_1_Write_1, HIGH);
        digitalWrite(Cam_1_Write_2, LOW);
    } else if (color == 3) {//蓝
        digitalWrite(Cam_1_Write_1, HIGH);
        digitalWrite(Cam_1_Write_2, HIGH);
    }
    while (1) {
        if (dir == 2) {
            Move_speed_adjust(-140, 0, 80, 0);
        } else if (dir == 1) {
            Move_speed_adjust(140, 0, 80, 0);
        }
        if (digitalRead(Cam_1_Read_1)) {//Cam_1_Read_1 42
            break;
        }
    }
    stop();
    Move_noTrack(4, 1000);
    Catch_Ball();
}

void Move_noTrack(int dir, int time) {
    if (dir == 1) {
        Move_speed_adjust(140, 0, 0, 0);
    } else if (dir == 2) {
        Move_speed_adjust(-140, 0, 0, 0);
    } else if (dir == 3) {
        Move_speed_adjust(0, 140, 0, 0);
    } else if (dir == 4) {
        Move_speed_adjust(0, -140, 0, 0);
    }
    delay(time);
    stop();
}

void Catch_Ball() {
    int i;
    Hand_Servo_1.write(90);
    Hand_Servo_4.write(20);//打开角度
    Hand_Servo_3.write(0);//收手爪
    Hand_Servo_2.write(120);//抬起角度
    Hand_Servo_1.write(0);//抓取位置
    delay(2000);
    Hand_Servo_2.write(90);//抬起后放回
    Hand_Servo_3.write(90);//放下手爪
    delay(1000);
    Hand_Servo_4.write(60);//抓
    delay(2000);
    Hand_Servo_3.write(0);//收手爪
    Hand_Servo_2.write(120);//抬起
    delay(1000);
    Hand_Servo_1.write(90);//到预设位置
    delay(2000);
}

int Cam_2_decode() {//在摄像头里写delay
    int a[2];
    a[0] = digitalRead(Cam_2_Read_1);
    a[1] = digitalRead(Cam_2_Read_2);
    if (!a[0] && a[1]) {
        return 1;
    } else if (a[0] && !a[1]) {
        return 2;
    } else if (a[0] && a[1]) {
        return 3;
    } else {
        return 0;
    }
}

void GoHome() {
    Auto_Move(2, 2);
    Auto_Move(4, 4);
    Move_noTrack(2, 1000);
    Move_noTrack(4, 1000);
    delay(10000000000);
}

void process() {
    //int c[4], q[4], p[4];
    Auto_Catch(2, q[1]);
    if (q[1] == c[1]) {
        c1_p1();
        p[1] = Cam_2_decode();
        if (p[1] == q[1]) {
            Auto_put();
            p[1] = 0;
        }
        Auto_Move(1, 1);
        p[2] = Cam_2_decode();
        p[3] = 6 - p[1] - p[2];
        if (q[1] == p[2]) {
            Auto_put();
            p[2] = 0;
            Auto_Move(4, 4);
        } else if (q[1] == p[3]) {
            Auto_Move(1, 1);
            Auto_put();
            p[3] = 0;
            if (q[2] == c[2]) {
                Auto_Move(4, 2);
                Auto_Move(2, 1);
                Auto_Move(4, 2);
            } else if (q[2] == c[3]) {
                Auto_Move(4, 4);
            }
        }
        if (q[2] == c[2]) {
            Catch_Ball();
            if (q[2] == p[1]) {
                c2_p1();
            } else if (q[2] == p[2]) {
                c2_p2();
            } else if (q[2] == p[3]) {
                c2_p3();
            }
            Auto_put();
            Auto_Move(4, 4);
            if (q[2] == p[3]) {
                Auto_Catch(2, q[3]);
            } else {
                Auto_Catch(1, q[3]);
            }
            if (q[3] == p[1]) {
                c3_p1();
            } else if (q[3] == p[2]) {
                c3_p2();
            } else if (q[3] == p[3]) {
                c3_p3();
            }
            Auto_put();
            Auto_Move(4, 2);
            if (q[3] == p[1]) { ;
            } else if (q[3] == p[2]) {
                Auto_Move(2, 1);
            } else if (q[3] == p[3]) {
                Auto_Move(2, 2);
            }
            GoHome();
        } else if (q[2] == c[3]) {
            if (p[3] == 0) {
                Auto_Catch(2, q[2]);
            } else {
                Auto_Catch(1, q[2]);
            }
            if (q[2] == p[1]) {
                c3_p1();
                Auto_put();
                Auto_Move(4, 2);
                Auto_Move(1, 1);
            } else if (q[2] == p[2]) {
                c3_p2();
                Auto_put();
                Auto_Move(4, 2);
            } else if (q[2] == p[3]) {
                c3_p3();
                Auto_put();
                Auto_Move(4, 2);
                Auto_Move(2, 1);
            }
            Auto_Move(4, 2);
            Catch_Ball();
            if (q[3] == p[1]) {
                c2_p1();
            } else if (q[3] == p[2]) {
                c2_p2();
            } else if (q[3] == p[3]) {
                c2_p3();
            }
            Auto_put();
            Auto_Move(4, 2);
            if (q[3] == p[1]) { ;
            } else if (q[3] == p[2]) {
                Auto_Move(2, 1);
            } else if (q[3] == p[3]) {
                Auto_Move(2, 2);
            }
            GoHome();
        }
    } else if (q[1] == c[2]) {
        c2_p1();
        p[1] = Cam_2_decode();
        if (p[1] == q[1]) {
            Auto_put();
            p[1] = 0;
        }
        Auto_Move(1, 1);
        p[2] = Cam_2_decode();
        p[3] = 6 - p[1] - p[2];
        if (q[1] == p[2]) {
            Auto_put();
        } else if (q[1] == p[3]) {
            Auto_Move(1, 1);
            Auto_put();
        }
        Auto_Move(4, 4);
        Auto_Catch(2, q[2]);
        if (q[2] == c[1]) {
            if (q[2] == p[1]) {
                c1_p1();
            } else if (q[2] == p[2]) {
                c1_p2();
            } else if (q[2] == p[3]) {
                c1_p3();
            }
            Auto_put();
            Auto_Move(4, 4);
            if (q[2] == p[3]) {
                Auto_Catch(2, q[3]);
            } else {
                Auto_Catch(1, q[3]);
            }
            if (q[3] == p[1]) {
                c3_p1();
            } else if (q[3] == p[2]) {
                c3_p2();
            } else if (q[3] == p[3]) {
                c3_p3();
            }
            Auto_put();
            Auto_Move(4, 2);
            if (q[3] == p[1]) { ;
            } else if (q[3] == p[2]) {
                Auto_Move(2, 1);
            } else if (q[3] == p[3]) {
                Auto_Move(2, 2);
            }
            GoHome();
        } else if (q[2] == c[3]) {
            if (q[2] == p[1]) {
                c3_p1();
            } else if (q[2] == p[2]) {
                c3_p2();
            } else if (q[2] == p[3]) {
                c3_p3();
            }
            Auto_put();
            Auto_Move(4, 4);
            if (q[2] == p[1]) {
                Auto_Catch(1, q[3]);
            } else {
                Auto_Catch(2, q[3]);
            }
            if (q[3] == p[1]) {
                c1_p1();
            } else if (q[3] == p[2]) {
                c1_p2();
            } else if (q[3] == p[3]) {
                c1_p3();
            }
            Auto_put();
            Auto_Move(4, 2);
            if (q[3] == p[1]) { ;
            } else if (q[3] == p[2]) {
                Auto_Move(2, 1);
            } else if (q[3] == p[3]) {
                Auto_Move(2, 2);
            }
            GoHome();
        }
    } else if (q[1] == c[3]) {
        c3_p1();
        p[3] = Cam_2_decode();
        if (q[1] == p[3]) {
            Auto_put();
            p[3] = 0;
        }
        Auto_Move(2, 1);
        p[2] = Cam_2_decode();
        p[1] = 6 - p[1] - p[2];
        if (q[1] == p[2]) {
            Auto_put();
            p[2] = 0;
            Auto_Move(4, 4);
        } else if (q[1] == p[1]) {
            Auto_Move(2, 1);
            Auto_put();
            p[1] = 0;
            if (q[2] == c[2]) {
                Auto_Move(4, 2);
                Auto_Move(1, 1);
                Auto_Move(4, 2);
            } else if (q[2] == c[3]) {
                Auto_Move(4, 4);
            }
        }
        if (q[2] == c[2]) {
            Catch_Ball();
            if (q[2] == p[1]) {
                c2_p1();
            } else if (q[2] == p[2]) {
                c2_p2();
            } else if (q[2] == p[3]) {
                c2_p3();
            }
            Auto_put();
            Auto_Move(4, 4);
            if (q[2] == p[3]) {
                Auto_Catch(2, q[3]);
            } else {
                Auto_Catch(1, q[3]);
            }
            if (q[3] == p[1]) {
                c1_p1();
            } else if (q[3] == p[2]) {
                c1_p2();
            } else if (q[3] == p[3]) {
                c1_p3();
            }
            Auto_put();
            Auto_Move(4, 2);
            if (q[3] == p[1]) { ;
            } else if (q[3] == p[2]) {
                Auto_Move(2, 1);
            } else if (q[3] == p[3]) {
                Auto_Move(2, 2);
            }
            GoHome();
        } else if (q[2] == c[1]) {
            if (p[1] == 0) {
                Auto_Catch(1, q[2]);
            } else {
                Auto_Catch(2, q[2]);
            }
            if (q[2] == p[1]) {
                c1_p1();
                Auto_put();
                Auto_Move(4, 2);
                Auto_Move(1, 1);
            } else if (q[2] == p[2]) {
                c1_p2();
                Auto_put();
                Auto_Move(4, 2);
            } else if (q[2] == p[3]) {
                c1_p3();
                Auto_put();
                Auto_Move(4, 2);
                Auto_Move(2, 1);
            }
            Auto_Move(4, 2);
            Catch_Ball();
            if (q[3] == p[1]) {
                c2_p1();
            } else if (q[3] == p[2]) {
                c2_p2();
            } else if (q[3] == p[3]) {
                c2_p3();
            }
            Auto_put();
            Auto_Move(4, 2);
            if (q[3] == p[1]) { ;
            } else if (q[3] == p[2]) {
                Auto_Move(2, 1);
            } else if (q[3] == p[3]) {
                Auto_Move(2, 2);
            }
            GoHome();
        }
    }
}

void Rec_QR() {
    int temp;
    temp = (int) Serial3.read();
    q[3] = temp % 10;
    q[2] = temp % 100 / 10;
    q[1] = temp % 1000 / 100;
    Print_QR((String) temp);
}

void Print_QR(String printStr) {
    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_ncenB14);
        u8g.setPrintPos(0, 20);
        u8g.print(printStr);
    } while (u8g.nextPage());
}

int Cam_1_decode() {
    int a[3];
    a[0] = digitalRead(Cam_1_Read_1);
    a[1] = digitalRead(Cam_1_Read_2);
    a[2] = digitalRead(Cam_1_Read_3);
    if (!a[0] && !a[1] && a[2])return 123;
    else if (!a[0] && a[1] && !a[2])return 132;
    else if (!a[0] && a[1] && a[2])return 213;
    else if (a[0] && !a[1] && !a[2])return 231;
    else if (a[0] && !a[1] && a[2])return 312;
    else if (a[0] && a[1] && !a[2])return 321;
    return 123;
}

void Begin() {
    Move_noTrack(1, 1000);
    Auto_Move(3, 2);
    Auto_Move(1, 4);
    Cam_1_decode();

    Rec_QR();
}

void INI_QR() {
    unsigned char hexData[9] = {0x7E, 0x00, 0x08, 0x01, 0x00, 0x02, 0x01, 0xAB, 0xCD};
    Serial1.write(hexData, 9);
    delay(50);
    while (Serial3.available()) {
        Serial3.read();
    }
}