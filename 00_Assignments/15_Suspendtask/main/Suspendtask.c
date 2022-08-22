/*
 * Problem 15. Find the tick frequency configuration for your RTOS. 
 * Create a task to suspend itself after 1200 ms and resume it from another task.
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2022	
 */


/************************** SOLUTION ******************************
* 
* Tick frequency configuration : 100 HZ
*/
 

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle;

void task_1(void *data)
{
    while (1)
    {
        printf("Entered in First Task\n");
        vTaskDelay(1200 / portTICK_PERIOD_MS);
        vTaskSuspend(task1_handle);
        printf("Suspended Task_1\n");
    }
}

void task_2(void *data)
{
    while (1)
    { 
        printf("This is the Second Task\n");
        vTaskResume(task1_handle);
        printf("Task_1 is Resumed\n");
    }
}

void app_main()
{
    BaseType_t res1, res2;
    UBaseType_t mt_prio;
    mt_prio = uxTaskPriorityGet(NULL);
    printf("This is the Main Task\n");
    printf("Task created successfully:Prio:%d\n", mt_prio);
    printf("\n*************************************\n");
    
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 4, &task1_handle);
    res2 = xTaskCreate(task_2, "Second Task", 2048, NULL, 3, &task2_handle);
    if (res1 !=pdPASS || res2 != pdPASS)
    {
        perror("Error in Creating Tasks :");
    }
}
