/*
 * bsp_uart.c
 *
 *  Created on: 23 de mai de 2019
 *      Author: JulioLeme
 */
#include "bsp_uart.h"
#include "decodification_task.h"

#include "stm32f1xx.h"

volatile uint8_t txData;
volatile uint8_t rxData;

void USART1_IRQHandler(void)
{
    uint32_t flags = USART1->SR;
    USART1->SR &= ~(uint32_t)USART_SR_RXNE;
    NVIC_ClearPendingIRQ(USART1_IRQn);

    if((flags & USART_SR_RXNE) == USART_SR_RXNE){
        rxData = USART1->DR;
        envia_dados_decodificador_isr(rxData);
    }
}



/*
if((USART1->SR & USART_SR_TXE) == USART_SR_TXE){
    USART1->DR = txData;
}
*/


void bsp_uart_configure(void)
{
    NVIC_DisableIRQ(USART1_IRQn);
    // ------------ Apply reset. ------------------------
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
    RCC->APB2RSTR |= (uint32_t)RCC_APB2RSTR_USART1RST;
    // ------------ Exit reset. --------------------------
    RCC->APB2RSTR &= ~((uint32_t)RCC_APB2RSTR_USART1RST);

    // ------------ Configure. ---------------------------
    uint32_t tmp1, tmp2;

    /********************************************
     * Configure UART1 pins.                    *
     ********************************************/
    // UART1 TX.
    GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9);
    GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0;
    // UART1 RX.
    GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    /********************************************
     * Configure UART1.                         *
     ********************************************/
    tmp2 = USART_CLOCK / BAUD_RATE;
    tmp1  = USART_CLOCK % BAUD_RATE;
    if(tmp2 >=  (BAUD_RATE/2)) tmp1++;

    USART1->BRR |= tmp2 & 0x0000FFFF;

    USART1->SR &= ~(USART_SR_TXE | USART_SR_TC | USART_SR_RXNE | USART_SR_ORE);
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    //USART1->CR1 |= USART_CR1_RXNEIE;
    /********************************************
     * Configure NVIC UART1 interrupt.               *
     ********************************************/
    NVIC_SetPriority(USART1_IRQn, BSP_USART1_IRQ_PRIORITY);
    NVIC_ClearPendingIRQ(USART1_IRQn);
    NVIC_EnableIRQ(USART1_IRQn);

    USART1->CR1 |= USART_CR1_UE;
    //----------------------------------------------------------------
}

