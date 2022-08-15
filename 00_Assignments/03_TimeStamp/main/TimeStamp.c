/*
 * Problem 3. Find the APIs in your RTOS that provides timestamp and use it to print the periodic task.
 * Observe the jitter in the timestamp vs the periodicity. Enhance the code to 10 periodic tasks
 * with different periodicity. Futher observe the jitter in each of the task.
`* 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2021	
 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle;

void task_1(void *data)
{
    int count = 0;
    while (1)
    {
        printf("This is the First Task\n");
        count += 1;
        if (count > 5)
        {
            vTaskResume(task2_handle);
            printf("Task 2 Resumed\n");
            count = 0;
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void task_2(void *data)
{
    while (1)
    {
        vTaskSuspend(task2_handle);
        printf("This is the Second Task\n");
    }
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
