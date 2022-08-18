
/*
 * Problem 4. Program for implementing Queue with Idenfication bit and message bit. 
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2021	
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"

#define QueueLength 4
#define ItemSize 64

struct {
    char id;
    int data;
}pData,tData; 

TaskHandle_t pressure_task1handle, temperature_task2handle, processing_task3handle;
//TaskHandle_t highprio_task4handle;
QueueHandle_t sensor_q;

void pressure_task1(void *data)
{   
    //struct pData = {'0',200};
    pData.id = 'P';          // Pressure ID
    pData.data = 100;      // Pressure Data

    printf("pressure_Task1: Starting the Pressure Task \n");
    while(1)
    {
        pData.data++;
        // send Pressure Data to queue
        //BaseType_t xQueueSend(QueueHandle_t xQueue, const void * pvItemToQueue, TickType_t xTicksToWait);
        xQueueSend(sensor_q , &pData, pdMS_TO_TICKS(5000));
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    vTaskDelete(NULL);
}

void temperature_task2(void *data)
{
    //struct pData = {'1',200};
    tData.id = 'T';          // Temperature ID
    tData.data = 200;      // Temperature Data
    
    printf("temperature_Task2: Starting the Temperature Task \n");
    while(1)
    {
        tData.data++;    
        // send Temperature Data to queue
        xQueueSend(sensor_q , &tData, pdMS_TO_TICKS(5000));
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    vTaskDelete(NULL);
}


void processing_task3(void *data)
{
    int buffer[2];
    printf("processing_Task3: Starting the Processing Task \n");
    while(1)
    {
        // Receive data to queue
        //BaseType_t xQueueReceive(QueueHandle_t xQueue,void *pvBuffer,TickType_t xTicksToWait);
        xQueueReceive(sensor_q, &buffer, portMAX_DELAY);
        printf("Processing Task Received ID: %c\n", buffer[0]);
        printf("Processing Task Received Data: %d\n", buffer[1]);
    }
    vTaskDelete(NULL);
}


// void highprio_task4(void *data)
// {
//     int buffer;
//     int count = 0;
//     printf("Highprio_Task4: Starting the High Priority Task \n");
//     while(1)
//     {
//         // Receive data to queue
//         //BaseType_t xQueueReceive(QueueHandle_t xQueue,void *pvBuffer,TickType_t xTicksToWait);
//         xQueueReceive(sensor_q, &buffer, pdMS_TO_TICKS(1000));
//         printf("High Priority Task Received Data: %d\n", buffer);
//         count++;
//         // if count is greater than 50, then delay/suspend the high priority task for 10sec.
//         if(count >50)
//         {
//             vTaskDelay(pdMS_TO_TICKS(10000));
//             count = 0;  /* else it will be TRUE always for Processing Task for the value count > 50, 
//             and High priority Task will get less number of chance.*/
//         }
//     }
//     vTaskDelete(NULL);
// }

void app_main()
{
    BaseType_t res;
    UBaseType_t mt_prio;
    printf("DESD RTOS PROJECT\n");
    
    mt_prio = uxTaskPriorityGet(NULL);
    printf("MT: Task created successfully: prio : %d\n", mt_prio);
    
    // Create Queue
    sensor_q = xQueueCreate( QueueLength, ItemSize );
    
    res = xTaskCreate(pressure_task1, "pressure_TASK1", 2048, NULL,8, &pressure_task1handle);
    res = xTaskCreate(temperature_task2, "temperature_TASK2", 2048, NULL,8, &temperature_task2handle);
    res = xTaskCreate(processing_task3, "processing_task3", 2048, NULL,8, &processing_task3handle);
//    res = xTaskCreate(highprio_task4, "highprio_task4", 2048, NULL,10, &highprio_task4handle);
}
