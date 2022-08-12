/*
 * To Create a Task1, Task2 and Task3. Schedule them in Round-Robin method.
 *  - Task1 after completion should Resume Task2.  
 *  - Task2 after completion should Resume Task3.  
 *  - Task3 after completion should Resume Task1.
 *   
 * 1. . ~/esp/esp-idf/export.sh
 * 2. idf.py menuconfig - go to component setting and change according to our requirement and save it, then quit.
 * 3. idf.py build && idf.py flash && idf.py monitor
 * Press "ctrl+]" to stop the monitoring mode.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task1_handle, task2_handle, task3_handle;

void task_1(void *data)
{
    int count = 0;
    UBaseType_t prio_1;
    prio_1 = uxTaskPriorityGet(task1_handle);
    while (1)
    {
        count += 1;
        if (count > 5)
        {
            printf("Task 2 Resumed\n");
            vTaskResume(task2_handle);
            vTaskSuspend(task1_handle);
            count = 0;
        }
        printf("This is the First Task & Priority is %d\n", prio_1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void task_2(void *data)
{
    vTaskSuspend(task2_handle);
    int count = 0;
    UBaseType_t prio_2;
    prio_2 = uxTaskPriorityGet(task2_handle);
    while (1)
    {
        count += 1;
        if (count > 5)
        {
            printf("Task 3 Resumed\n");
            vTaskResume(task3_handle);
            vTaskSuspend(task2_handle);
            count = 0;
        }
        printf("This is the Second Task & Priority is %d\n", prio_2);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void task_3(void *data)
{
    vTaskSuspend(task3_handle);
    int count = 0;
    UBaseType_t prio_3;
    prio_3 = uxTaskPriorityGet(task3_handle);
    while (1)
    {
        count += 1;
        if (count > 5)
        {
            printf("Task 3 Resumed\n");
            vTaskResume(task1_handle);
            vTaskSuspend(task3_handle);
            count = 0;
        }
        printf("This is the Third Task & Priority is %d\n", prio_3);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    BaseType_t res1, res2, res3;
    printf("This is the Main Task\n");
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 4, &task1_handle);
    res2 = xTaskCreate(task_2, "Second Task", 2048, NULL, 3, &task2_handle);
    res3 = xTaskCreate(task_3, "Third Task", 2048, NULL, 5, &task3_handle);
    if (res1 != pdPASS || res2 != pdPASS || res3 != pdPASS)
    {
        perror("Error in Creating Tasks : ");
    }
}