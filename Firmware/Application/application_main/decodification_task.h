/*
 * task2.h
 *
 *  Created on: 7 de mai de 2019
 *      Author: andre
 */

#ifndef APPLICATION_MAIN_DECODIFICATION_TASK_H_
#define APPLICATION_MAIN_DECODIFICATION_TASK_H_
#include "stdint.h"
#include "lib_utilities.h"
#include "fsm_avi_rede.h"
#include "bsp_led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "application_main.h"
#include "queue.h"
#include "bsp_uart.h"

#define NUMERO_DADOS_VETOR              11
/* The queue is to be created to hold a maximum of 10 uint8_t variables. */
#define DECODER_QUEUE_LENGTH    10
#define DECODER_ITEM_SIZE       sizeof(uint8_t)

uint8_t envia_dados_decodificador(uint8_t dado);
uint8_t envia_dados_decodificador_isr(uint8_t dado);
void decodification_task(void *args);

#endif /* APPLICATION_MAIN_DECODIFICATION_TASK_H_ */
