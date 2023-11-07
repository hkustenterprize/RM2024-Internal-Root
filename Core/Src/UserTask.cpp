/**
 * @file UserTask.cpp
 * @author JIANG Yicheng  RM2024 (EthenJ@outlook.sg)
 * @author GUO, Zilin
 * @brief RDC user task files
 * @version 0.3
 * @date 2022-10-20
 *
 * @copyright Copyright (c) 2024
 */
#include "AppConfig.h"   // Include our customized configuration
#include "DJIMotor.hpp"  // Include DR16
#include "DR16.hpp"
#include "FreeRTOS.h"  // Include FreeRTOS.h
#include "PID.hpp"     // Include PID
#include "main.h"
#include "task.h"  // Include task

/*Allocate the stack for our PID task*/
StackType_t uxPIDTaskStack[256];
/*Declare the PCB for our PID task*/
StaticTask_t xPIDTaskTCB;

/**
 * @todo Show your control outcome of the M3508 motor as follows
 */
void userTask(void *)
{
    // DJIMotor::DJIMotor &motor = DJIMotor::getMotor();
    // motor.setCurrentLimit(30000);
    /* Your user layer codes begin here*/
    /*=================================================*/
    static Control::PID pid1(10,2,0);
    DJIMotor::Motor_measure_t Motor_measure[14];
    DJIMotor::can_filter_init();
    /* Your user layer codes end here*/
    /*=================================================*/
    while (true)
    {
        /* Your user layer codes in loop begin here*/
        /*=================================================*/
        //currentRPM = motor.getRPM();
       //static Control::PID motorPID(0, 0, 0);
        
        
		
		//spd = 1000;
		//Motor_measure[0].Output = PID_calc(&Motor_pid[0],Motor_measure[0].speed,spd);
        Motor_measure[0].Output = pid1.update(1000,Motor_measure[0].speed,0.001f);
		DJIMotor::Set_motor_cmd(&hcan,0x200,Motor_measure[0].Output,0,0,0);
		

        // float output = motorPID.update(targetRPM,currentRPM,0.001f);

        // motor.setOutput(output);

        // DJIMotor::transmit(1);  // Transmit the data to the motor, whiche
        vTaskDelay(10);  // Delay and block the task for 1ms.
    
}
}

/**
 * @todo In case you like it, please implement your own tasks
 */








/**
 * @brief Intialize all the drivers and add task to the scheduler
 * @todo  Add your own task in this file
*/
void startUserTasks()
{
    //DJIMotor::init();  // Initalize the DJIMotor driver
    DR16::init();      // Intialize the DR16 driver

    xTaskCreateStatic(userTask,
                      "user_default ",
                      256,
                      NULL,
                      1,
                      uxPIDTaskStack,
                      &xPIDTaskTCB);  // Add the main task into the scheduler
    /**
     * @todo Add your own task here
    */
}
