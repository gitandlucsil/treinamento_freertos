/*
 * task2.c
 *
 *  Created on: 7 de mai de 2019
 *      Author: andre
 */
#include "decodification_task.h"

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

uint8_t dataReceived;

uint8_t envia_dados_decodificador(uint8_t dado)
{
	uint8_t result = FALSE;
	if(decoderQueueHandle != NULL){
		if(xQueueSend(decoderQueueHandle,(void *)&dado,(TickType_t)0) == pdTRUE){
			result = TRUE;
		}
	}
	return result;
}
uint8_t envia_dados_decodificador_isr(uint8_t dado)
{
    uint8_t resultado = FALSE;
    if(decoderQueueHandle != NULL){
        if(xQueueSendFromISR(decoderQueueHandle, &dado, NULL) == pdTRUE){
            resultado = TRUE;
        }
    }
    return resultado;
}
void decodification_task(void *args)
{
    /* Create a queue capable of containing 10 uint8_t values. */
	decoderQueueHandle = xQueueCreateStatic( DECODER_QUEUE_LENGTH,
											 DECODER_ITEM_SIZE,
											 decoderQueueStorageArea,
											 &decoderStaticQueue );
    /* decoderQueueStorageArea was not NULL so decoderQueueHandle should not be NULL. */
    configASSERT( decoderQueueHandle );
	while(1){
	    if(xQueueReceive(decoderQueueHandle,&dataReceived,(TickType_t)10) == pdTRUE){
            exec_decodificador_avirede(dataReceived);
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
        vTaskDelay(10);
	}
}
