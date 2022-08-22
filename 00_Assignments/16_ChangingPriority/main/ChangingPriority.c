/*
 * Problem 16. Write a RTOS application to demonstrate the use of changing priority.
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2022	
 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle;

void task_1(void *data)
{
    UBaseType_t prio;
    while (1)
    {
        printf("This is the First Task\n");

        //Change priority to 2. Earlier it was 4.
        vTaskPrioritySet(task1_handle, 2);
        
        prio = uxTaskPriorityGet(task1_handle);
        printf("Task-1 prio : %d\n", prio);
        
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task_2(void *data)
{
    UBaseType_t prio;
    while (1)
    {
        printf("This is the Second Task\n");
        prio = uxTaskPriorityGet(task2_handle);
        printf("Task-2 prio : %d\n", prio);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main()
{
    BaseType_t res1, res2;
    printf("This is the Main Task\n");
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 4, &task1_handle);
    res2 = xTaskCreate(task_2, "Second Task", 2048, NULL, 3, &task2_handle);
    if (res1 !=pdPASS || res2 != pdPASS)
    {
        perror("Error in Creating Tasks :");
    }
}
