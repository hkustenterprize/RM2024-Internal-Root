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
#include "can.h"

#if USE_DJI_MOTOR

#ifndef DJI_MOTOR_CAN
#define DJI_MOTOR_CAN hcan
#endif

#include "main.h"

namespace DJIMotor
{

/**
 * @brief A motor's handle. We do not require you to master the cpp class
 * syntax.
 * @brief However, some neccessary OOP thought should be shown in your code.
 * @brief For example, if you have multiple motors, which is going to happen in
 * RDC (You have at least 4 wheels to control)
 * @brief You are able to write a "template" module for all the abstract motors,
 * and instantiate them with different parameters
 * @brief Instead of copy and paste your codes for four times
 * @brief This is what we really appreiciate in our programming
 */
class DJIMotor
{
   public:
    DJIMotor(const DJIMotor &)            = delete;
    DJIMotor &operator=(const DJIMotor &) = delete;

    /**
     * @brief Get the raw encoder value
     *
     * @return uint16_t
     */
    uint16_t getRawEncoder() const;

    /**
     * @brief Get the current position of the motor in radian
     * @note  You may need to multiply the reduction ratio of the motor to get
     * the actual position.
     *
     * @return float
     */
    virtual float getPosition() const;

    /**
     * @brief Set the Current Position object in radian
     * @note This just set the current reference position of the motor, it does
     * not change the actual position of the motor.
     *
     * @param position
     */
    virtual void setPosition(float position);

    /**
     * @brief Get the current speed of the motor in revolutions per minute (rpm)
     *
     * @return int16_t
     */
    virtual int16_t getRPM() const;

    /**
     * @brief Get the actual output current(or voltage) of the motor
     *
     * @return int16_t
     */
    virtual int16_t getActualCurrent() const;

    /**
     * @brief Get the set output current(or voltage) of the motor
     *
     * @return int16_t
     */
    int16_t getOutputCurrent() const;

    /**
     * @brief Set the output current(or voltage) of the motor
     * @note  This function will limit the current(or voltage) according to the
     * current(or voltage) limit of the motor. Please call sendMotorGroup() to
     * send the command to the motor.
     *
     * @param current
     */
    virtual void setOutputCurrent(int32_t current);

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
    void setCurrentLimit(uint16_t current);

    /**
     * @brief Get the temperature of the motor
     *
     * @return uint8_t
     */
    uint8_t getTemperature() const;

    /**
     * @brief Get the Reveice Count of the motor, this can be used to estimate
     * the receive frequency of the motor
     *
     * @return uint32_t
     */
    virtual uint32_t getReveiceCount() const;

    /**
     * @brief Check if the motor is connected
     *
     * @return true
     * @return false
     */
    bool isConnected() const;

    /**
     * @brief The array of all the possible DJIMotors
     */
    static DJIMotor motors[11];

    /**
     * @attention   This function is used to decode the CAN message and update
     * the motor data, you should not use this function.
     */
    static void decodeFeedback(CAN_HandleTypeDef *);

   protected:
    /**
     * @attention   You should not call this constructor directly.
     *              Instead, call DJIMotor::getMotor() to get the motor instance
     * according to the motor CAN ID.
     */
    DJIMotor();

    volatile uint16_t rawEncoder;
    volatile uint16_t lastRawEncoder;
    volatile float position;
    volatile int16_t rpm;
    volatile int16_t actualCurrent;
    volatile int16_t setCurrent;
    volatile uint16_t currentLimit;

    volatile uint8_t temperature;

    volatile int32_t rotaryCnt;
    volatile int16_t positionOffset;

    volatile uint32_t disconnectCnt;
    volatile uint32_t receiveCnt;
    volatile bool connected;

    friend DJIMotor &getMotor(uint8_t id);
    friend void motorUpdate(void *);
    friend void sendMotorGroup(uint32_t group);
};

/**
 * @brief The whole motor's module initialization function
 * @note  You might initialize the CAN Module here
 * @retval
 */

DJIMotor &getMotor(uint32_t canID);

/**
 * @brief   Send the command to the motor by group,
 *          call this function after you set the output current(or voltage) of
 * the motor.
 *
 * @param group     0 -> 0x200 , 1 -> 0x1ff, 2 -> 0x2ff
 */

void sendMotorGroup(uint32_t canID);

/**
 * @brief Initialize the DJIMotor driver
 *          Call this function before using this DJIMotor driver
 *
 * @note  If you do not want to use this DJIMotor driver provided by us, do not
 * call this function.
 */

void init();



/*===========================================================*/
}  // namespace DJIMotor
#endif  // USE_DJI_MOTOR