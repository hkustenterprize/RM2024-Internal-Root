#include "PID.hpp"

float abs(float n)
{
    if (n >= 0)
        return n;
    return -n;
}

#if USE_PID
namespace Control
{

/*This is where you implement the PID algorithm*/
float PID::update(float target, float measurement, float dt)
{
    /*=====================================================================*/
    // Your implementation of the PID algorithm begins here
    /*=====================================================================*/
    
    int index;
    if (measurement > maxRPM)
    {
        if (abs(error) > 200)
        {
            index = 0;
        }
        else
        {
            index = 1;
            if(error < 0)
            {
                integral += error * dt;
            }
        }
    }
    else if (measurement < minRPM)
    {
        if (abs(error) > 200)
        {
            index = 0;
        }
        else
        {
            index = 1;
            if (error > 0)
            {
                integral += error * dt;
            }
        }
    }
    else
    {
        if (abs(error) > 200)
        {
            index = 0;
        }
        else
        {
            index = 1;
            integral += error * dt;
        }
    }
    currentfilter = a * previousfilter + (1 - a) * (error-lastError);
    previousfilter = currentfilter;
    error = target - measurement;  // Calculate the error
    pOut = Kp * error;             // Calculate the P term
    iOut = Ki * integral * index ;    // Calculate the I term
    dOut = Kd * currentfilter/dt;   // Calculate the D term
    output = pOut + iOut + dOut ;  // The output is the sum of all terms
    lastError = error;     // Update the last error
    /*=====================================================================*/
    // Your implementation of the PID algorithm ends here
    /*=====================================================================*/
    return this->output;  // You need to give your user the output for every update
}

}  // namespace Control
#endif
