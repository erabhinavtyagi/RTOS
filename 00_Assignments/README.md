# RTOS Assignment 
NOTE: All Solutions are given by taking FREERTOS into account. Solutions may vary as per other Real-Time Operating System.

## 1. Find what is the task priority numbering for the RTOS you are using. eg. Higher the number higher the priority or vice-versa. Find the range of priority that can be assigned to a task for your RTOS.

Each task is assigned a priority from 0 to ( configMAX_PRIORITIES - 1 ), where configMAX_PRIORITIES is defined within FreeRTOSConfig.h.
If the port in use implements a port optimised task selection mechanism that uses a 'count leading zeros' type instruction (for task selection in a single instruction) and configUSE_PORT_OPTIMISED_TASK_SELECTION is set to 1 in FreeRTOSConfig.h, then configMAX_PRIORITIES cannot be higher than 32. In all other cases configMAX_PRIORITIES can take any value within reason - but for reasons of RAM usage efficiency should be kept to the minimum value actually necessary.
Low priority numbers denote low priority tasks. The idle task has priority zero (tskIDLE_PRIORITY).
The FreeRTOS scheduler ensures that tasks in the Ready or Running state will always be given processor (CPU) time in preference to tasks of a lower priority that are also in the ready state. In other words, the task placed into the Running state is always the highest priority task that is able to run.
Any number of tasks can share the same priority. If configUSE_TIME_SLICING is not defined, or if configUSE_TIME_SLICING is set to 1, then Ready state tasks of equal priority will share the available processing time using a time sliced round robin scheduling scheme.


## 2. What is the mechanism used to make a task periodic for the RTOS you are using? Write a program to make a task periodic with periodicity of 500ms.

In FreeRTOS, there are two APIs to create delay or make the task periodic.
 
 1. void vTaskDelay( const TickType_t xTicksToDelay );
 
For eg.
``` 
 vTaskDelay( pdMS_TO_TICKS( ms ) ); // less complex in computation as per several blogs.
 
 vTaskDelay(ms / portTICK_PERIOD_MS);
```
 2. void vTaskDelayUntil( TickType_t *pxPreviousWakeTime, const TickType_t xTimeIncrement );
 
 "vTaskDelay" specifies a time at which the task wishes to unblock relative to the time
 at which vTaskDelay() is called.
 Whereas vTaskDelayUntil() specifies an absolute (exact) time at which the task wishes to unblock.
 Hence it is safe to use vTaskDelayUntil().
 It should be noted that vTaskDelayUntil() will return immediately (without blocking) 
 if it is used to specify a wake time that is already in the past. Therefore a task using
 vTaskDelayUntil() to execute periodically will have to re-calculate its required wake time
 if the periodic execution is halted for any reason (for example, the task is temporarily placed into the Suspended state) causing the task to miss one or more periodic executions. 


## 3. Find the APIs in your RTOS that provides timestamp and use it to print the periodic task. Observe the jitter in the timestamp vs the periodicity. Enhance the code to 10 periodic tasks with different periodicity. Futher observe the jitter in each of the task.



## 4. Create two task with priority 10 and 20. Each task prints its own custom message.

Refer Program code.

## 5. Swap the priority and observe the changes in the output. What is your conclusion on the sequence of printing the messages.

Refer Program code.
CONCLUSION : Higher Priority Task started first in each case.

## 6. What are the maximum number of tasks that can be created on the RTOS you are using? Is it limited by the RTOS design or underlying hardware resources or both.

The task control block (TCB) and the task's stack space are both allocated from the FreeRTOS heap as defined by configTOTAL_HEAP_SIZE (and the specific heapX.c file included in the build). There is nothing in FreeRTOS that limits the number of created tasks except the available FreeRTOS heap space.

## 7. What is the scheduling algorithm used by your RTOS?

FreeRTOS kernel supports two types of scheduling policy:

1.  **Time Slicing Scheduling Policy** : This is also known as a round-robin algorithm. In this algorithm, all equal priority tasks get CPU in equal portions of CPU time.
       
2.  **Fixed Priority Preemptive Scheduling** : This scheduling algorithm selects tasks according to their priority. In other words, a high priority task always gets the CPU before a low priority task. A low priority task gets to execute only when there is no high priority task in the ready state.

But in FreeRTOS, we usually use scheduling policy by mixing both the above-mentioned algorithms and it is known as Prioritized Preemptive Scheduling with Time Slicing.


## 8. List the customization options for creating a task for the RTOS you are using. eg. priority etc.

FreeRTOS is customised using a configuration file called FreeRTOSConfig.h.

1. Idle Task
2. Hooks (Callbacks)
3. Symmetric Multiprocessing (SMP) Support
4. Memory Protection Support
5. Thread Local Storage Pointers
6. Blocking on Multiple Objects
7. Deferred Interrupt Handling
8. Low Power Support etc

check FreeRTOSConfig.h for more options.


## 9. Find the fields that are maintained in the Task Control Block / Process Control Block of the RTOS you are using.

FreeRTOS uses a newly allocated TCB object to store the name, priority, and other details for a task, then allocates the amount of stack the user requests (assuming there's enough memory available) and remembers the start of the stack memory in TCB's pxStack member. 


## 10. Draw a process or task state diagram for the RTOS you are using.

A task can exist in one of the following states:

### 1. Running
When a task is actually executing it is said to be in the Running state. It is currently utilising the processor. If the processor on which the RTOS is running only has a single core then there can only be one task in the Running state at any given time.

### 2. Ready
Ready tasks are those that are able to execute (they are not in the Blocked or Suspended state) but are not currently executing because a different task of equal or higher priority is already in the Running state.

### 3. Blocked
A task is said to be in the Blocked state if it is currently waiting for either a temporal or external event. For example, if a task calls vTaskDelay() it will block (be placed into the Blocked state) until the delay period has expired - a temporal event. Tasks can also block to wait for queue, semaphore, event group, notification or semaphore event. Tasks in the Blocked state normally have a 'timeout' period, after which the task will be timeout, and be unblocked, even if the event the task was waiting for has not occurred.

Tasks in the Blocked state do not use any processing time and cannot be selected to enter the Running state.

### 4. Suspended
Like tasks that are in the Blocked state, tasks in the Suspended state cannot be selected to enter the Running state, but tasks in the Suspended state do not have a time out. Instead, tasks only enter or exit the Suspended state when explicitly commanded to do so through the vTaskSuspend() and xTaskResume() API calls respectively.

![Valid task state transitions](https://www.freertos.org/fr-content-src/uploads/2018/07/tskstate.gif)

## 11. What is the API for deleting a task? Write a program demonstrate this capability.

```
void vTaskDelete( TaskHandle_t pxTask ); 
```

It will delete an instance of a task that was previously created using a call to 
xTaskCreate() or xTaskCreateStatic().

When a task is deleted, it is the responsibility of the idle task to free the memory 
that had been used to hold the deleted task’s stack and data structures (task control block).
Therefore, if an application makes use of the vTaskDelete() API function, it is vital that
the application also ensures the idle task is not starved of processing time (the idle task must be allocated time in the Running state).


## 12. What are the APIs provided by your RTOS for enabling and disabling the interrupts? Write a program to demonstrate this capability?

**taskDISABLE_INTERRUPTS()**

include task. h

If the port in use supports the configMAX_SYSCALL_INTERRUPT_PRIORITY (or configMAX_API_CALL_INTERRUPT_PRIORITY) constant, then taskDISABLE_INTERRUPTS will either disable all interrupts, or mask (disable) interrupts up to the configMAX_SYSCALL_INTERRUPT_PRIORITY setting. Check the implementation of taskDISABLE_INTERRUPTS for the port in use.

If the port in use does not support the configMAX_SYSCALL_INTERRUPT_PRIORITY constant then taskDISABLE_INTERRUPTS() will globally disable all maskable interrupts.

Normally this macro would not be called directly and **taskENTER_CRITICAL()** and **taskEXIT_CRITICAL()** should be used in its place.

**taskENABLE_INTERRUPTS()**

include task. h

Macro to enable microcontroller interrupts.

Normally this macro would not be called directly and **taskENTER_CRITICAL()** and **taskEXIT_CRITICAL()** should be used in its place.

```
void taskENTER_CRITICAL( void );
void taskEXIT_CRITICAL( void );
```
Critical sections are entered by calling taskENTER_CRITICAL(), and subsequently exited by calling taskEXIT_CRITICAL().

The taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros provide a basic critical section implementation that works by simply disabling interrupts, either globally, or up to a specific interrupt priority level. See the vTaskSuspendAll() RTOS API function for information on creating a critical section without disabling interrupts.

If the FreeRTOS port being used does not make use of the configMAX_SYSCALL_INTERRUPT_PRIORITY kernel configuration constant (also called configMAX_API_CALL_INTERRUPT_PRIORITY), then calling taskENTER_CRITICAL() will leave interrupts globally disabled. If the FreeRTOS port being used does make use of the configMAX_SYSCALL_INTERRUPT_PRIORITY kernel configuration constant, then calling taskENTER_CRITICAL() will leave interrupts at and below the interrupt priority set by configMAX_SYSCALL_INTERRUPT_PRIORITY disabled, and all higher priority interrupt enabled.

Preemptive context switches only occur inside an interrupt, so will not occur when interrupts are disabled. Therefore, the task that called taskENTER_CRITICAL() is guaranteed to remain in the Running state until the critical section is exited, unless the task explicitly attempts to block or yield (which it should not do from inside a critical section).

Calls to taskENTER_CRITICAL() and taskEXIT_CRITICAL() are designed to nest. Therefore, a critical section will only be exited when one call to taskEXIT_CRITICAL() has been executed for every preceding call to taskENTER_CRITICAL().

Critical sections must be kept very short, otherwise they will adversely affect interrupt response times. Every call to taskENTER_CRITICAL() must be closely paired with a call to taskEXIT_CRITICAL().

FreeRTOS API functions must not be called from within a critical section.

taskENTER_CRITICAL() and taskEXIT_CRITICAL() must not be called from an interrupt service routine (ISR) - see taskENTER_CRITICAL_FROM_ISR() and taskEXIT_CRITICAL_FROM_ISR() for interrupt safe equivalents.


## 13. Does your RTOS provide APIs to collect task statistics. If yes, list the statistics parameters that are collected and write a program to display the runtime task statistics?

FreeRTOS provide following API for Runtime Task Statistics.
```
void vTaskGetRunTimeStats( char *pcWriteBuffer );
```
**pcWriteBuffer** 	A buffer into which the execution times will be written, in ASCII form. This buffer is assumed to be large enough to contain the generated report. Approximately 40 bytes per task should be sufficient.

FreeRTOS can be configured to collect task run time statistics.
Task run time statistics provide information on the amount of processing time each task has received. Figures are provided as both an absolute time and a percentage of the total application run time. The vTaskGetRunTimeStats() API function formats the collected run time statistics into a human readable table. Columns are generated for the task name, the absolute time allocated to that task, and the percentage of the total application run time allocated to that task.

**Notes**

 - vTaskGetRunTimeStats() is a utility function that is provided for convenience only. It is not
considered part of the kernel. vTaskGetRunTimeStats() obtains its raw data using the xTaskGetSystemState() API function.

 - configGENERATE_RUN_TIME_STATS and configUSE_STATS_FORMATTING_FUNCTIONS must both be set to 1 in FreeRTOSConfig.h for vTaskGetRunTimeStats() to be available.
 
 - Setting configGENERATE_RUN_TIME_STATS will also require the application to define the
following macros:

1. portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
The run time statistics time base needs to have a higher resolution than the tick interrupt - otherwise the statistics may be too inaccurate to be truly useful. It is recommended to make the time base between 10 and 100 times faster than the tick interrupt. The faster the time base the more accurate the statistics will be - but also the sooner the timer value will overflow.

If configGENERATE_RUN_TIME_STATS is defined as 1 then the RTOS kernel will automatically call portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() as it is started (it is called from within the vTaskStartScheduler() API function). It is intended that the application designer uses the macro to configure a suitable time base. Some examples are provided below.

2. portGET_RUN_TIME_COUNTER_VALUE()
This macro should just return the current 'time', as configured by portCONFIGURE_TIMER_FOR_RUN_TIME_STATS().


## 14. Find the tick frequency configuration for your RTOS.

In my PC, the value of Tick Frequency in the file **FreeRTOSConfig.h** is given as **1000**. It may vary for other systems.

## 15. Create a task to suspend itself after 1200 ms and resume it from another task.

Refer Program code.

## 16. Write a RTOS application to demonstrate the use of changing priority.


## 17. If your RTOS supports idle task hooking, write a program to demonstrate it.


## 18. Write a RTOS application to demonstrate the use of task to task communication using Queue management APIs. Also demonstrate blocking on a queue.


## 19. Write a RTOS application to demonstrate the effects of task priorities when sending to and receiving from a queue.


## 20. Write a RTOS application to demonstrate deferred interrupt processing using binary semaphores.


## 21. Write a RTOS application to demonstrate counting semaphores to synchronize a task.

Refer Program code.

include "semphr. h"

```
SemaphoreHandle_t xSemaphoreCreateCounting( UBaseType_t uxMaxCount, UBaseType_t uxInitialCount);
```
Creates a counting semaphore and returns a handle by which the newly created semaphore can be referenced. configSUPPORT_DYNAMIC_ALLOCATION must be set to 1 in FreeRTOSConfig.h, or left undefined (in which case it will default to 1), for this RTOS API function to be available.

Each counting semaphore require a small amount of RAM that is used to hold the semaphore's state. If a counting semaphore is created using xSemaphoreCreateCounting() then the required RAM is automatically allocated from the FreeRTOS heap. If a counting semaphore is created using xSemaphoreCreateCountingStatic() then the RAM is provided by the application writer, which requires an additional parameter, but allows the RAM to be statically allocated at compile time. See the Static Vs Dynamic allocation page for more information.

Counting semaphores are typically used for two things:

1. Counting events.
In this usage scenario an event handler will 'give' a semaphore each time an event occurs (incrementing the semaphore count value), and a handler task will 'take' a semaphore each time it processes an event (decrementing the semaphore count value). The count value is therefore the difference between the number of events that have occurred and the number that have been processed. In this case it is desirable for the initial count value to be zero.

Note the same functionality can often be achieved in a more efficient way using a direct to task notification.

2. Resource management.
In this usage scenario the count value indicates the number of resources available. To obtain control of a resource a task must first obtain a semaphore - decrementing the semaphore count value. When the count value reaches zero there are no free resources. When a task finishes with the resource it 'gives' the semaphore back - incrementing the semaphore count value. In this case it is desirable for the initial count value to be equal to the maximum count value, indicating that all resources are free.

Parameters:
**uxMaxCount**  	The maximum count value that can be reached. When the semaphore reaches this value it can no longer be 'given'.
**uxInitialCount**  	The count value assigned to the semaphore when it is created.
Returns:
If the semaphore is created successfully then a handle to the semaphore is returned. If the semaphore cannot be created because the RAM required to hold the semaphore cannot be allocated then NULL is returned.

## 22. Write a RTOS application to demonstrate the usage of queues within an interrupt service routine.


## 23. Write a RTOS application to manage resources using mutual exclusion.


## 24. Write a RTOS application to demonstrate a priority inversion problem. If your RTOS supports priority inheritance or priority ceiling, use it to solve the priority inversion problem.


## 25. Write a RTOS application to create a software timer that invokes a callback function every 5 seconds.