/*
 * task1.c
 *
 *  Created on: 2 de mai de 2019
 *      Author: JulioLeme
 */
#include "task1.h"
const uint8_t serialData[NUMERO_DADOS_VETOR] = {0x00, 0x35, 0x25, 0xAA, 0x01, 0x00, 0x01, 0x35, 0x00, 0x35, 0x55};
volatile uint8_t run = TRUE;
volatile uint8_t modeloDecodificado = 0;
volatile uint8_t idDecodificado = 0;
volatile uint8_t dadosDecodificados[255];
volatile uint8_t nDadosDecodificado = 0;

void task_1(void *args)
{

    while(1){
        bsp_led_fsm_run();
        bsp_led_requisita(
                1,
                500,
                500,
                30,
                150,
                3);
        if(run == TRUE){
            run = FALSE;

            uint8_t i;
            for(i=0; i<NUMERO_DADOS_VETOR; i++){
                exec_decodificador_avirede(serialData[i]);
                if(frame_decodificado() == TRUE){
                    modeloDecodificado = recebe_modelo_frame();
                    idDecodificado = recebe_id_frame();
                    nDadosDecodificado = recebe_dados_frame((uint8_t *)dadosDecodificados);
                    bsp_led_requisita(
                            2,
                            500,
                            500,
                            30,
                            30,
                            20);
                }
            }
        }
    }
}

