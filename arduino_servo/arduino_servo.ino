/********************************************************************************
  Copyright: 2016-2019 ROS小课堂 www.corvin.cn
  Author: corvin
  Editor: jally
  Description:
       使用arduino UNO开发板。通过串口可以发送命令控制舵机的旋转，在
    控制转动前需要先使能指定pwm引脚上的舵机，具体操作命令格式如下：
    (0).使能pwm 9号引脚上的舵机,该引脚舵机索引值为0,第2个参数表明使能（非0）或禁用（0）：
      e 0 1
    (1).控制舵机旋转:
      w 0 90 20:该串口命令中w表示写入，0表示0号舵机，90表示旋转到90度,每次移动延时20ms
      w 1 30 50:表示1号舵机移动到30度,每个移动周期延时50ms.
    (2).读取指定舵机ID的当前角度：
      r 0:串口输入该命令，则返回90,表示0号舵机当前在90度位置.
      r 1:输入该命令后，返回30,表示1号舵机当前在30度位置。
    (3).获取所有舵机的使能状态命令s:
      s:0 1：返回的一串数字表明第几个舵机使能。
    (4).获取所有舵机的角度p:
      p:90 0:第1个舵机当前在90度位置。
********************************************************************************/
#define  CONNECT_BAUDRATE   57600

#include <Servo.h>
#include "serialData.h"
#include "commands.h"
#include "servos.h"

/* Run a command.  Commands char are defined in commands.h */
void runCommand(void)
{
  serialObj.arg1 = atoi(serialObj.argv1);
  serialObj.arg2 = atoi(serialObj.argv2);
  serialObj.arg3 = atoi(serialObj.argv3);

  switch (serialObj.cmd_chr)
  {
    case GET_CONNECT_BAUDRATE:  // 'b'
      Serial.println(CONNECT_BAUDRATE);
      break;

    case SET_ONE_SERVO_ENABLE:  // 'e'
      myServos[serialObj.arg1].setEnable(serialObj.arg2);
      Serial.println("OK");
      break;

    case SET_ONE_SERVO_POS:   // 'w'
      myServos[serialObj.arg1].setTargetPos(serialObj.arg2, serialObj.arg3);
      Serial.println("OK");
      break;

    case GET_ONE_SERVO_POS:   // 'r'
      Serial.println(myServos[serialObj.arg1].getServoObj().read());
      break;

    case GET_ALL_SERVOS_POS: // 'p'
      for (byte i = 0; i < N_SERVOS; i++)
      {
        Serial.print(myServos[i].getCurrentPos());
        Serial.print(' ');
      }
      Serial.println("");
      break;

    case GET_ALL_SERVOS_ENABLE: // 's'
      for (byte i = 0; i < N_SERVOS; i++)
      {
        Serial.print(myServos[i].isEnabled());
        Serial.print(' ');
      }
      Serial.println("");
      break;

    case SERVO_TEST:  // 'z'
      if (serialObj.arg1 == 0)
      {
        myServos[0].setTargetPos(0, 10);
      }
      else if (serialObj.arg1 == 1)
      {
        myServos[0].setTargetPos(45, 10);
      }
      else if (serialObj.arg1 == 2)
      {
        myServos[0].setTargetPos(90, 10);
      }
      else if (serialObj.arg1 == 3)
      {
        myServos[0].setTargetPos(120, 10);
      }
      Serial.println("Done");
      break; 
      
    default:
      Serial.println("Invalid Command");
      break;
  }
}

/* Setup function--runs once at startup. */
void setup()
{
  Serial.begin(CONNECT_BAUDRATE);
  serialObj.resetCmdParam();

  /* when power on init all servos position */
  for (byte i = 0; i < N_SERVOS; i++)
  {
    myServos[i].initServo(myServoPins[i], servoInitPosition[i], 0);
  }
}

/* Enter the main loop.  Read and parse input from the serial port
   and run any valid commands.
*/
void loop()
{
  while (Serial.available() > 0)
  {
    char tmp_chr = Serial.read(); // Read the next character
    
    if (tmp_chr == 13) // Terminate a command with a CR
    {
      runCommand();
      serialObj.resetCmdParam();
    }
    else if (tmp_chr == ' ') // Use spaces to delimit parts of the command
    {
      serialObj.argCnt++;
      serialObj.argIndex = 0;
    }
    else // get valid param
    {
      if (serialObj.argCnt == 0) // The first arg is the single-letter command
      {
        serialObj.cmd_chr = tmp_chr;
      }
      else if (serialObj.argCnt == 1) // Get after cmd first param
      {
        serialObj.argv1[serialObj.argIndex] = tmp_chr;
        serialObj.argIndex++;
      }
      else if (serialObj.argCnt == 2)
      {
        serialObj.argv2[serialObj.argIndex] = tmp_chr;
        serialObj.argIndex++;
      }
      else if (serialObj.argCnt == 3)
      {
        serialObj.argv3[serialObj.argIndex] = tmp_chr;
        serialObj.argIndex++;
      }
    }
  } //end while

  // Check everyone servos isEnabled, when true will move servo. Other don't move servo.
  for (byte i = 0; i < N_SERVOS; i++)
  {
    //if (myServos[i].isEnabled())
    {
      myServos[i].moveServo();
    }
  }
}//end loop
