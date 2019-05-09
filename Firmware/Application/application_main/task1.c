/*
 * task1.c
 *
 *  Created on: 2 de mai de 2019
 *      Author: JulioLeme
 */
#include "task1.h"

TaskHandle_t taskToSuspend = NULL;
void task_1(void *args)
{

    while(1){
    	taskToSuspend = get_task_handle(2);
        bsp_led_fsm_run();
        bsp_led_requisita(
                1,
                500,
                500,
                30,
                150,
                3);
        vTaskSuspend(taskToSuspend);
        //vTaskDelay(10);
    }
}


