 /*1. . ~/esp/esp-idf/export.sh
   2. idf.py menuconfig - go to component setting and change according to our requirement and save it, then quit.
   3.idf.py build
   4.idf.py flash
   5.idf.py monitor */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include "pthread.h"
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

TaskHandle_t LP_task_handle, MP_task_handle, HP_task_handle;
SemaphoreHandle_t lock;

static portMUX_TYPE spinlock = portMUX_INITIALIZER_UNLOCKED;

//settings
TickType_t cs_wait = 250;   // Time spent in critical section (ms)
TickType_t med_wait = 5000; // Time medium task spends working (ms)


//*************** Low Priority Task ********************

void LP_task(void *data)
{
    TickType_t timestamp;

  // Do forever
  while (1) {

    // Take lock
    printf("Task LP trying to take lock...\n");
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    portENTER_CRITICAL(&spinlock);
    //xSemaphoreTake(lock, portMAX_DELAY);

    // Say how long we spend waiting for a lock
    printf("Task LP got lock. Spent \n");
    printf((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);
    printf(" ms waiting for lock. Doing some work...\n");

    // Hog the processor for a while doing nothing
    //timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

    // Release lock
    printf("Task LP releasing lock.\n");
    //xSemaphoreGive(lock);
    portEXIT_CRITICAL(&spinlock);
    // Go to sleep
    vTaskDelay(500 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
  }
}

//*************** Medium Priority Task ********************

void MP_task(void *data)
{
     TickType_t timestamp;

  // Do forever
  while (1) {

    // Hog the processor for a while doing nothing
    printf("Task MP doing some work...\n");
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < med_wait);

    // Go to sleep
    printf("Task MP done!\n");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
  }
}

//*************** High Priority Task ********************

void HP_task(void *data)
{
    TickType_t timestamp;

  // Do forever
  while (1) {

    // Take lock
    printf("Task HP trying to take lock...\n");
    timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    //xSemaphoreTake(lock, portMAX_DELAY);
    portENTER_CRITICAL(&spinlock);
    // Say how long we spend waiting for a lock
    printf("Task HP got lock. Spent \n");
    printf((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);
    printf(" ms waiting for lock. Doing some work...\n");

    // Hog the processor for a while doing nothing
    //timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
    while ( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

    // Release lock
    printf("Task H releasing lock.\n");
    //xSemaphoreGive(lock);
    portENTER_CRITICAL(&spinlock);
    // Go to sleep
    vTaskDelay(500 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);
  }
}

//*************** Main Function ********************
void app_main()
{
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
    BaseType_t res;
    UBaseType_t mt_prio;
    printf("Freeinversion RTOS program....\n");
    mt_prio = uxTaskPriorityGet(NULL);
    printf("MT: Task created successfully: prio : %d\n", mt_prio);
    
    //lock = xSemaphoreCreateBinary();
    
    res = xTaskCreatePinnedToCore(LP_task, "LPTASK", 1024, NULL,1, &LP_task_handle, app_cpu);
    // Introducing a delay to force priority inversion
    vTaskDelay(1 / portTICK_PERIOD_MS);
    res = xTaskCreatePinnedToCore(HP_task, "HPTASK", 1024, NULL,3, &HP_task_handle, app_cpu);
    res = xTaskCreatePinnedToCore(MP_task, "MPTASK", 1024, NULL,2, &MP_task_handle, app_cpu);
}