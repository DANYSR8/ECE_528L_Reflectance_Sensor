# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Reflectance Sensor Lab
The Reflectance Sensor lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* 8-Channel QTRX Sensor Array - [Product Link](https://www.pololu.com/product/3672)


### Pre-Lab

***1. What does a reflectance sensor consist of? How many reflectance sensors are on the QTRX Reflectance Sensor Array? What is its operating voltage? Refer to Pololu’s documentation page of the QTRX Reflectance Sensor Array.***


The reflectance sensor consists of 8 inline pairs of IR LED and phototransitors and operate at 5V.  


***2. Which control pins on the QTRX Reflectance Sensor Array are responsible for enabling the reflectance sensors? What is their default value after powering on the sensor array? List the pin names and the pin numbers used to connect the two control pins. Refer to Pololu’s documentation page of the QTRX Reflectance Sensor Array.***


Pins 5.3 and 9.2 control the even and odd emitters respectivley.Additionaly the pins are label as Reflectance Sensor Ctrl Even(P5.3) and  Reflectance Sensor Ctrl Odd (9.2). Apond turning on the sensors inital value is "0" and will only change to 1 onces black and or some form if refrlectance is detected.   


***3. Write a void function named P5_0_and_P9_7_Init that takes no arguments and configures the P5.0 and P9.7 pins as output GPIO pins. Initialize the value of the P5.0 and P9.7 pins to zero.***


```c

void P5_0_and_P9_7_Init(void){

/* GPIO Setup  

SEL0 --> 0 
SEL1 --> 0 
DIR --> 1 

*/

// Clearing pins 5.0 and 9.7 
P5->SEL0 &= ~0x01; 
P9->SEL0 &= ~0x80;

// Clearing pins 5.0 and 9.7 
P5->SEL1 &= ~0x01; 
P9->SEL1 &= ~0x80;

// Initalize pins to value of zero
P5->OUT &= ~0x01; 
P9->OUT &= ~0x80;

// Setting pins 5.0 and 9.7 
P5->DIR |= 0x01; 
P9->DIR |= 0x80;



}


```



***4. Write a void function named Print_Binary that has an input parameter called value_to_convert of type uint8_t. Your function must print an unsigned 8-bit integer in binary representation with an underscore (_) separator after the 4th bit. If the input value is 0, it should print the “Binary: 0000_0000” and return. Include your name in the author section of the code documentation. If you’ve used references (e.g. GeeksforGeeks, StackOverflow, etc.), cite them below.***

See file `Print_Binary.c` in the folder. For developmening this code used the following reasources: 

1. https://www.youtube.com/shorts/OYP0pa50a0Q