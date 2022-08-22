/*
 * Problem 17. If your RTOS supports idle task hooking, write a program to demonstrate it.
 *
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 23, 2022	
 */

/* Create two tasks with priorities 3 and 4. 
   * Enable the Idle Task Hook by setting configUSE_IDLE_HOOK to 1, by this the loop function can be used as Idle task*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle;

void vApplicationIdleHook()
{
    printf("I am Idle.\n");
    vTaskDelay(100 / portTICK_PERIOD_MS);
}

void task_1(void *data)
{
    UBaseType_t prio1;
    while (1)
    {
        printf("\nThis is the First Task\n");
        prio1 = uxTaskPriorityGet(task1_handle);
        printf("Task1 Priority: %d\n", prio1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    UBaseType_t prio2;
    while (1)
    {
        printf("\nThis is the Second Task\n");
        prio2 = uxTaskPriorityGet(task2_handle);
        printf("Task2 Priority: %d\n", prio2);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main()
{
    BaseType_t res1, res2;
    UBaseType_t mt_prio;
    mt_prio = uxTaskPriorityGet(NULL);
    
    printf("This is the Main Task\n");
    printf("Task created successfully:Prio:%d\n", mt_prio);
    printf("\n*************************************\n");
    
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 1, &task1_handle);
    res2 = xTaskCreate(task_2, "Second Task", 2048, NULL, 2, &task2_handle);
 
    if (res1 != pdPASS || res2 != pdPASS)
    {
        perror("Error in Creating Tasks.\n");
    }
}
