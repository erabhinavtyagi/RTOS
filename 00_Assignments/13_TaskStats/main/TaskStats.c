/*
 * Problem 13. Does your RTOS provide APIs to collect task statistics. 
 * If yes, list the statistics parameters that are collected and write a program to 
 * display the runtime task statistics?
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2021	
 */


/************************** SOLUTION *******************************
 * void vTaskGetRunTimeStats( char *pcWriteBuffer );
 * 
 * By this API we can collect task run time statistics. 
 * where pcWriteBuffer is - A pointer to a character buffer into which the formatted and 
 * human readable table is written. The buffer must be large enough to hold the entire table, as
 * no boundary checking is performed.
 * 
 * vTaskGetRunTimeStats() is a utility function that is provided for convenience only. It is not
considered part of the kernel.
 * 

Configure the project

idf.py menuconfig
Select Enable FreeRTOS to collect run time stats under Component Config > FreeRTOS (this should be enabled in the example by default)

Choose the clock source for run time stats configured under Component Config > FreeRTOS. The esp_timer should be selected be default. 
This option will affect the time unit resolution in which the statistics are measured with respect to.


 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUFFER_SIZE 2048

TaskHandle_t task1_handle, task2_handle;

void vAFunction( void )
{
/* Define a buffer that is large enough to hold the generated table. In most cases
the buffer will be too large to allocate on the stack, hence in this example it is
declared static. */
static char cBuffer[ BUFFER_SIZE ];
/* Pass the buffer into vTaskGetRunTimeStats() to generate the table of data. */
vTaskGetRunTimeStats( cBuffer );
/* The generated information can be saved or viewed here. */
}


void task_1(void *data)
{
    UBaseType_t prio;
    while (1)
    {
        printf("\nThis is the First Task\n");
        prio = uxTaskPriorityGet(task1_handle);
        printf("Task1 Priority: %d\n", prio);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(task1_handle);
}

void app_main()
{
    BaseType_t res1;

    UBaseType_t mt_prio;
    mt_prio = uxTaskPriorityGet(NULL);
    
    printf("This is the Main Task\n");
    printf("Task created successfully:Prio:%d\n", mt_prio);
    printf("\n*************************************\n");
    
    res1 = xTaskCreate(task_1, "First Task", 2048, NULL, 3, &task1_handle);
   
    if (res1 !=pdPASS)
    {
        perror("Error in Creating Tasks.\n");
    }
    vAFunction();
}