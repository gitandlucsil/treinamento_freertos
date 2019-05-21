/*
 * task1.h
 *
 *  Created on: 2 de mai de 2019
 *      Author: JulioLeme
 */

#ifndef APPLICATION_MAIN_TASK1_H_
#define APPLICATION_MAIN_TASK1_H_
#include "stdint.h"
#include "bsp_led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "application_main.h"


void task_1(void *args);
uint8_t valor_conhecido(uint8_t valor);

#endif /* APPLICATION_MAIN_TASK1_H_ */
