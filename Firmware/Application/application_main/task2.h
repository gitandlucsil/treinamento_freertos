/*
 * task2.h
 *
 *  Created on: 7 de mai de 2019
 *      Author: andre
 */

#ifndef APPLICATION_MAIN_TASK2_H_
#define APPLICATION_MAIN_TASK2_H_
#include "stdint.h"
#include "lib_utilities.h"
#include "fsm_avi_rede.h"
#include "bsp_led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "application_main.h"

#define NUMERO_DADOS_VETOR              11

void task_2(void *args);

#endif /* APPLICATION_MAIN_TASK2_H_ */
