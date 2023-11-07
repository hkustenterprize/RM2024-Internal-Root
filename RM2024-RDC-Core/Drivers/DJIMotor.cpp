#include "DJIMotor.hpp"

// DEF
#ifdef USE_DJI_MOTOR
#ifndef RDC_DJIMotor_MAX_NUM
#define RDC_DJIMotor_MAX_NUM 8
#endif
#include "can.h"
namespace DJIMotor
{
void can_filter_init(void)
{
	CAN_FilterTypeDef can_filter_st;	                //定义过滤器结构体
    can_filter_st.FilterActivation = ENABLE;			//ENABLE使能过滤器
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;	//设置过滤器模式--标识符屏蔽位模式
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;	//过滤器的位宽 32 位
    can_filter_st.FilterIdHigh = 0x0000;				//ID高位
    can_filter_st.FilterIdLow = 0x0000;					//ID低位
    can_filter_st.FilterMaskIdHigh = 0x0000;			//过滤器掩码高位
    can_filter_st.FilterMaskIdLow = 0x0000;				//过滤器掩码低位
    
    can_filter_st.FilterBank = 0;						//过滤器组-双CAN可指定0~27
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;	//与过滤器组管理的 FIFO
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);		//HAL库配置过滤器函数
    HAL_CAN_Start(&hcan1);								//使能CAN1控制器
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    can_filter_st.SlaveStartFilterBank = 14;   //双CAN模式下规定CAN的主从模式的过滤器分配，从过滤器为14
    can_filter_st.FilterBank = 14;						//过滤器组-双CAN可指定0~27
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);		//HAL库配置过滤器函数
    HAL_CAN_Start(&hcan2);								//使能CAN2控制器
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);

}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef RX_Header;	//数据帧帧头
	uint8_t RX_BUFFER[8];	//接收存放数据帧数据的数组
	HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&RX_Header,RX_BUFFER);	
	
	static uint8_t i = 0;
	if(hcan==&hcan1){		
		i = RX_Header.StdId - Chassis_3508A;		
		Motor_measure_fun(&Motor_measure[i], RX_BUFFER);	
	}
	else if(hcan==&hcan2){    
		i = RX_Header.StdId - CAN2_3508_ID1 + 7;	
		Motor_measure_fun(&Motor_measure[i], RX_BUFFER);	
	}
}
void Motor_measure_fun(Motor_measure_t *ptr,uint8_t* RX_buffer)
{
	ptr->last_angle = ptr->angle;		
	ptr->angle = (uint16_t)((RX_buffer)[0] << 8 | (RX_buffer)[1]); 	//转子机械角度
	ptr->speed = (uint16_t)((RX_buffer)[2] << 8 | (RX_buffer)[3]);	//转子转速(rpm)
	ptr->torque_current = (uint16_t)((RX_buffer)[4] << 8 | (RX_buffer)[5]);	//转矩电流
	ptr->temp = (RX_buffer)[6];         
	if(ptr->angle - ptr->last_angle > 4096)				
		ptr->round_cnt --;								
	else if(ptr->angle - ptr->last_angle < -4096)		
		ptr->round_cnt ++;
	ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle;	
}
void Set_motor_cmd(CAN_HandleTypeDef *hcan,uint32_t STDID,int16_t motor1,int16_t motor2,int16_t motor3,int16_t motor4)
{
	uint32_t send_mail_box;	
	CANx_tx_message.StdId = STDID;			
	CANx_tx_message.IDE = CAN_ID_STD;		
    CANx_tx_message.RTR = CAN_RTR_DATA;	
    CANx_tx_message.DLC = 0x08;			
	
	CANx_send_data[0] = motor1 >> 8;		
	CANx_send_data[1] = motor1;
	CANx_send_data[2] = motor2 >> 8;
	CANx_send_data[3] = motor2;
	CANx_send_data[4] = motor3 >> 8;
	CANx_send_data[5] = motor3;
	CANx_send_data[6] = motor4 >> 8;
	CANx_send_data[7] = motor4;

	HAL_CAN_AddTxMessage(hcan,&CANx_tx_message, CANx_send_data,&send_mail_box);	
}
}
// namespace DJIMotor
#endif