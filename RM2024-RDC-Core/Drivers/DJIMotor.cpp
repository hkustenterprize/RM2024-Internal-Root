#include "DJIMotor.hpp"

// DEF
#ifdef USE_DJI_MOTOR
#ifndef RDC_DJIMotor_MAX_NUM
#define RDC_DJIMotor_MAX_NUM 8
#endif

namespace DJIMotor
{

uint8_t txData[8]            = {};
uint8_t rxData[8]            = {};
CAN_TxHeaderTypeDef txHeader = {0x1FF, 0, CAN_ID_STD, CAN_RTR_DATA, 8, DISABLE};
CAN_FilterTypeDef filter     = {0,
                                0x205 << 5,
                                0,
                                0,
                                CAN_FILTER_FIFO0,
                                ENABLE,
                                CAN_FILTERMODE_IDMASK,
                                CAN_FILTERSCALE_16BIT,
                                CAN_FILTER_ENABLE,
                                0};
CAN_RxHeaderTypeDef rxheader;
int16_t rpm;

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
    HAL_CAN_ConfigFilter(&hcan, &filter);;
  HAL_CAN_Start(&hcan);
}

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

DJIMotor &getMotor(uint32_t canID) {
    
}
void sendMotorGroup(uint32_t canID) {}

}  // namespace DJIMotor
#endif