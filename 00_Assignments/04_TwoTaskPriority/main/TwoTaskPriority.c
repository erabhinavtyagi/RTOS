/*
 * Problem 4. Create two task with priority 10 and 20. Each task prints its own custom message.
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2022	
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle;
//TaskHandle_t task3_handle;

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
    vTaskDelete(task1_handle);
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
    vTaskDelete(task2_handle);
}

// void task_3(void *data)
// {
//     UBaseType_t prio3;
//     while (1)
//     {
//         printf("\nThis is the Third Task\n");
//         prio3 = uxTaskPriorityGet(task3_handle);
//         printf("Task3 Priority: %d\n", prio3);
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
//     vTaskDelete(task3_handle);
// }

void app_main()
{
    BaseType_t res1, res2;
    //BaseType_t res3;
    UBaseType_t mt_prio;
    mt_prio = uxTaskPriorityGet(NULL);
    
    printf("This is the Main Task\n");
    printf("Task created successfully:Prio:%d\n", mt_prio);
    printf("\n*************************************\n");
    
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 4, &task1_handle);
    res2 = xTaskCreate(task_2, "Second Task", 2048, NULL, 3, &task2_handle);
    //res3 = xTaskCreate(task_3, "Third Task", 2048, NULL, 2, &task3_handle);
 
    if (res1 != pdPASS || res2 != pdPASS)
    {
        perror("Error in Creating Tasks.\n");
    }
}