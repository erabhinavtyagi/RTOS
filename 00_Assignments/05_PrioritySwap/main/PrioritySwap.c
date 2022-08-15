/*
 * Problem 5. Swap the priority and observe the changes in the output. What is your conclusion on the sequence of printing the messages.
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2021	
 */

/************************** SOLUTION *******************************
****** Output without SWAP : Priority Task1 - 4, Priority Task2 - 3
This is the Second Task

This is the First Task
Task1 Priority: 4
Task2 Priority: 3

This is the First Task
Task1 Priority: 4

This is the Second Task
Task2 Priority: 3

This is the First Task
Task1 Priority: 4

This is the Second Task
Task2 Priority: 3


****** Output After SWAP :  Priority Task1 - 3, Priority Task2 - 4
This is the Main Task

This is the Second Task

This is the First Task
Task2 Priority: 4

This is the Second Task
Task1 Priority: 3

This is the First Task
Task2 Priority: 4

This is the Second Task
Task1 Priority: 3

This is the First Task
Task2 Priority: 4
*/
// CONCLUSION : Higher Priority Task started first in each case.

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle;

void task_1(void *data)
{
    UBaseType_t prio;
    while (1)
    {
        printf("\nThis is the First Task\n");
        prio = uxTaskPriorityGet(task1_handle);
        printf("Task1 Priority: %d\n", prio);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(task1_handle);
}

void task_2(void *data)
{
    UBaseType_t prio;
    while (1)
    {
        printf("\nThis is the Second Task\n");
        prio = uxTaskPriorityGet(task2_handle);
        printf("Task2 Priority: %d\n", prio);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(task2_handle);
}

void app_main()
{
    BaseType_t res1, res2;

    UBaseType_t mt_prio;
    mt_prio = uxTaskPriorityGet(NULL);
    
    printf("This is the Main Task\n");
    printf("Task created successfully:Prio:%d\n", mt_prio);
    printf("\n*************************************\n");
    
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 3, &task1_handle);
    res2 = xTaskCreate(task_2, "Second Task", 2048, NULL, 4, &task2_handle);
    if (res1 !=pdPASS || res2 != pdPASS)
    {
        perror("Error in Creating Tasks.\n");
    }
}