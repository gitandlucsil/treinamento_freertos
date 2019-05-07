/*
 * bsp_led.h
 *
 *  Created on: 4 de abr de 2019
 *      Author: JulioLeme
 */

#ifndef BSP_BSP_LED_H_
#define BSP_BSP_LED_H_

#include "stdint.h"

uint8_t bsp_led_requisita(
        uint8_t prioridade,
        uint32_t atrasoAntes,
        uint32_t atrasoDepois,
        uint32_t tempoLigado,
        uint32_t tempoDesligado,
        uint8_t ciclos);

void bsp_led_fsm_run(void);


#endif /* BSP_BSP_LED_H_ */
