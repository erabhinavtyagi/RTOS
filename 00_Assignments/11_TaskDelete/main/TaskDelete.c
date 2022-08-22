/*
 * Problem 11: What is the API for deleting a task? Write a program demonstrate this capability.
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2022	
 */

/************************** SOLUTION *******************************
 * void vTaskDelete( TaskHandle_t pxTask ); 
 * 
 * It will delete an instance of a task that was previously created using a call to 
 * xTaskCreate() or xTaskCreateStatic().
 * 
 * When a task is deleted, it is the responsibility of the idle task to free the memory 
 * that had been used to hold the deleted task’s stack and data structures (task control block).
 * Therefore, if an application makes use of the vTaskDelete() API function, it is vital that
 * the application also ensures the idle task is not starved of processing time 
 * (the idle task must be allocated time in the Running state).
 *  
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
        printf("\nThis is the First Task\n");
        prio = uxTaskPriorityGet(task1_handle);
        printf("Task1 Priority: %d\n", prio);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    BaseType_t res1;

    UBaseType_t mt_prio;
    mt_prio = uxTaskPriorityGet(NULL);
    
    printf("This is the Main Task\n");
    printf("Task created successfully:Prio:%d\n", mt_prio);
    printf("\n*************************************\n");
    
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 3, &task1_handle);
   
    if (res1 !=pdPASS)
    {
        perror("Error in Creating Tasks.\n");
    }
    else
    {
        /* Delete the task just created. Use the handle passed out of xTaskCreate()
        to reference the subject task. */
        vTaskDelete(task1_handle);
        printf("Task1 Deleted\n");
    }
}