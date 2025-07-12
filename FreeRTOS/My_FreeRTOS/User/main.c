#include "list.h"
#include "FreeRTOS.h"
#include "task.h"
portCHAR flag1;
portCHAR flag2;
portCHAR flag3;


/*
*************************************************************************
*                        任务控制块 & STACK 
*************************************************************************
*/
/*定义任务栈,预先定义好的一个全局数组*/
TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE                    128
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE                    128
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB;

TaskHandle_t Task3_Handle;
#define TASK3_STACK_SIZE                    128
StackType_t Task3Stack[TASK3_STACK_SIZE];
TCB_t Task3TCB;


/*函数声明*/
void delay(uint32_t count);
void Task1_Entry(void *p_arg);
void Task2_Entry(void *p_arg);
void Task3_Entry(void *p_arg);

extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

 /************************************************************************
 * main 函数
 ************************************************************************
 */
 int main(void)
 {
	 prvInitialiseTaskLists();
	 Task1_Handle = xTaskCreateStatic(Task1_Entry,
						"Task1",
						TASK1_STACK_SIZE,
	 					NULL,
						(UBaseType_t) 2,
						Task1Stack,
						&Task1TCB);
//	 vListInsert(&pxReadyTasksLists[1],&Task1TCB.xStateListItem);
	 Task2_Handle = xTaskCreateStatic(Task2_Entry,
						"Task2",
						TASK2_STACK_SIZE,
	 					NULL,
						(UBaseType_t) 2,
						Task2Stack,
						&Task2TCB);
	 Task3_Handle = xTaskCreateStatic(Task3_Entry,
						"Task3",
						TASK3_STACK_SIZE,
	 					NULL,
						(UBaseType_t) 2,
						Task3Stack,
						&Task3TCB);
//	 vListInsert(&pxReadyTasksLists[2],&Task2TCB.xStateListItem);
	 portDISABLE_INTERRUPTS();
	 vTaskStartScheduler();
	for (;;)
	{
		/* 啥事不干 */
	}
 }
 void delay(uint32_t count)
 {
	 for(;count!=0;count--);
 }
 /*定义一个任务函数*/
 void Task1_Entry(void *p_arg)
 {
	 for(;;)
	 {
		 flag1 =1 ;
		 vTaskDelay(1);
		 //delay(100);
		 flag1 =0;
		 //delay(100);
		 vTaskDelay(1);
		 /*不返回的函数*/
	 }
 }	 
  void Task2_Entry(void *p_arg)
 {
	 for(;;)
	 {
		 flag2 =1 ;
		 //delay(100);
		 vTaskDelay(1);
		 flag2 =0;
		 //delay(100);
		 vTaskDelay(1);
		 /*不返回的函数*/
	 }
 }	
   void Task3_Entry(void *p_arg)
 {
	 for(;;)
	 {
		 flag3 =1 ;
		 vTaskDelay(1);
		 //delay(100);
		 flag3 =0;
		 vTaskDelay(1);
		 //delay(100);
		 /*不返回的函数*/
	 }
 }
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
TCB_t IdleTaskTCB;
void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
                                    StackType_t **ppxIdleTaskStackBuffer, 
                                    uint32_t *pulIdleTaskStackSize )
{
		*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
		*ppxIdleTaskStackBuffer=IdleTaskStack; 
		*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}
