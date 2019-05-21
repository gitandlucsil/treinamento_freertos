/*
 * task1.c
 *
 *  Created on: 2 de mai de 2019
 *      Author: JulioLeme
 */
#include "task1.h"

TaskHandle_t taskToSuspend = NULL;
/*void task_1(void *args)
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
}*/
static volatile uint8_t valor_recebido = 0;
static volatile uint32_t i;
uint8_t valor_conhecido(uint8_t valor)
{
	valor_recebido = valor;
	for(i=0;i<200000;i++);
	return valor_recebido;
}
void task_1(void *args)
{
	while(1){
		if(valor_conhecido('a') != 'a'){
			while(1);
		}
	}
}
