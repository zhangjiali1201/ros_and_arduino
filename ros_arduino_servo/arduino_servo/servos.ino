/**********************************************************************
  Copyright: 2016-2019 ROS小课堂 www.corvin.cn
  Author: corvin
  Description:
   Sweep servos one degree step at a time with a user defined
   delay in between steps.
  History:
  20181121: initial this code.
  20181130: 新增获取和设置舵机使能状态的函数。
  20181204: 删除了舵机的disable函数,使用enable来实现。新增了getCurrentPos()
      函数,用户获取当前舵机的角度。
**********************************************************************/
// Constructor function
SweepServo::SweepServo()
{
  this->currentPosDegrees = 0;
  this->targetPosDegrees  = 0;
  this->lastMoveTime      = 0;
}

// Init servo params, default all servos disabled.
void SweepServo::initServo(int servoPin, unsigned int initPosition, unsigned int stepDelayMs)
{
  this->servo.attach(servoPin);
  this->stepDelayMs = stepDelayMs;
  this->currentPosDegrees = initPosition;
  this->targetPosDegrees  = initPosition;
  this->lastMoveTime = millis();
  this->enabled = SERVO_DISABLE;

  this->servo.write(initPosition); //when power on, move all servos to initPosition
}

//Servo Perform Sweep
void SweepServo::moveServo(void)
{
  // Get ellapsed time from last cmd time to now.
  unsigned int delta = millis() - this->lastMoveTime;

  // Check if time for a step
  if (delta > this->stepDelayMs)
  {
    // Check step direction
    if (this->targetPosDegrees > this->currentPosDegrees)
    {
      this->currentPosDegrees++;
      this->servo.write(this->currentPosDegrees);
    }
    else if (this->targetPosDegrees < this->currentPosDegrees)
    {
      this->currentPosDegrees--;
      this->servo.write(this->currentPosDegrees);
    }
    // if target == current position, do nothing

    // reset timer, save current time to last cmd time.
    this->lastMoveTime = millis();
  }
}

// Set a new target position with step delay param.
void SweepServo::setTargetPos(unsigned int targetPos, unsigned int stepDelayMs)
{
  this->targetPosDegrees = targetPos;
  this->stepDelayMs      = stepDelayMs;
}

int SweepServo::getCurrentPos(void)
{
  return this->currentPosDegrees;
}

void SweepServo::setEnable(byte flag)
{
  if (flag == SERVO_ENABLE)
  {
    this->enabled = SERVO_ENABLE;
  }
  else
  {
    this->enabled = SERVO_DISABLE;
  }
}

byte SweepServo::isEnabled(void)
{
  return this->enabled;
}

// Accessor for servo object
Servo SweepServo::getServoObj()
{
  return this->servo;
}
