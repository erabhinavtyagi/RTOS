- Porting of RTOS/ EOS

  - Proceesor Independent
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

- CRT =>

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
-
