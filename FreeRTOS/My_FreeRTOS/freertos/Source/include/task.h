#ifndef TASK_H
#define TASK_H

#include "list.h"
#include "FreeRTOS.h"

#define tskIDLE_PRIORITY			       ( ( UBaseType_t ) 0U )
#define taskYIELD()					       portYIELD()

#define taskENTER_CRITICAL() portENTER_CRITICAL() 
#define taskENTER_CRITICAL_FROM_ISR() portSET_INTERRUPT_MASK_FROM_ISR()

#define taskEXIT_CRITICAL()			       portEXIT_CRITICAL()
#define taskEXIT_CRITICAL_FROM_ISR( x )    portCLEAR_INTERRUPT_MASK_FROM_ISR( x )

#define taskYIELD()			portYIELD()//宏定义 启动pendsv中断

/* 任务句柄 */
typedef void * TaskHandle_t;


#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(	TaskFunction_t pxTaskCode,
					            const char * const pcName,
					            const uint32_t ulStackDepth,
					            void * const pvParameters,
								UBaseType_t uxPriority,              /* 任务优先级，数值越大，优先级越高 */
					            StackType_t * const puxStackBuffer,
					            TCB_t * const pxTaskBuffer );
#endif /* configSUPPORT_STATIC_ALLOCATION */
                                
void prvInitialiseTaskLists( void );                                
void vTaskStartScheduler( void );
void vTaskSwitchContext( void );
void vTaskDelay( const TickType_t xTicksToDelay );
BaseType_t xTaskIncrementTick( void );
#endif
