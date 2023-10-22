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
float getRPM(uint16_t canID) { return 0.0f; }

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