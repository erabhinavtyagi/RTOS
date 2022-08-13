 /* BINARY SEMAPHORE

   1. . ~/esp/esp-idf/export.sh
   2. idf.py menuconfig - go to component setting and change according to our requirement and save it, then quit.
   3.idf.py build
   4.idf.py flash
   5.idf.py monitor */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"

TaskHandle_t adc_task_handle, processing_task_handle;
SemaphoreHandle_t adcSignal;


void adc_task(void *data)
{
    printf("AT: Starting the ADC task \n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xSemaphoreGive(adcSignal);
    printf("AT: Posted signal to processing task\n");
    vTaskDelete(NULL);
}

void processing_task(void *data)
{
    printf("PT: Starting The Processing Task\n");
    xSemaphoreTake(adcSignal,0);
    printf("PT: Got the signal\n");
    vTaskDelete(NULL);
}

int app_main()
{
    BaseType_t res;
    UBaseType_t mt_prio;
    printf("DESD RTOS PROJECT\n");
    mt_prio = uxTaskPriorityGet(NULL);
    printf("MT: Task created successfully: prio : %d\n", mt_prio);
    
    adcSignal = xSemaphoreCreateBinary();
    res = xTaskCreate(adc_task, "ADCTASK", 2048, NULL,8, &adc_task_handle);
    res = xTaskCreate(processing_task, "PROCESSINGTASK", 2048, NULL,5, &processing_task_handle);
    return 0;
}
