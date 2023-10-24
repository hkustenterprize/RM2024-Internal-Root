/**
 * @file  DR16.hpp
 * @brief The header file of the DR16.hpp
 *
 */

#pragma once
#include "AppConfig.h"

#if USE_DR16

#include "main.h"
#include "stdint.h"
#include "usart.h"

namespace DR16
{

/**
 * @brief the DR16 remote controller structure
 * @brief This structure is based on the DR16 user manual
 *
 * @param channel0 The channel0 data from the remote controller
 * @param channel1 The channel1 data from the remote controller
 * @param channel2 The channel2 data from the remote controller
 * @param channel3 The channel3 data from the remote controller
 *
 * @param s1       The switch 1 data from the remote controller
 * @param s2       The switch 2 data from the remote controller
 */
typedef struct
{
    uint16_t channel0 : 11;  // Channel 0 data
    uint16_t channel1 : 11;  // Channel 1 data
    uint16_t channel2 : 11;  // Channel 2 data
    uint16_t channel3 : 11;  // Channel 3 data

    uint8_t s1 : 2;  // Switch 1 data
    uint8_t s2 : 2;  // Switch 2 data
} RcData;

/**
 * @brief Access the decoded remote controller datat by this API
 * @remark You are recommended to:
 *         - Return a constant pointer of the decoded remote controller data
 * in this fucntion
 */
const RcData* getRcData();
extern bool connected;
extern uint8_t rxBuffer[18];

/*===========================================================================*/
/*You can declare your own function here, supposing you would like to desgin
 * a more complicated DR16 module*/

void updateConnectionStatus(uint32_t timeLimit);
void rxCallback(UART_HandleTypeDef *huart, uint16_t dataSize);
char *getStatus();

/*===========================================================================*/

/**
 * @brief The initialization of your assingment DR16 Module
 * @remark You are recommended to:
 *         - Register your callback in the function
 *         - Start the first round of the UART data reception
 * @remark If you wish to, please implement the function body in the
 * DR16.cpp file
 */
void init();

}  // namespace DR16
#endif  // DR16_UART
