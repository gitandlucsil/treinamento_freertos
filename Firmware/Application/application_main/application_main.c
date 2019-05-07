/*
 * application_main.c
 *
 *  Created on: 2 de abr de 2019
 *      Author: JulioLeme
 */
#include "application_main.h"

TaskHandle_t xTask1Handle = NULL;
StaticTask_t xTask1Buffer;
StackType_t xTask1Stack[TASK1_STACK_SIZE];

TaskHandle_t xTask2Handle = NULL;
StaticTask_t xTask2Buffer;
StackType_t xTask2Stack[TASK2_STACK_SIZE];

void app_run(void)
{
    /* Create the task without using any dynamic memory allocation. */
    xTask1Handle = xTaskCreateStatic(
                  task_1,                /* Function that implements the task. */
                  "TASK1",               /* Text name for the task. */
                  TASK1_STACK_SIZE,      /* Number of indexes in the xStack array. */
                  (void *) NULL,         /* Parameter passed into the task. */
                  TASK1_PRIORITY,        /* Priority at which the task is created. */
                  xTask1Stack,           /* Array to use as the task's stack. */
                  &xTask1Buffer);        /* Variable to hold the task's data structure. */
    /* Create the task without using any dynamic memory allocation. */
    xTask2Handle = xTaskCreateStatic(
                  task_2,                /* Function that implements the task. */
                  "TASK2",               /* Text name for the task. */
                  TASK2_STACK_SIZE,      /* Number of indexes in the xStack array. */
                  (void *) NULL,         /* Parameter passed into the task. */
                  TASK2_PRIORITY,        /* Priority at which the task is created. */
                  xTask2Stack,           /* Array to use as the task's stack. */
                  &xTask2Buffer);        /* Variable to hold the task's data structure. */

    vTaskStartScheduler();

    while(1);
}


/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

