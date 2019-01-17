#include<Wire.h>
#include<math.h>
#include <MsTimer2.h>
//#include<SoftwareSerial.h>
//#include<JY901.h>//陀螺仪库
#include <Servo.h>//舵机库
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
#define MecMIX(X,Y,Z) (x*X+y*Y+z*Z)

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
int xxx = 0, yyy = 0, aa, bb, val, val1, val2, val3, i = 0, j = 5, a0, a1, a2, a3, b0, b1, b2, b3, jj = 0, ii, b[4], c[4], u,ooooo;
long int iiii;

//double zzz;


void setup()
{
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

    if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
        u8g.setColorIndex(255);     // white
    }
    else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
        u8g.setColorIndex(3);         // max intensity
    }
    else if ( u8g.getMode() == U8G_MODE_BW ) {
        u8g.setColorIndex(1);         // pixel on
    }
    else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
        u8g.setHiColorByRGB(255, 255, 255);
    }


    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(8, OUTPUT);
    digitalWrite(8, HIGH);
    delay(300);

}
//loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooop
void loop()
{

}


void automove(int order, int line)
{
    digitalWrite(8, LOW);
    i = 1;
    if (order == 1)
    {
        Serial1.write("1");
        Serial2.write("2");
        //i = 0;
        delay(2000);

        while (1)
        {
            if (Serial2.available())
            {
                if (Serial2.read() == '0')
                {

                    i++;
                    if (i > line)
                    {
                        break;
                    }
                    Serial2.write("2");
                }
            }
            movexyz3(140, 0, 60, 0);
        }
        stop();
        Serial1.write("9");
    }
    else if (order == 2)
    {
        Serial1.write("1");
        Serial2.write("3");
        delay(2000);
        //i = 0;
        while (1)
        {
            if (Serial2.available())
            {
                if (Serial2.read() == '0')
                {

                    i++;
                    if (i > line)
                    {
                        break;
                    }
                    Serial2.write("3");
                }
            }
            movexyz3(-140, 0, 60, 0);
        }
        stop();
        Serial1.write("9");
    }
    else if (order == 3)
    {
        Serial1.write("2");
        Serial2.write("1");
        delay(2000);
        // i = 0;
        while (1)
        {
            if (Serial1.available())
            {
                if (Serial1.read() == '0')
                {

                    i++;
                    if (i > line)
                    {
                        break;
                    }
                    Serial1.write("2");
                }
            }
            movexyz3(0, 140, 0, 30);
        }
        stop();
        Serial2.write("9");
    }
    else if (order == 4)
    {
        Serial1.write("3");
        Serial2.write("1");
        delay(2000);
        // i = 0;
        while (1)
        {
            if (Serial1.available())
            {
                if (Serial1.read() == '0')
                {
                    i++;
                    if (i > line)
                    {
                        break;
                    }

                    Serial1.write("3");
                }
            }
            movexyz3(0, -140, 0, 30);
        }
        stop();
        Serial2.write("9");
    }
}

void catchball()//抓手，抓取物料，目前写的是一个舵机控制抓手，后期应改为两个舵机控制
{
    int i;
    Hand_Servo_1.write(90);
    Hand_Servo_4.write(20);//打开角度
    //delay(3000);
    Hand_Servo_3.write(0);//收手爪
    //delay(3000);
    Hand_Servo_2.write(120);//抬起角度
    // delay(3000);
    Hand_Servo_1.write(0);//抓取位置
    delay(2000);
    Hand_Servo_2.write(90);//抬起后放回
    //delay(1000);
    Hand_Servo_3.write(90);//放下手爪
    delay(1000);
    Hand_Servo_4.write(60);//抓
    delay(2000);

    //  for (i = 0; i < 180; i++)
    //  {
    //    Hand_Servo_1.write(i);
    //    delay(50);
    //  }
    Hand_Servo_3.write(0);//收手爪
    //delay(1000);
    Hand_Servo_2.write(120);//抬起
    delay(1000);
    Hand_Servo_1.write(90);//到预设位置
    delay(2000);
}

void putballa()//舱门打开
{
    int i;
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

void putballb()//舱门关闭
{
    Hand_Servo_2.write(120);
    delay(1000);
    Hand_Servo_1.write(90);
    delay(1000);
    Hand_Servo_2.write(90);
}
//void movexyz4()
//{
//  int dataz[2];
//  dataz[0] = digitalRead(traca);
//  dataz[1] = digitalRead(tracb);
//  if ((!dataz[0] && !dataz[1]) || (dataz[0] && dataz[1]))
//  {
//    moveee(0, -120, 120, 0);
//  }
//  if (!dataz[0] && dataz[1])
//  {
//    moveee(-70, 120, 120, 70);
//  }
//  if (dataz[0] && !dataz[1])
//  {
//    moveee(70, 120, 120, -70);
//  }
//}

void movexyz3(int x, int y, int xx, int yy)
{
    int data[8];
    data[0] = digitalRead(Cam_1L);
    data[1] = digitalRead(Cam_1R);
    data[2] = digitalRead(Cam_2L);
    data[3] = digitalRead(Cam_2R);
    data[4] = digitalRead(Cam_3L);
    data[5] = digitalRead(Cam_3R);
    data[6] = digitalRead(Cam_4L);
    data[7] = digitalRead(Cam_4R);

    if (x > 0)
    {
        MotorSpeed_1 = x;
        MotorSpeed_4 = -x;
        MotorSpeed_2 = 0;
        MotorSpeed_3 = 0;
        if (data[2])
        {
            MotorSpeed_2 = -70;
            MotorSpeed_3 = 70;
        }
        if (data[3])
        {
            MotorSpeed_2 = 70;
            MotorSpeed_3 = -70;
        }
        if (data[0])
        {
            MotorSpeed_4 = -(x + xx);
            MotorSpeed_1 = x - xx;
        }
        if (data[1])
        {
            MotorSpeed_1 = x + xx;
            MotorSpeed_4 = -(x - xx);
        }
    }
    if (x < 0)
    {
        MotorSpeed_1 = x;
        MotorSpeed_4 = -x;
        MotorSpeed_2 = 0;
        MotorSpeed_3 = 0;
        if (data[2])
        {
            MotorSpeed_2 = -70;
            MotorSpeed_3 = 70;
        }
        if (data[3])
        {
            MotorSpeed_2 = 70;
            MotorSpeed_3 = -70;
        }
        if (data[0])
        {
            MotorSpeed_4 = -(x + xx);
            MotorSpeed_1 = x - xx;
        }
        if (data[1])
        {
            MotorSpeed_1 = x + xx;
            MotorSpeed_4 = -(x - xx);
        }
    }
    else if (y != 0)
    {
        MotorSpeed_2 = -y;
        MotorSpeed_3 = y;
        MotorSpeed_1 = 0;
        MotorSpeed_4 = 0;


        if (data[4])
        {
            MotorSpeed_1 = -40;
            MotorSpeed_4 = 40;
        }
        if (data[5])
        {
            MotorSpeed_1 = 40;
            MotorSpeed_4 = -40;
        }
        if (data[6])
        {
            MotorSpeed_2 = -(y + yy);
            MotorSpeed_3 = y - yy;
        }
        if (data[7])
        {
            MotorSpeed_2 = -(y - yy);
            MotorSpeed_3 = y + yy;
        }
    }



    if (MotorSpeed_1 > 0)//判断正反转
    {
        digitalWrite(Motor_A1, LOW);
        digitalWrite(Motor_B1, HIGH);
        analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
    }
    else
    {
        digitalWrite(Motor_A1, HIGH);
        digitalWrite(Motor_B1, LOW);
        analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
    }


    if (MotorSpeed_2 > 0)//以下三个轮子同理
    {
        digitalWrite(Motor_A2, LOW);
        digitalWrite(Motor_B2, HIGH);
        analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
    }
    else
    {
        digitalWrite(Motor_A2, HIGH);
        digitalWrite(Motor_B2, LOW);
        analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
    }

    if (MotorSpeed_3 > 0)
    {
        digitalWrite(Motor_A3, LOW);
        digitalWrite(Motor_B3, HIGH);
        analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
    }
    else
    {
        digitalWrite(Motor_A3, HIGH);
        digitalWrite(Motor_B3, LOW);
        analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
    }

    if (MotorSpeed_4 > 0)
    {
        digitalWrite(Motor_A4, LOW);
        digitalWrite(Motor_B4, HIGH);
        analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
    }
    else
    {
        digitalWrite(Motor_A4, HIGH);
        digitalWrite(Motor_B4, LOW);
        analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
    }
}
void move_4_speed(int motorspeed1, int motorspeed2, int motorspeed3, int motorspeed4)
{




    if (motorspeed1 > 0)//判断正反转
    {
        digitalWrite(Motor_A1, LOW);
        digitalWrite(Motor_B1, HIGH);
        analogWrite(Motor_PWM_1, abs(motorspeed1));
    }
    else
    {
        digitalWrite(Motor_A1, HIGH);
        digitalWrite(Motor_B1, LOW);
        analogWrite(Motor_PWM_1, abs(motorspeed1));
    }


    if (motorspeed2 > 0)//以下三个轮子同理
    {
        digitalWrite(Motor_A2, LOW);
        digitalWrite(Motor_B2, HIGH);
        analogWrite(Motor_PWM_2, abs(motorspeed2));
    }
    else
    {
        digitalWrite(Motor_A2, HIGH);
        digitalWrite(Motor_B2, LOW);
        analogWrite(Motor_PWM_2, abs(motorspeed2));
    }

    if (motorspeed3 > 0)
    {
        digitalWrite(Motor_A3, LOW);
        digitalWrite(Motor_B3, HIGH);
        analogWrite(Motor_PWM_3, abs(motorspeed3));
    }
    else
    {
        digitalWrite(Motor_A3, HIGH);
        digitalWrite(Motor_B3, LOW);
        analogWrite(Motor_PWM_3, abs(motorspeed3));
    }

    if (motorspeed4 > 0)
    {
        digitalWrite(Motor_A4, LOW);
        digitalWrite(Motor_B4, HIGH);
        analogWrite(Motor_PWM_4, abs(motorspeed4));
    }
    else
    {
        digitalWrite(Motor_A4, HIGH);
        digitalWrite(Motor_B4, LOW);
        analogWrite(Motor_PWM_4, abs(motorspeed4));
    }
}

void stop()
{

    MotorSpeed_1 = 0;
    MotorSpeed_2 = 0;
    MotorSpeed_3 = 0;
    MotorSpeed_4 = 0;


    if (MotorSpeed_1 > 0)//判断正反转
    {
        digitalWrite(Motor_A1, LOW);
        digitalWrite(Motor_B1, HIGH);
        analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
    }
    else
    {
        digitalWrite(Motor_A1, HIGH);
        digitalWrite(Motor_B1, LOW);
        analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
    }


    if (MotorSpeed_2 > 0)//以下三个轮子同理
    {
        digitalWrite(Motor_A2, LOW);
        digitalWrite(Motor_B2, HIGH);
        analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
    }
    else
    {
        digitalWrite(Motor_A2, HIGH);
        digitalWrite(Motor_B2, LOW);
        analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
    }

    if (MotorSpeed_3 > 0)
    {
        digitalWrite(Motor_A3, LOW);
        digitalWrite(Motor_B3, HIGH);
        analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
    }
    else
    {
        digitalWrite(Motor_A3, HIGH);
        digitalWrite(Motor_B3, LOW);
        analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
    }

    if (MotorSpeed_4 > 0)
    {
        digitalWrite(Motor_A4, LOW);
        digitalWrite(Motor_B4, HIGH);
        analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
    }
    else
    {
        digitalWrite(Motor_A4, HIGH);
        digitalWrite(Motor_B4, LOW);
        analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
    }
}




//void numy(int i, int speed)
//{
//  int temp, m = 0, n = 0;
//  while (1)
//  {
//    movexyz3(0, speed, 0, 20);
//    //temp = digitalRead(trac3);
//    //tempy[1] = digitalRead(trac4);
//    if (digitalRead(trac3))
//    {
//      delay(50);
//      while (1)
//      {
//        if (digitalRead(trac3) == 0)
//        {
//          break;
//        }
//      }
//      m++;
//    }
//    if (m >= i)
//    {
//      break;
//    }
//  }
//}
//
//void numx(int i, int speed)
//{
//  int temp, m = 0, n = 0;
//  while (1)
//  {
//    movexyz3(speed, 0, 20, 0);
//    //tempx[0] = digitalRead(trac1);
//    //tempx[1] = digitalRead(trac2);
//    if (digitalRead(trac1))
//    {
//      while (1)
//      {
//        if (digitalRead(trac1) == 0)
//        {
//          break;
//        }
//      }
//      m++;
//    }
//    if (m >= (i + i))
//    {
//      break;
//    }
//  }
//}

//void movexyz2(int x, int y, int xx, int yy)
//{
//  int datax[8],data;
////  datax[0] = digitalRead(trac1);
////  datax[1] = digitalRead(trac2);
////  datax[2] = digitalRead(trac3);
////  datax[3] = digitalRead(trac4);
////  datax[4] = digitalRead(trac5);
////  datax[5] = digitalRead(trac6);
//
//  data=Serial2.read();
//
//  if (x != 0)
//  {
//    MotorSpeed_1 = x;
//    MotorSpeed_4 = x;
//    MotorSpeed_2 = 0;
//    MotorSpeed_3 = 0;
//    if ((!datax[0] && !datax[1]) || (datax[0] && datax[1]))
//    {
//      ;
//    }
//    if (datax[0] && !datax[1])
//    {
//      MotorSpeed_4 = x + xx;
//    }
//    if (!datax[0] && datax[1])
//    {
//      MotorSpeed_1 = x + xx;
//    }
//  }
//  else if (y != 0)
//  {
//    MotorSpeed_2 = y;
//    MotorSpeed_3 = y;
//    MotorSpeed_1 = 0;
//    MotorSpeed_4 = 0;
//    if ((!datax[2] && !datax[3]) || (datax[2] && datax[3]))
//    {
//      ;
//    }
//    if (datax[2] && !datax[3])
//    {
//      MotorSpeed_2 = y + yy;
//    }
//    if (!datax[2] && datax[3])
//    {
//      MotorSpeed_3 = y + yy;
//    }
//  }
//
//
//
//  if (MotorSpeed_1 > 0)//判断正反转
//  {
//    digitalWrite(Motor_A1, LOW);
//    digitalWrite(Motor_B1, HIGH);
//    analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
//  }
//  else
//  {
//    digitalWrite(Motor_A1, HIGH);
//    digitalWrite(Motor_B1, LOW);
//    analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
//  }
//
//
//  if (MotorSpeed_2 > 0)//以下三个轮子同理
//  {
//    digitalWrite(Motor_A2, LOW);
//    digitalWrite(Motor_B2, HIGH);
//    analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
//  }
//  else
//  {
//    digitalWrite(Motor_A2, HIGH);
//    digitalWrite(Motor_B2, LOW);
//    analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
//  }
//
//  if (MotorSpeed_3 > 0)
//  {
//    digitalWrite(Motor_A3, LOW);
//    digitalWrite(Motor_B3, HIGH);
//    analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
//  }
//  else
//  {
//    digitalWrite(Motor_A3, HIGH);
//    digitalWrite(Motor_B3, LOW);
//    analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
//  }
//
//  if (MotorSpeed_4 > 0)
//  {
//    digitalWrite(Motor_A4, LOW);
//    digitalWrite(Motor_B4, HIGH);
//    analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
//  }
//  else
//  {
//    digitalWrite(Motor_A4, HIGH);
//    digitalWrite(Motor_B4, LOW);
//    analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
//  }
//}

//void trac12(int speedx)
//{
//  int datax[2];
//  datax[0] = digitalRead(trac1);
//  datax[1] = digitalRead(trac2);
//  if ((!datax[0] && !datax[1]) || (datax[0] && datax[1]))
//  {
//    movexyz(speedx, 0, 0);
//  }
//  if (datax[0] && !datax[1])
//  {
//    movexyz(speedx, 0, 150);
//  }
//  if (!datax[0] && datax[1])
//  {
//    movexyz(speedx, 0, -150);
//  }
//}
//
//void trac34(int speedy)
//{
//  int datay[4];
//  datay[0] = digitalRead(trac3);
//  datay[1] = digitalRead(trac4);
//  // datay[2]=digitalRead(trac5);
//  //  datay[3]=digitalRead(trac6);
//  if ((!datay[0] && !datay[1]) || (datay[0] && datay[1])) //||(datay[2]&&datay[3])||(!datay[2]&&!datay[3])
//  {
//    movexyz(0, speedy, 0);
//  }
//  if ((datay[0] && !datay[1])) //||(datay[2]&&!datay[3])
//  {
//    movexyz(0, speedy, -50);
//    delay(0);
//  }
//  if (!datay[0] && datay[1]) //||(!datay[2]&&datay[3])
//  {
//    movexyz(0, speedy, 50);
//    delay(0);
//  }
//}


//void movexyz(int x, int y, int z)//麦轮移动，xy为xy轴方向移动速度
//{
//
//  //double z = Serial.println((float)JY901.stcAngle.Angle[2]/32768*180)-zzz;//航向轴，陀螺仪数据
//
//  MotorSpeed_1 = MecMIX(-1, +1, +1);
//  MotorSpeed_2 = MecMIX(+1, +1, +1);
//  MotorSpeed_3 = MecMIX(-1, -1, +1);
//  MotorSpeed_4 = MecMIX(+1, -1, +1);
//
//  //  MotorSpeed_1 = MecMIX(-1, +1, +1);
//  //  MotorSpeed_2 = MecMIX(-1, -1, +1);
//  //  MotorSpeed_3 = MecMIX(+1, +1, +1);
//  //  MotorSpeed_4 = MecMIX(+1, -1, +1);
//
//
//
//
//  if (MotorSpeed_1 > 0)//判断正反转
//  {
//    digitalWrite(Motor_A1, LOW);
//    digitalWrite(Motor_B1, HIGH);
//    analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
//  }
//  else
//  {
//    digitalWrite(Motor_A1, HIGH);
//    digitalWrite(Motor_B1, LOW);
//    analogWrite(Motor_PWM_1, abs(MotorSpeed_1));
//  }
//
//
//  if (MotorSpeed_2 > 0)//以下三个轮子同理
//  {
//    digitalWrite(Motor_A2, LOW);
//    digitalWrite(Motor_B2, HIGH);
//    analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
//  }
//  else
//  {
//    digitalWrite(Motor_A2, HIGH);
//    digitalWrite(Motor_B2, LOW);
//    analogWrite(Motor_PWM_2, abs(MotorSpeed_2));
//  }
//
//  if (MotorSpeed_3 > 0)
//  {
//    digitalWrite(Motor_A3, LOW);
//    digitalWrite(Motor_B3, HIGH);
//    analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
//  }
//  else
//  {
//    digitalWrite(Motor_A3, HIGH);
//    digitalWrite(Motor_B3, LOW);
//    analogWrite(Motor_PWM_3, abs(MotorSpeed_3));
//  }
//
//  if (MotorSpeed_4 > 0)
//  {
//    digitalWrite(Motor_A4, LOW);
//    digitalWrite(Motor_B4, HIGH);
//    analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
//  }
//  else
//  {
//    digitalWrite(Motor_A4, HIGH);
//    digitalWrite(Motor_B4, LOW);
//    analogWrite(Motor_PWM_4, abs(MotorSpeed_4));
//  }
//}


//void ks103move(double y, int sp)//通过超声波进行横向移动，输入位置和速度
//{
//  int range1 = 0,range2=0;
//
//  Wire.beginTransmission(ks1031);               // Start communticating with SRF08
//  Wire.beginTransmission(ks1032);
//  Wire.write(Reg);                                // Send Command Byte
//  Wire.write(0xb4);                                // Send 0xb0 to start a ranging
//  Wire.endTransmission();
//
//  delay(100);                                     // Wait for ranging to be complete
//
//  Wire.beginTransmission(ks1031);              // start communicating with SRFmodule
//  Wire.beginTransmission(ks1032);
//  Wire.write(Reg);                                // Call the register for start of ranging data
//  Wire.endTransmission();
//
//  Wire.requestFrom(ks1031, 2);                 // Request 2 bytes from SRF module
//  while(Wire.available() < 2);                    // Wait for data to arrive
//  highByte = Wire.read();                         // Get high byte
//  lowByte = Wire.read();                          // Get low byte
//  range1 = (highByte << 8) + lowByte;              // Put them together
//
//  Wire.requestFrom(ks1032, 2);                 // Request 2 bytes from SRF module
//  while(Wire.available() < 2);                    // Wait for data to arrive
//  highByte = Wire.read();                         // Get high byte
//  lowByte = Wire.read();                          // Get low byte
//  range2 = (highByte << 8) + lowByte;              // Put them together
//
//  double range;
//  range = range1 / range2;
//  for (; range < y;)//条件还没写全
//  {
//    movexy(sp, 0);//以特定速度横向移动
//  }
//    movexy(0, 0);//刹车
//}

//

//void numy(int i, int speed)
//{
//  int temp, m = 0, n = 0;
//  Serial1.write("1");
//  while (1)
//  {
//    movexyz3(0, speed, 0, 20);
//
//    if (Serial2.read() == '1')
//    {
//      m++;
//      Serial2.write("1");
//    }
//    if (m >= i)
//    {
//      break;
//    }
//  }
//}

//void numx(int i, int speed)
//{
//  int temp, m = 0, n = 0;
//  Serial3.write("1");
//  while (1)
//  {
//    movexyz3(speed, 0, 20, 0);
//    if (digitalRead(trac1))
//    {
//      m++;
//      Serial3.write("1");
//    }
//    if (m >= (i + i))
//    {
//      break;
//    }
//  }
//}
