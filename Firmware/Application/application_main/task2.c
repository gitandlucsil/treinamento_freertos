/*
 * task2.c
 *
 *  Created on: 7 de mai de 2019
 *      Author: andre
 */
#include "task2.h"

const uint8_t serialData[NUMERO_DADOS_VETOR] = {0x00, 0x35, 0x25, 0xAA, 0x01, 0x00, 0x01, 0x35, 0x00, 0x35, 0x55};
volatile uint8_t run = TRUE;
volatile uint8_t modeloDecodificado = 0;
volatile uint8_t idDecodificado = 0;
volatile uint8_t dadosDecodificados[255];
volatile uint8_t nDadosDecodificado = 0;
/* The variable used to hold the queue's data structure. */
static StaticQueue_t decoderStaticQueue;
/* The array to use as the queue's storage area.  This must be at least uxQueueLength * uxItemSize bytes. */
uint8_t decoderQueueStorageArea[DECODER_QUEUE_LENGTH * DECODER_ITEM_SIZE];
QueueHandle_t decoderQueueHandle;


void task_2(void *args)
{
    /* Create a queue capable of containing 10 uint8_t values. */
	decoderQueueHandle = xQueueCreateStatic( DECODER_QUEUE_LENGTH,
											 DECODER_ITEM_SIZE,
											 decoderQueueStorageArea,
											 &decoderStaticQueue );
    /* decoderQueueStorageArea was not NULL so decoderQueueHandle should not be NULL. */
    configASSERT( decoderQueueHandle );
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
        vTaskDelay(10);
	}
}
