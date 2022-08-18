/* DEMO 15: Program for implementing Event Flags. 
`*          Pressure bit = bit 0
 *          Temperature bit = bit 1
 *
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2021	
 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"

TaskHandle_t pressure_task1handle, temperature_task2handle, processing_task3handle;
EventGroupHandle_t sensor_ef;

void pressure_task1(void *data)
{
    int pData = 200;          // Pressure Data
    printf("pressure_Task1: Starting the Pressure Task \n");
    while(1)
    {
        pData++;        // NOT used in this program
        //***** Set the Event *************
        //EventBits_t xEventGroupSetBits(EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSets);
        xEventGroupSetBits(sensor_ef, (1 << 0)); // 1 shifted by 0 bits i.e. bit 0 (first bit)
        printf("Pressure Task : Setting the bit --> Event Generated\n");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelete(NULL);
}

void temperature_task2(void *data)
{
    int tData = 100;              // Temperature Data
    printf("temperature_Task2: Starting the Temperature Task \n");
    while(1)
    {
        tData++;        // NOT used in this program
        //***** Set the Event *************
        xEventGroupSetBits(sensor_ef, (1 << 1)); // 1 shifted by 1 bit i.e. bit 1 (second bit)
        printf("Temperature Task : Setting the bit --> Event Generated\n");        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}


void processing_task3(void *data)
{
    printf("processing_Task3: Starting the Processing Task \n");
    while(1)
    {
        //****** Wait for the Event***********
        // EventBits_t xEventGroupWaitBits(
        //                const EventGroupHandle_t xEventGroup,
        //                const EventBits_t uxBitsToWaitFor,
        //                const BaseType_t xClearOnExit,
        //                const BaseType_t xWaitForAllBits,
        //                TickType_t xTicksToWait );
        
        xEventGroupWaitBits(sensor_ef, (1 << 0) | (1 << 1), pdTRUE, pdFALSE, portMAX_DELAY);
         
        printf("Processing Task: Received Event\n");
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
    
    // Create Event
    // sensor_q = xQueueCreate( QueueLength, ItemSize );
    sensor_ef = xEventGroupCreate();    
    res = xTaskCreate(pressure_task1, "pressure_TASK1", 2048, NULL,8, &pressure_task1handle);
    res = xTaskCreate(temperature_task2, "temperature_TASK2", 2048, NULL,8, &temperature_task2handle);
    res = xTaskCreate(processing_task3, "processing_task3", 2048, NULL,8, &processing_task3handle);
}
