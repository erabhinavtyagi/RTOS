/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
 /*1. . ~/esp/esp-idf/export.sh
   2. idf.py menuconfig - go to component setting and change according to our requirement and save it, then quit.
   3.idf.py build
   4.idf.py flash
   5.idf.py monitor */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t serial_task_handle;
TimerHandle_t serial_timer_handle;

void serial_timer_callback(TimerHandle_t xTimer)
{
    printf("Timer fired\n");
}

void serial_task(void *data)
{
    printf("Starting The Serial Task\n");
    printf("creating the timer\n");
    serial_timer_handle = xTimerCreate("one_shot_timer", 5000 / portTICK_PERIOD_MS, pdTRUE, 0, serial_timer_callback);
    printf("starting the timer\n");
    xTimerStart(serial_timer_handle, 0);
    vTaskDelete(serial_task_handle);
    printf("Serial task dead\n");
}

int app_main()
{
    BaseType_t res;
    UBaseType_t mt_prio;
    printf("DESD RTOS pROJECT\n");
    mt_prio = uxTaskPriorityGet(NULL);
    printf("MT: Task created successfully: prio : %d\n", mt_prio);
    res = xTaskCreate(serial_task, "SERIALTASK", 2048, NULL,5, &serial_task_handle);
    return 0;
}
