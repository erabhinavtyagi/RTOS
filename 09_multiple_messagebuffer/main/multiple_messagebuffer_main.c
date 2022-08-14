// Program for Multiple Message Buffer

 /*1. . ~/esp/esp-idf/export.sh
   2. idf.py menuconfig - go to component setting and change according to our requirement and save it, then quit.
   3.idf.py build && idf.py flash && idf.py monitor 
   NOTE:- idf.py fullclean....if build failed or we want to rebuld*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/message_buffer.h"
#include "pthread.h"

TaskHandle_t task1handle, task2handle;
MessageBufferHandle_t mb_t1_t2;


void task1(void *data)
{
    printf("Task1: Starting the Task1 \n");
    printf("Task1 Sending message\n");
    xMessageBufferSend(mb_t1_t2, "1st data\n", 10, pdMS_TO_TICKS(20000));
    xMessageBufferSend(mb_t1_t2, "2nd data\n", 10, pdMS_TO_TICKS(20000));
    xMessageBufferSend(mb_t1_t2, "3rd data\n", 10, pdMS_TO_TICKS(20000));
    printf("Task1 finished sending message\n");
    vTaskDelete(NULL);
}

void task2(void *data)
{
    unsigned char rbuff[200];
    size_t nbytes = 0;
    printf("Task2: Starting the Task2 \n");
    while(1)
    {
    printf("Task2 requesting data to be received\n");
    nbytes = xMessageBufferReceive(mb_t1_t2, rbuff, 200 , pdMS_TO_TICKS(20000));
    printf("Task2 received data bytes size: %d: : %s\n", nbytes, rbuff);
    }
    vTaskDelete(NULL);
}


void app_main()
{
    BaseType_t res;
    UBaseType_t mt_prio;
    printf("DESD RTOS PROJECT\n");
    mt_prio = uxTaskPriorityGet(NULL);
    printf("MT: Task created successfully: prio : %d\n", mt_prio);
    mb_t1_t2 = xMessageBufferCreate(200);
    res = xTaskCreate(task1, "TASK1", 2048, NULL,8, &task1);
    res = xTaskCreate(task2, "TASK2", 2048, NULL,8, &task2);
    
}