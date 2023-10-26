#include "DJIMotor.hpp"

// DEF
#ifdef USE_DJI_MOTOR
#ifndef RDC_DJIMotor_MAX_NUM
#define RDC_DJIMotor_MAX_NUM 8
#endif

namespace DJIMotor
{
<<<<<<< HEAD
// Initialize motor's controller instance
DJIMotor motors[8];



int16_t DJIMotor::getRPM()
{
    // uint32_t mailbox;
    // HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rxheader, rxData);

    // rpm = rxData[2]<<8 | rxData[3];

    // HAL_Delay(1);
    // return 0.0f;
=======

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
//int16_t rpm;

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
    HAL_CAN_ConfigFilter(&hcan, &filter);
  HAL_CAN_Start(&hcan);
>>>>>>> ad723e03a2a42cba7373e10ee096fdd6243668a4
}

/**
 * @brief Get the raw encoder value
 *
 * @return uint16_t
 */
uint16_t DJIMotor::getRawEncoder() const {

}

/**
 * @brief Get the current position of the motor in radian
 * @note  You may need to multiply the reduction ratio of the motor to get
 * the actual position.
 *
 * @return float
 */
float DJIMotor::getPosition() const {

}

/**
 * @brief Set the Current Position object in radian
 * @note This just set the current reference position of the motor, it does
 * not change the actual position of the motor.
 *
 * @param position
 */
void DJIMotor::setPosition(float position) {

}

/**
 * @brief Get the current speed of the motor in revolutions per minute (rpm)
 *
 * @return int16_t
 */
int16_t DJIMotor::getRPM() {

}

/**
 * @brief Get the actual output current(or voltage) of the motor
 *
 * @return int16_t
 */
int16_t DJIMotor::getActualCurrent() const {}

/**
 * @brief Get the set output current(or voltage) of the motor
 *
 * @return int16_t
 */
int16_t DJIMotor::getOutputCurrent() const {}

/**
 * @brief Set the output current(or voltage) of the motor
 * @note  This function will limit the current(or voltage) according to the
 * current(or voltage) limit of the motor. Please call sendMotorGroup() to
 * send the command to the motor.
 *
 * @param current
 */
void DJIMotor::setOutputCurrent(int32_t current) {

}

/**
 * @brief Set the Current(or voltage) Limit of the motor
 * @note  To avoid overflow,
 *          the maximum current limit for M3508 is 16384,
 *          and the maximum voltage limit for GM6020 is 30000.
 *
 * The default limit is 10000.
 *
 * @param current
 */
void DJIMotor::setCurrentLimit(uint16_t current) {

}

/**
 * @brief Get the temperature of the motor
 *
 * @return uint8_t
 */
uint8_t DJIMotor::getTemperature() const {

}

/**
 * @brief Get the Reveice Count of the motor, this can be used to estimate
 * the receive frequency of the motor
 *
 * @return uint32_t
 */
uint32_t DJIMotor::getReveiceCount() const {}

/**
 * @brief Check if the motor is connected
 *
 * @return true
 * @return false
 */
bool DJIMotor::isConnected() const {

}

DJIMotor &getMotor(uint32_t canID) {
    
}
void sendMotorGroup(uint32_t canID) {}

void init()
{
    // HAL_CAN_ConfigFilter(&hcan, &DJIMotor::filter);
    // HAL_CAN_Start(&hcan);
}
}  // namespace DJIMotor
#endif