/*
 * Problem 12. What are the APIs provided by your RTOS for enabling and disabling the interrupts?
 * Write a program to demonstrate this capability?
 * 
 * @ author	: Abhinav Tyagi
 * @ email 	: erabhinavtyagi@gmail.com
 * @ date	: Aug 15, 2022	
 */

/************************** SOLUTION *******************************
 * Following are the two APIs for enabling and disabling the interrupts respectively.
 * 1. void taskENABLE_INTERRUPTS( void );
 * 2. void taskDISABLE_INTERRUPTS( void );
 * 
 * if nesting is required then use "taskENTER_CRITICAL()" and "taskEXIT_CRITICAL()" in place of
 * taskDISABLE_INTERRUPTS() and taskENABLE_INTERRUPTS() respectively.
 *  
 */
