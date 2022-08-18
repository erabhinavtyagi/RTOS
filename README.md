# Real Time Operating System

- Here in this course we are using FreeRTOS and ESP32.

- Download ESP-IDF from following link and follow the procedure.

  [For Linux/MacOS Users](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html)

  [For Windows](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/windows-setup.html)


- What is Port of the RTOS ?

  - FreeRTOS runs on many many architectures, and can be built with many different compilers. 
  - A ‘port’ is considered to be a compiler/architecture combination.  
  - For example, if you are targeting a Cortex-M0 MCU using the IAR compiler, then you are using the Cortex-M0 IAR port.


- Porting of RTOS/ EOS

  - Processor Independent
  - Processor Dependent
    - Timer => Clock Tick
    - Context Saving and Context Restoring


- Assignment

  - Scheduler Algo => High priority Task
  - Function in FreeRTOS => Scheduling
  - Have separate files for the Task1 and Task2
  - Task1 => Resume => Task2
  - Task1 => Resume => Task2 and Task3
  - Task1 => Resume => Task2 => Resume => Task3 => Resume => Task1
  - Find out 3 real world examples of usage of Signals/ Event Notifications
  - Extend MQ demo to send additional field in the message that distinguishes the sender of the message


- C Runtime Environment (CRT)
  - It initializes Interrupts.
  - It initializes Stack Pointer.
  - It initializes global BSS Segment to Zero to uninitialized data.
    NOTE: It can give Zero value or garbage value depending upon compiler. In GCC, if we write 
    "int b" then it will intialize "b = 0" which can be seen through normal printf function.
  - It initializes Data segment.
  - It initializes main() function which is the entry function for each program. 
    -  For example in ESP-IDF the entry function is "app_main()" and in c programs it is main(). 

- Task => Stack =>

  - CreateTask
    - Size of Stack
    - Priority

- Stack Guard

- Priorities affect the task execution

  - Same priority => Round Robbin
  - Highest Priority task always executes

- Periodic Task

  - Delay by Periodicity =>

- Task Categories

  - Periodic
  - Aperiodic
  - Sporadic

- Specifications (Temporal)

  - Periodicity
  - Deadline
  - Execution/ Computing Time

- RMS (Rate Monotonic Scheduling)

  - Shorter Period -> Higher Rate -> Higher Priority
  - Summation Ci/Pi <= m(2 ^ 1/m - 1)

- Interrupt Latency
- Interrupt Response time
- Interrupt Recovery time

- ISR Entry Function
- ISR Exit Function

- Binary Signalling Semaphore
- Mutex
- Message Queues