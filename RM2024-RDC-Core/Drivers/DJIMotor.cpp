#include "DJIMotor.hpp"

// DEF
#ifdef USE_DJI_MOTOR
#ifndef RDC_DJIMotor_MAX_NUM
#define RDC_DJIMotor_MAX_NUM 8
#endif
#include "can.h"
namespace DJIMotor
{

// Initialize motor's controller instance
DJIMotor motors[8];

/*========================================================*/
// Your implementation of the function, or even your customized function, should
// be implemented here
/*========================================================*/
/**
 * @todo
 */
void init() {
    HAL_CAN_Start(&hcan);
    
    
}

/**
 * @todo
 */
float getEncoder(uint16_t canID) { return 0.0f; }

/**
 * @todo
 */
int getRPM(uint32_t canID) { 
    uint8_t rxData[8] ={};
    CAN_FilterTypeDef filter = {0, (0x200+canID)<<5,0,0,CAN_FILTER_FIFO0, ENABLE, CAN_FILTERMODE_IDMASK, CAN_FILTERSCALE_16BIT, CAN_FILTER_ENABLE,0};
    
    CAN_RxHeaderTypeDef rxheader;
    HAL_CAN_ConfigFilter(&hcan, &filter);;
    
    int16_t rpm;
    HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rxheader, rxData);
    rpm = rxData[2]<<8 | rxData[3];
    return rpm; 
    
    }

/**
 * @todo
 */
void setOutput(int16_t output) {
    
    
    //txHeader ={0x1FF,0, CAN_ID_STD, CAN_RTR_DATA, 8, DISABLE};
    
}

/**
 * @todo
 */
void transmit(uint16_t header) {
    uint32_t mailbox;
    uint8_t txData[8] ={};
    CAN_TxHeaderTypeDef txHeader ={0x1FF,0, CAN_ID_STD, CAN_RTR_DATA, 8, DISABLE};
    HAL_CAN_AddTxMessage(&hcan, &txHeader, txData, &mailbox);
}  
}
// namespace DJIMotor
#endif