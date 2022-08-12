/*
 * To Create a Task1 and Task2. Task1 after completion should Resume Task2.  
 *
 * 1. . ~/esp/esp-idf/export.sh
 * 2. idf.py menuconfig - go to component setting and change according to our requirement and save it, then quit.
 * 3. idf.py build && idf.py flash && idf.py monitor
 * Press "ctrl+]" to stop the monitoring mode.
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