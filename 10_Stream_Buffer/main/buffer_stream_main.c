// Program for Stream Buffer. 

 /*1. . ~/esp/esp-idf/export.sh
   2. idf.py menuconfig - go to component setting and change according to our requirement and save it, then quit.
   3. idf.py build
   4. idf.py flash
   5. idf.py monitor */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/stream_buffer.h"

TaskHandle_t task1handle, task2handle, task3handle, task4handle;
StreamBufferHandle_t sb_t1_t2;


void task1(void *data)
{
    printf("Task1: Starting the  task1 \n");
    printf("Task1 Sending message\n");
    xStreamBufferSend(sb_t1_t2, "1st data\n", 9, pdMS_TO_TICKS(20000));
    xStreamBufferSend(sb_t1_t2, "2nd data\n", 9, pdMS_TO_TICKS(20000));
    xStreamBufferSend(sb_t1_t2, "3rd data\n", 9, pdMS_TO_TICKS(20000));
    printf("Task1 Finished sending message\n");
    vTaskDelete(NULL);
}

void task2(void *data)
{
    unsigned char rbuff[200];
    size_t nbytes = 0;
    printf("Task2: Starting the task2\n");
    while(1)
    {
        printf("Task2 Requesting data to be received\n");
        nbytes = xStreamBufferReceive(sb_t1_t2, rbuff, 200, pdMS_TO_TICKS(20000));
        printf("Task2 Received data bytes size: %d : : %s\n", nbytes, rbuff);
    }
    vTaskDelete(NULL);
}
    
int app_main()
{
    BaseType_t res;
    UBaseType_t mt_prio;
    printf("DESD RTOS PROJECT\n");
    mt_prio = uxTaskPriorityGet(NULL);
    printf("MT: Task created successfully: prio : %d\n", mt_prio);
    sb_t1_t2 = xStreamBufferCreate(200,25);
    res = xTaskCreate(task1, "TASK1", 2048, NULL,8, &task1);
    res = xTaskCreate(task2, "TASK2", 2048, NULL,8, &task2);

    return 0;
}
