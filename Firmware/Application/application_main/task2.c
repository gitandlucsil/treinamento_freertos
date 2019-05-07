/*
 * task2.c
 *
 *  Created on: 7 de mai de 2019
 *      Author: andre
 */
#include "task2.h"

void task_2(void *args)
{
	while(1){
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
