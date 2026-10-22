/**
 * @file Print_Binary.c
 * @brief Source code for Print_Binary function implementation.
 *
 * This file contains the function implementation for the Print_Binary function,
 * which takes in a uint8_t value and prints the value in binary format.
 * It relies on the EUSCI_A0_UART driver.
 *
 * @author Aaron Nanas
 *
 */

#include "../inc/Print_Binary.h"

void Print_Binary(uint8_t value_to_convert)
{
    // Initial setup 
int i = 0; 
int remainder[8]; 
uint8_t quotient = value_to_convert; 


while (quotient > 0) {

    remainder[i] = quotient % 2 ;
    quotient = quotient / 2 ; 
    i = i + 1 ; 

}


printf("Binary: ");
for (int j = i - 1; j >= 0; j--) {

    if (j % 4 == 0 & j != 0)
    {
        printf ("%u_", remainder[j]);
    }

    else{
        printf("%u", remainder[j]);
    }
    

}
printf("\n");

}
