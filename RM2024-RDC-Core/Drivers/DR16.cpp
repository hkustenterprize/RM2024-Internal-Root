/**
 * @file DR16.cpp
 * @brief Implement the function definition that is declared in DR16.hpp file
 */

/* Include the DR16.hpp header file here, so the compiler would look for the
 * variable or function definition here */
#include "DR16.hpp"
#include <stdio.h>
#include <memory.h>

#if USE_DR16

namespace DR16
{

/**
 * @brief Define a singleton RcData structure instance here.
 * @param connected The boolean variable updated in time showing the connection status 
 */
static RcData rcData;

/*Return the constant pointer of the current decoded data*/
const RcData *getRcData() { return &rcData; }

/*================================================================================*/

const int DATASIZE = 18;
const int RANGE_MAX = 1684;
const int RANGE_MIN = 364;
const int RANGE_DEFAULT = 1024;

bool ifContinue = true;
bool connected  = false;

uint8_t rxBuffer[DATASIZE];

uint32_t lastReceiveTick = HAL_GetTick();

char strBuffer[100];

char* getStatus() {
    memset(strBuffer, 0, 100 * sizeof(char));
    sprintf(strBuffer,
            "channel0: %u\nchannel1: %u\nchannel2: %u\nchannel3: %u\n",
            rcData.channel0,
            rcData.channel1,
            rcData.channel2,
            rcData.channel3);
    return strBuffer;
}

void clearMemory() {
    rcData.channel0 = RANGE_DEFAULT;
    rcData.channel1 = RANGE_DEFAULT;
    rcData.channel2 = RANGE_DEFAULT;
    rcData.channel3 = RANGE_DEFAULT;
    // Set the middle position to be the default for switches
    rcData.s1       = 2;
    rcData.s2       = 2;
}

/**
 * Put this function in the while loop. This function updates a boolean global variable
 * RC16::connected constantly and call clearMemory when not connected
*/
void updateConnectionStatus(uint32_t timeLimit) {
    if (HAL_GetTick() - lastReceiveTick > timeLimit){
        connected = false;
    } else {
        connected = true;
    }
    if (connected == false)
        clearMemory();
}

// Error Callback Function
void ErrorCallback(UART_HandleTypeDef *huart) {
    clearMemory();
    HAL_UART_Abort_IT(huart);
    HAL_UARTEx_ReceiveToIdle_IT(huart, rxBuffer, 18);
}

// Normal Callback Function
void rxEventCallback(UART_HandleTypeDef *huart, uint16_t dataSize)
{
    // Verifiy data validity
    if (dataSize != DATASIZE) {
        ErrorCallback(huart);
        return;
    }

    // Decode the data after receiving (Rather stupid since I did not use the provided version)
    // TODO: Update decoding to the provided code by DJI
    rcData.channel0 =
        (uint16_t)rxBuffer[0] + (((uint16_t)(rxBuffer[1] & 0b00000111)) << 8);
    rcData.channel1 = (((uint16_t)rxBuffer[1]) >> 3) +
                      (((uint16_t)(rxBuffer[2] & 0b00111111)) << 5);
    rcData.channel2 = (((uint16_t)rxBuffer[2]) >> 6) +
                      (((uint16_t)rxBuffer[3]) << 2) +
                      (((uint16_t)rxBuffer[4] & 0b00000001) << 10);
    rcData.channel3 = (((uint16_t)rxBuffer[4]) >> 1) +
                      ((((uint16_t)rxBuffer[5]) & 0b00001111) << 7);
    rcData.s1 = (((uint16_t)rxBuffer[5]) & 0b00110000) >> 4;
    rcData.s2 = (((uint16_t)rxBuffer[5]) & 0b11000000) >> 6;

    // Verify decoded data range;
    bool p1 = rcData.channel0 <= RANGE_MAX && rcData.channel0 >= RANGE_MIN;
    bool p2 = rcData.channel1 <= RANGE_MAX && rcData.channel1 >= RANGE_MIN;
    bool p3 = rcData.channel2 <= RANGE_MAX && rcData.channel2 >= RANGE_MIN;
    bool p4 = rcData.channel3 <= RANGE_MAX && rcData.channel3 >= RANGE_MIN;
    bool p5 =
        rcData.s1 <= 3 && rcData.s1 >= 1 && rcData.s2 <= 3 && rcData.s2 >= 1;
    if (!(p1&&p2&&p3&&p4&&p5)) {
        ErrorCallback(huart);
        return;
    }
    // Record time when receive
    lastReceiveTick = HAL_GetTick();

    // Repeat
    HAL_UARTEx_ReceiveToIdle_IT(huart, rxBuffer, 18);
}

/*================================================================================*/
void init()
{
    HAL_UART_RegisterRxEventCallback(&huart1, rxEventCallback);
    HAL_UART_RegisterCallback(&huart1, HAL_UART_ERROR_CB_ID, ErrorCallback);
    HAL_UARTEx_ReceiveToIdle_IT(&huart1, rxBuffer, 18);
}

}  // namespace DR16

#endif
