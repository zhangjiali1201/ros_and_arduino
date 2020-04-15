/***************************************************************
 Copyright: 2016-2019 ROS小课堂 www.corvin.cn
 Author: corvin
 Editor: jally
 Description:
    定义舵机操作的类SweepServo,舵机连接的引脚和初始的舵机角度.在这里
    舵机可连接9或10引脚.
*************************************************************/
#ifndef _SERVOS_H_
#define _SERVOS_H_

#define  N_SERVOS  2

#define  SERVO_ENABLE   1
#define  SERVO_DISABLE  0

//Define All Servos's Pins
byte myServoPins[N_SERVOS] = { 9, 10};

// Initial Servo Position [0, 180] degrees
int servoInitPosition[N_SERVOS] = {0, 0};

class SweepServo
{
  public:
    SweepServo();
    void initServo(int servoPin, unsigned int initPosition, unsigned int stepDelayMs);
    void setTargetPos(unsigned int targetPos, unsigned int stepDelayMs);
    int getCurrentPos(void);
    void setEnable(byte flag);
    void moveServo(void);
    byte isEnabled(void);
    Servo getServoObj();

  private:
    Servo servo;
    unsigned int stepDelayMs;
    unsigned long lastMoveTime;
    int currentPosDegrees;
    int targetPosDegrees;
    byte enabled;
};

SweepServo myServos[N_SERVOS];

#endif
