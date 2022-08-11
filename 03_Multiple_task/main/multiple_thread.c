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
        


        TaskHandle_t serial_task_handle, ether_task_handle;
        int count = 0;

        void serial_task(void *data)
        {
            UBaseType_t prio;
            while(1)
            {
                
                count += 1;
                if(count>5)
                {
                    vTaskResume(ether_task_handle);
                    count = 0;
                }
                prio = uxTaskPriorityGet(serial_task_handle);
                printf("Serial task:Started:%d\n", prio);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            vTaskDelete(serial_task_handle);
        }

        void ether_task(void *data)
        {
            UBaseType_t prio;
            while(1)
            {
            vTaskSuspend(NULL);
            prio = uxTaskPriorityGet(ether_task_handle);
            printf("Serial task:Started %d\n", prio);
            vTaskDelay(1000 / portTICK_PERIOD_MS);   
            }
            vTaskDelete(serial_task_handle);
        }

        int app_main()
        {
            BaseType_t res;
            UBaseType_t mt_prio;
            
            
            printf("DESD RTOS pROJECT\n");
            mt_prio = uxTaskPriorityGet(NULL);
            printf("Task created successfully:Prio:%d\n", mt_prio);
            res = xTaskCreate(serial_task, "SERIALTASK", 2048, NULL,5, &serial_task_handle);
            res = xTaskCreate(ether_task, "ETHERTASK", 2048, NULL,8, &ether_task_handle);
            mt_prio = uxTaskPriorityGet(serial_task_handle);
            return 0;
        }
