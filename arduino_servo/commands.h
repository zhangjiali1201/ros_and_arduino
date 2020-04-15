/**********************************************************************
 Copyright: 2016-2019 ROS小课堂 www.corvin.cn
 Author: corvin
 Editor: jally
 Description:
   Define single-letter commands that will be sent by the PC over the
   serial link.
   e.g. b       获取波特率
        e 0 1   使能接9号引脚的舵机
        w 0 30  接9号引脚的舵机旋转到30°处
        r 0     读取接9号引脚的舵机当前位置
        p       获取当前所有舵机位置
        s       获取当前所有舵机的使能状态
        z 1     接9号引脚的舵机旋转到45°处
*/
#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define  GET_CONNECT_BAUDRATE   'b'
#define  SET_ONE_SERVO_ENABLE   'e'
#define  SET_ONE_SERVO_POS      'w'
#define  GET_ONE_SERVO_POS      'r'
#define  GET_ALL_SERVOS_POS     'p'
#define  GET_ALL_SERVOS_ENABLE  's'
#define  SERVO_TEST   'z'

#endif
