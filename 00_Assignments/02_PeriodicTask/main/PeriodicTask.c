/*
 * Problem 2. What is the mechanism used to make a task periodic for the RTOS you are using?
 * Write a program to make a task periodic with periodicity of 500ms.
`* 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2022	
 */

/*********** SOLUTION ****************
* In FreeRTOS, there are two APIs to create delay or make the task periodic.
* 
* 1. void vTaskDelay( const TickType_t xTicksToDelay );
* For eg. 
*    vTaskDelay( pdMS_TO_TICKS( ms ) );     // less complex in computation as per blogs.
*               or
*    vTaskDelay(ms / portTICK_PERIOD_MS);

* 2. void vTaskDelayUntil( TickType_t *pxPreviousWakeTime,  const TickType_t xTimeIncrement );
*  
* "vTaskDelay" specifies a time at which the task wishes to unblock relative to the time
* at which vTaskDelay() is called.
* Whereas vTaskDelayUntil() specifies an absolute (exact) time at which the task wishes to unblock.
* Hence it is safe to use vTaskDelayUntil().
* It should be noted that vTaskDelayUntil() will return immediately (without blocking) 
* if it is used to specify a wake time that is already in the past. Therefore a task using
* vTaskDelayUntil() to execute periodically will have to re-calculate its required wake time
* if the periodic execution is halted for any reason (for example, the task is temporarily placed
* into the Suspended state) causing the task to miss one or more periodic executions. 
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle;

void task_1(void *data)
{
    while (1)
    {
        printf("This is the First Task\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(task1_handle);
}

void task_2(void *data)
{
    while (1)
    {
        printf("This is the Second Task\n");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(task2_handle);
}

void app_main()
{
    BaseType_t res1, res2;
    printf("This is the Main Task\n");
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 4, &task1_handle);
    res2 = xTaskCreate(task_2, "Second Task", 2048, NULL, 3, &task2_handle);
    if (res1 !=pdPASS || res2 != pdPASS)
    {
        perror("Error in Creating Tasks : ");
    }
}