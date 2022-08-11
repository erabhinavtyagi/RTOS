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

TaskHandle_t serial_task_handle;

void serial_task(void *data)
{
    printf("Serial task:Started\n");
}

int app_main()
{
    BaseType_t res;
    printf("DESD RTOS pROJECT\n");
    res = xTaskCreate(serial_task, "SERIALTASK", 2048, NULL,5, &serial_task_handle);
    if(res == pdPASS)
    {
        printf("Task created successfully\n");
    }    
return 0;
}
