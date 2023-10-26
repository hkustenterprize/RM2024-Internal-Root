#include "DJIMotor.hpp"

// DEF
#ifdef USE_DJI_MOTOR
#ifndef RDC_DJIMotor_MAX_NUM
#define RDC_DJIMotor_MAX_NUM 8
#endif

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
void init() {}

/**
 * @todo
 */
float getEncoder(uint16_t canID) { return 0.0f; }

/**
 * @todo
 */
float getRPM(uint16_t canID) { 
uint32_t mailbox;
    HAL_CAN_AddTxMessage(&hcan, &txHeader, txData, &mailbox);
    HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rxheader, rxData);

    rpm = rxData[2]<<8 | rxData[3];

    HAL_Delay(1);
    return 0.0f; }
/**
 * @todo
 */
void setOutput(int16_t output) {}

/**
 * @todo
 */
void transmit(uint16_t header) {}

}  // namespace DJIMotor
#endif