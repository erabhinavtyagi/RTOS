/*
 * Problem 19. Write a RTOS application to demonstrate the effects of task priorities
 * when sending to and receiving from a queue.
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 23, 2022	
 */

// SOLUTION: Data has been sent to the queue in the order of priority of the task. 
// i.e Task with higher Priority is sent first to the queue and then the lower ones in decreasing 
// order of priorities.  

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <freertos/queue.h>
//#include <freertos/semphr.h>

#define QueueLength 4       // 4 blocks
#define ItemSize 16         // 16 Kb

struct {
    char id;
    int data;
}distance,humidity,temp,pressure; 

TaskHandle_t task1Handle,task2Handle,task3Handle,task4Handle,task5Handle;
QueueHandle_t queue;

void task1(void *data)
{
    BaseType_t send;
    distance.id = 'D';
    distance.data = 100;

    while(1)
    {   
        distance.data++;
        printf("\nIN TASK 1 -----------\n");
        send = xQueueSend(queue, &distance, pdMS_TO_TICKS(1000));
        if (send == pdFALSE)
        {
            perror("Sending Failed\n");
        }
        else
        {
            printf("Distance Data Sent to Queue.\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
    vTaskDelete(NULL);
}

void task2(void *data)
{
    BaseType_t send;
    temp.id = 'T';
    temp.data = 200;

    while(1)
    {   
        temp.data++;
        printf("\nIN TASK 2 -----------\n");
        send = xQueueSend(queue, &temp, pdMS_TO_TICKS(1000));
        if (send == pdFALSE)
        {
            perror("Sending Failed\n");
        }
        else
        {
            printf("Temperature Data Sent to Queue\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
    vTaskDelete(NULL);
}

void task3(void *data)
{
    BaseType_t send;
    humidity.id = 'H';
    humidity.data = 300;

    while(1)
    {   
        humidity.data++;
        printf("\nIN TASK 3 -----------\n");
        send = xQueueSend(queue, &humidity, pdMS_TO_TICKS(1000));
        if (send == pdFALSE)
        {
            perror("Sending Failed\n");
        }
        else
        {
            printf("Humidity Data Sent to Queue.\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
    vTaskDelete(NULL);
}

void task4(void *data)
{
    BaseType_t send;

    pressure.id = 'P';
    pressure.data = 400;

    while(1)
    {   
        pressure.data++;
        printf("\nIN TASK 4 -----------\n");
        send = xQueueSend(queue, &pressure, pdMS_TO_TICKS(1000));
        if (send == pdFALSE)
        {
            perror("Sending Failed\n");
        }
        else
        {
            printf("Pressure Data Sent to Queue.\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
    vTaskDelete(NULL);
}

void task5(void *data)
{
    int buffer[2];
    BaseType_t rec =0;
    while(1)
    {   
        printf("\n------------ IN QUEUE -----------\n");
        
        rec = xQueueReceive(queue, &buffer, pdMS_TO_TICKS(1000));
        if (rec == pdTRUE)
        {
            printf("Data Received : %c\n", buffer[0]);
            printf("Data Received : %d\n", buffer[1]);
        }                       
        else
        {
            perror("Error in Receving Data From TASK 4.\n");
        }
        printf("------------------------------------\n\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    BaseType_t res;

    printf("Starting Main Task\n\n");

    // Create Queue to Transfer Data from Task 4 to Task 5
       queue = xQueueCreate(QueueLength, ItemSize);

   // Create Task 1
   res = xTaskCreate(task1, "Task1", 2048, NULL, 5, &task1Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task1.\n");
   }
   
    // Create Task 2
   res = xTaskCreate(task2, "Task2", 2048, NULL, 6, &task2Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task2.\n");
   }
   
   // Create Task 3
   res = xTaskCreate(task3, "Task3", 2048, NULL, 7, &task3Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task3.\n");
   }
   
   // Create Task 4
   res = xTaskCreate(task4, "Task4", 2048, NULL, 8, &task4Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task4.\n");
   }
   
   // Create Task 5
   res = xTaskCreate(task5, "Task5", 2048, NULL, 9, &task5Handle);
   if (res != pdPASS)
   {
    perror("Error in Creating Task5.\n");
   }
 }