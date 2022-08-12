/*
 * Write a Scheduler Algorithm in C which schedules the High Priority Tasks having following functionalities.
 *  - It Should be Memory Efficient. (Use Bit Manipulation)
 *  - It Should take Constant Time.
 */

// Priority Bit Table --> Ready Queue --> Running

#include <stdio.h>

// struct {
//    unsigned int P0 : 1;
//    unsigned int P1 : 1;
//    unsigned int P2 : 1;
//    unsigned int P3 : 1;
//    unsigned int P4 : 1;
//    unsigned int P5 : 1;
//    unsigned int P6 : 1;
//    unsigned int P7 : 1;
//    unsigned int P8 : 1;
//    unsigned int P9 : 1;
//    unsigned int P10 : 1;
//    unsigned int P11 : 1;
//    unsigned int P12 : 1;
//    unsigned int P13 : 1;
//    unsigned int P14 : 1;
//    unsigned int P15 : 1;
// } readyQueue;

// NOTE: if using "uint8_t A[]" instead of "int A[]" then divide by 8, not 32
void setBit(int a[], int k)
{
    int i = k/32;           //gives the corresponding index in the array A
    int pos = k%32;         //gives the corresponding bit position in A[i]

    unsigned int flag = 1;  // flag = 0000.....00001

    flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)
    a[i] = a[i] | flag;     // Set the bit at the k-th position in A[i]

    printf("flag: %d \t a[%d] = %d\n", flag, i, a[i]);    
    // a[k/32] |= 1<<(k%32); // Set the bit at the k-th position in A[i]
}

void clearBit(int a[], int k)
{
    a[k/32] &= ~(1<<(k%32));
}

int testBit(int a[], int k)
{
    return ( (a[k/32] & (1<<(k%32)) != 0));
}

int main()
{
    int num;
    int prio[10];
    //int prio[3][4];
    //printf("Size of readyQueue is %ld\n", sizeof(readyQueue));
    printf("Enter the Bit number to Set Priority: ");
    scanf("%d", &num);
    
    setBit(prio,num);
    // clearBit();
    // testBit();
    return 0;
}