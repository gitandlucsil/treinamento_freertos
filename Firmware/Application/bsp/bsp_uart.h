/*
 * bsp_uart.h
 *
 *  Created on: 23 de mai de 2019
 *      Author: JulioLeme
 */

#ifndef BSP_BSP_UART_H_
#define BSP_BSP_UART_H_

#include "FreeRTOS.h"

#define BSP_USART1_IRQ_PRIORITY       configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
#define USART_CLOCK                   72000000
#define BAUD_RATE                     9600

void bsp_uart_configure(void);

#endif /* BSP_BSP_UART_H_ */
