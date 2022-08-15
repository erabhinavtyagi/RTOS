/*
 * Problem 21. Write a RTOS application to demonstrate counting semaphores to synchronize a task.
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2021	
 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"

TaskHandle_t task1handle, task2handle, task3handle, task4handle;
SemaphoreHandle_t serial_counting_sem;


void task1(void *data)
{
    printf("Task1: Starting the  task1 \n");
    printf("Task1 Requesting for the serial port\n");
    xSemaphoreTake(serial_counting_sem, pdMS_TO_TICKS(20000));
    printf("Task1 Got the serial port\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xSemaphoreGive(serial_counting_sem);
    printf("Task1 Released the serial port\n");
    vTaskDelete(NULL);
}

void task2(void *data)
{
    printf("Task2: Starting the  task2 \n");
    printf("Task2 Requesting for the serial port\n");
    xSemaphoreTake(serial_counting_sem, pdMS_TO_TICKS(20000));
    printf("Task2 Got the serial port\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    xSemaphoreGive(serial_counting_sem);
    printf("Task2 Released the serial port\n");
    vTaskDelete(NULL);
}

void task3(void *data)
{
    printf("Task3: Starting the  task3 \n");
    printf("Task3 Requesting for the serial port\n");
    xSemaphoreTake(serial_counting_sem, pdMS_TO_TICKS(20000));
    printf("Task3 Got the serial port\n");
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    xSemaphoreGive(serial_counting_sem);
    printf("Task3 Released the serial port\n");
    vTaskDelete(NULL);
}

void task4(void *data)
{
    printf("Task4: Starting the  task4 \n");
    printf("Task4 Requesting for the serial port\n");
    xSemaphoreTake(serial_counting_sem, pdMS_TO_TICKS(20000));
    printf("Task4 got the serial port\n");
    vTaskDelay(8000 / portTICK_PERIOD_MS);
    xSemaphoreGive(serial_counting_sem);
    printf("Task4 released the serial port\n");
    vTaskDelete(NULL);
}

int app_main()
{
    BaseType_t res;
    UBaseType_t mt_prio;
    printf("DESD RTOS PROJECT\n");
    mt_prio = uxTaskPriorityGet(NULL);
    printf("MT: Task created successfully: prio : %d\n", mt_prio);
    serial_counting_sem = xSemaphoreCreateCounting(2,2);
    res = xTaskCreate(task1, "TASK1", 2048, NULL,5, &task1);
    res = xTaskCreate(task2, "TASK2", 2048, NULL,5, &task2);
    res = xTaskCreate(task3, "TASK3", 2048, NULL,5, &task3);
    res = xTaskCreate(task4, "TASK4", 2048, NULL,5, &task4);
    return 0;
}
