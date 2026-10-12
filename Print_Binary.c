/**
* @file print_binary.c
*
* @brief Main source code for Print_Binary program. Used the following 
* reasource for helping write the fucntion " https://www.youtube.com/shorts/OYP0pa50a0Q"
*
* This file contains the main entry point and the implementation
* of the Print_Binary function that takes in a uint8_t value and
* prints the value in binary format.
*
* @author Daniel Silva Rios 
*/



#include <stdio.h>
#include <stdint.h>

void Print_Binary(uint8_t value_to_convert);



int main()
{
uint8_t value_to_convert = 170;
printf("Decimal: %d\n", value_to_convert);
Print_Binary(value_to_convert);
return 0;
}




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