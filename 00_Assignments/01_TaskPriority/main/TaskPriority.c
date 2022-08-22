/*
 * Problem 1. Find what is the task priority numbering for the RTOS you are using. 
 * eg. Higher the number higher the priority or vice-versa. Find the range of priority 
 * that can be assigned to a task for your RTOS.
`* 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2022	
 */

/*********** SOLUTION ****************
* In FreeRTOS: Higher the Number, Higher is the Priority. 
* Each task is assigned a priority from 0 to ( configMAX_PRIORITIES - 1 ),
* where configMAX_PRIORITIES is defined within FreeRTOSConfig.h.
* i.e if configMAX_PRIORITIES is 25 then Max Range for Priorities will be 0 to (25-1) i.e 0 to 24.
* But it cannot be higher than 32. 
*/

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
    printf("Ether task:Started %d\n", prio);
    vTaskDelay(1000 / portTICK_PERIOD_MS);   
    }
    vTaskDelete(ether_task_handle);
}

int app_main()
{
    BaseType_t res;
    UBaseType_t mt_prio;
    
    printf("DESD RTOS PROJECT\n");
    mt_prio = uxTaskPriorityGet(NULL);
    printf("Task created successfully:Prio:%d\n", mt_prio);
    res = xTaskCreate(serial_task, "SERIALTASK", 2048, NULL,5, &serial_task_handle);
    res = xTaskCreate(ether_task, "ETHERTASK", 2048, NULL,8, &ether_task_handle);
    mt_prio = uxTaskPriorityGet(serial_task_handle);
    return 0;
}
