/**
 * @file DJIMotor.hpp
 * @author - GUO, Zilin
 *         - Your Name
 * @brief This is the DJIMotor template codes for RM2024-Tutorial PA3 and RDC
 * @note  You could directly transplant your code to the RDC after finishing PA3
 * @note  If you do not like the template I provide for you, you could remove
 * all of them and use your own
 * @copyright This file is only for HKUST Enterprize RM2024 internal
 * competition. All Rights Reserved.
 *
 */

#pragma once
#include "AppConfig.h"

#if USE_DJI_MOTOR

#ifndef DJI_MOTOR_CAN
#define DJI_MOTOR_CAN hcan
#endif

#include "main.h"
#include "can.h"
 //int16_t currentRPM = 0;
   // uint32_t id = 2;
namespace DJIMotor
{

//Motor_measure_t Motor_measure[14];
typedef struct{
	int16_t	 	speed;
  int16_t  	torque_current;
	int16_t   Output;
  uint8_t  	temp;
	int16_t 	angle;				//abs angle range:[0,8191]
	int16_t 	last_angle;	        //abs angle range:[0,8191]
	int32_t		round_cnt;
	int32_t		total_angle;
}Motor_measure_t;

void can_filter_init(void);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void Motor_measure_fun(Motor_measure_t *ptr,uint8_t* RX_buffer);
void Set_motor_cmd(CAN_HandleTypeDef *hcan,uint32_t STDID,int16_t motor1,int16_t motor2,int16_t motor3,int16_t motor4);
/*===========================================================*/
}  // namespace DJIMotor
#endif  // USE_DJI_MOTOR