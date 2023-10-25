#include "PID.hpp"
#if USE_PID
namespace Control
{

/*This is where you implement the PID algorithm*/
float PID::update(float target, float measurement, float dt)
{
    /*=====================================================================*/
    // Your implementation of the PID algorithm begins here
    /*=====================================================================*/
    error = target - measurement;  // Calculate the error
    pOut = Kp * error;             // Calculate the P term
    iOut += Ki * error * dt;    // Calculate the I term
    dOut = Kd * (error-lastError)/dt;   // Calculate the D term
    output = pOut + iOut + dOut ;  // The output is the sum of all terms
    lastError = error;     // Update the last error
    /*=====================================================================*/
    // Your implementation of the PID algorithm ends here
    /*=====================================================================*/
    return this->output;  // You need to give your user the output for every update
}

}  // namespace Control
#endif
