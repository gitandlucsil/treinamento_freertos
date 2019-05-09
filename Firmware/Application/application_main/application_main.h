/*
 * application_main.h
 *
 *  Created on: 2 de abr de 2019
 *      Author: JulioLeme
 */

#ifndef APPLICATION_MAIN_H_
#define APPLICATION_MAIN_H_
#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "task1.h"
#include "task2.h"

#define TASK1_PRIORITY        (tskIDLE_PRIORITY+1)
#define TASK1_STACK_SIZE      configMINIMAL_STACK_SIZE

#define TASK2_PRIORITY        (tskIDLE_PRIORITY+2)
#define TASK2_STACK_SIZE      configMINIMAL_STACK_SIZE

void app_run(void);
TaskHandle_t get_task_handle(uint8_t task_number);

#endif /* APPLICATION_MAIN_H_ */
