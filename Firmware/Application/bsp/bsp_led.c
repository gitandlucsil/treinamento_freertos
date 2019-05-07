/*
 * bsp_led.c
 *
 *  Created on: 4 de abr de 2019
 *      Author: JulioLeme
 */
#include "bsp_led.h"
#include "lib_utilities.h"

#include "stm32f1xx.h"

#define ESTADO_CONFIGURANDO             0
#define ESTADO_AGUARDA_REQUISICAO       1
#define ESTADO_AGUARDA_T_ANTES          2
#define ESTADO_LIGAR_LED                3
#define ESTADO_AGUARDA_T_LIGADO         4
#define ESTADO_DESLIGA_LED              5
#define ESTADO_AGUARDA_T_DESLIGADO      6
#define ESTADO_AGUARDA_T_DEPOIS         7

static uint8_t estado = ESTADO_CONFIGURANDO;

uint8_t emFuncionamento = FALSE;
uint8_t pPrioridade = 0;
uint32_t pAtrasoAntes = 0;
uint32_t pAtrasoDepois = 0;
uint32_t pTempoLigado = 0;
uint32_t pTempoDesligado = 0;
uint8_t pCiclos = 0;


uint8_t bsp_led_requisita(
        uint8_t prioridade,
        uint32_t atrasoAntes,
        uint32_t atrasoDepois,
        uint32_t tempoLigado,
        uint32_t tempoDesligado,
        uint8_t ciclos)
{
    uint8_t resultado = FALSE;

    if(emFuncionamento == TRUE){
        if(prioridade > pPrioridade){
            resultado = TRUE;
        }
    }else{
        resultado = TRUE;
    }

    if(resultado == TRUE){
        pPrioridade = prioridade;
        pAtrasoAntes = atrasoAntes;
        pAtrasoDepois = atrasoDepois;
        pTempoLigado = tempoLigado;
        pTempoDesligado = tempoDesligado;
        pCiclos = ciclos;

        emFuncionamento = TRUE;
    }

    return resultado;
}

uint32_t marcoDeTempo = 0;

void liga_led(void)
{
    GPIOC->BSRR |= GPIO_BSRR_BR13;
}

void desliga_led(void)
{
    GPIOC->BSRR |= GPIO_BSRR_BS13;
}

void configura_led(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(uint32_t)GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13_1;
}

void bsp_led_fsm_run(void)
{
    switch(estado){
        case ESTADO_CONFIGURANDO:
        	configura_led();
            estado = ESTADO_AGUARDA_REQUISICAO;
            break;

        case ESTADO_AGUARDA_REQUISICAO:
            if(emFuncionamento == TRUE){
                desliga_led();
                marcoDeTempo = get_current_time();
                estado = ESTADO_AGUARDA_T_ANTES;
            }
            break;

        case ESTADO_AGUARDA_T_ANTES:
            if(elapsed_time(marcoDeTempo) >= pAtrasoAntes){
                estado = ESTADO_LIGAR_LED;
            }
            break;

        case ESTADO_LIGAR_LED:
            liga_led();
            marcoDeTempo = get_current_time();
            estado = ESTADO_AGUARDA_T_LIGADO;
            break;

        case ESTADO_AGUARDA_T_LIGADO:
            if(elapsed_time(marcoDeTempo) >= pTempoLigado){
                estado = ESTADO_DESLIGA_LED;
            }
            break;

        case ESTADO_DESLIGA_LED:
            desliga_led();
            marcoDeTempo = get_current_time();
            estado = ESTADO_AGUARDA_T_DESLIGADO;
            break;

        case ESTADO_AGUARDA_T_DESLIGADO:
            if(elapsed_time(marcoDeTempo) >= pTempoDesligado){
                pCiclos--;
                if(pCiclos > 0){
                    estado = ESTADO_LIGAR_LED;
                }else{
                    marcoDeTempo = get_current_time();
                    estado = ESTADO_AGUARDA_T_DEPOIS;
                }
            }
            break;

        case ESTADO_AGUARDA_T_DEPOIS:
            if(elapsed_time(marcoDeTempo) >= pAtrasoDepois){
            	emFuncionamento = FALSE;
                estado = ESTADO_AGUARDA_REQUISICAO;
            }
            break;

        default:
            estado = ESTADO_CONFIGURANDO;
    }

}


