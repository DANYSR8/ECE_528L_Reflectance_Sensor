# ECE 528/L - Robotics and Embedded Systems with Lab
**CSU Northridge**

**Department of Electrical and Computer Engineering**

## Reflectance Sensor Lab

### Overview:
This lab introduces the 8-Channel QTRX Reflectance Sensor Array, which is interfaced using GPIO. The module measures surface reflectance using IR LEDs and phototransistors. The goal of this lab is to develop the foundational driver functions for this module so that they can be used to implement a line-following application that follows a black line on a white background.

### Componets Used:
The Reflectance Sensor lab interfaces with the following:

* User LEDs of the TI MSP432 LaunchPad
* 8-Channel QTRX Sensor Array - [Product Link](https://www.pololu.com/product/3672)


### Analysis and Results: 




#### Pre-Lab

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

See file `Print_Binary.c` in the folder for full code function is just shown below. For developmening this code used the following reasources: 

1. https://www.youtube.com/shorts/OYP0pa50a0Q

```c
void Print_Binary(uint8_t value_to_convert)
{
    // Initial setup 

int remainder[8]; 
uint8_t quotient = value_to_convert; 


for (int i = 0; i < 8; i++)
{
    remainder[i] = quotient % 2;
    quotient = quotient / 2;
}


printf("Binary: ");
for (int j = 7; j >= 0; j--) {

    if (j % 4 == 0 && j != 0)
    {
        printf ("%d_", remainder[j]);
    }

    else{
        printf("%d", remainder[j]);
    }
    

}
printf("\n");

}
```






#### Reflecatance Sensor Initilzation 

The lab calls for the following pins to be initialzied P5.3 and P9.2 as GPIO outputs, and P7.0 through P7.7 as GPIO inputs. In order to set up the 8-Channel QTRX Sensor Array module. This was done with the following code below. 

***Reflectance_Sensor_Init Function***

```c 
void Reflectance_Sensor_Init()
{
    // Configure P5.3 as an output GPIO pin by
    // clearing Bit 3 of the SEL0 and SEL1 registers for P5
    // and setting Bit 3 of the DIR register for P5

    P5->SEL0 &= ~0x08; //DSR
    P5->SEL1 &= ~0x08; //DSR
    P5->DIR |= 0x08; //DSR

    // Turn off the even-numbered IR LEDs by
    // clearing Bit 3 of the OUT register for P5


    P5->OUT &= ~0x08; //DSR


    // Configure P9.2 as an output GPIO pin by
    // clearing Bit 2 of the SEL0 and SEL1 registers for P9
    // and setting Bit 2 of the DIR register for P9

    P9->SEL0 &= ~0x04; //DSR
    P9->SEL1 &= ~0x04; //DSR
    P9->DIR |= 0x04; //DSR


    // Turn off the odd-numbered IR LEDs by
    // clearing Bit 2 of the OUT register for P9

    P9->OUT &= ~0x04; //DSR


    // Configure P7.0 - P7.7 as input GPIO pins by
    // clearing Bits 0 to 7 of the SEL0, SEL1, and DIR registers for P7


    P7->SEL0 &= ~0xFF; //DSR
    P7->SEL1 &= ~0xFF; //DSR
    P7->DIR &= ~0xFF; //DSR

}
```





#### Reflecatance Sensor Read out 
Addditonally we need to have a way to read the 8-Channel QTRX Sensor Array module output, therefor we need a `Reflectance_Sensor_Read` function. This functuon follows the following sequnece. 

 1. Turns on the 8 IR LEDs.
 2. Pulses the 8 sensors high for 10 microseconds.
 3. Makes the sensor pins input.
 4. Waits for a specified time in microseconds.
 5. Reads the sensors.
 6. Turns off the 8 IR LEDs.

 This is implments using the following code block. 

 ```c 
uint8_t Reflectance_Sensor_Read(uint32_t time)
{
    // Turn on the even-numbered IR LEDs by
    // setting Bit 3 of the OUT register for P5

    P5->OUT |= 0x08; //DSR

    // Turn on the odd-numbered IR LEDs by
    // setting Bit 2 of the OUT register for P9

    P9->OUT |= 0x04; //DSR

    // Configure P7.0 - P7.7 as output GPIO pins by
    // setting Bits 0 to 7 of the DIR register for P7

    P7->SEL0 &= ~0xFF; //DSR
    P7->SEL1 &= ~0xFF; //DSR
    P7->DIR |= 0xFF; //DSR

    // Set the P7.0 - P7.7 pins to high by
    // setting Bits 0 to 7 of the OUT register for P7

    P7->OUT |= 0xFF; //DSR

    // Wait for 10 us using the Clock_Delay1us function

    Clock_Delay1us(10); //DSR

    // After waiting 10 us, configure P7.0 - P7.7 as input GPIO pins
    // by clearing Bits 0 to 7 of the DIR register for P7

    P7->DIR &= ~0xFF; //DSR

    // Call the Clock_Delay1us function and pass in the "time" input parameter

    Clock_Delay1us(time);


    // Declare a local uint8_t variable called "reflectance_value"
    // and assign it the value of P7->IN, which is the 8-bit data
    // read from P7. This represents the reflectance sensor value
    // Note: "1" indicates black while "0" indicates white
    uint8_t reflectance_value = P7->IN;

    // Turn off the even-numbered IR LEDs by
    // clearing Bit 3 of the OUT register for P5

    P5->OUT &= ~0x08; //DSR

    // Turn off the odd-numbered IR LEDs by
    // clearing Bit 2 of the OUT register for P9

    P9->OUT &= ~0x04; //DSR

    // Return the local variable, "reflectance_value"
    return reflectance_value;
}

 ```







#### Detect_Line_Position

With the initalization and readout of the Reflecatance Sensor done, the lab tasked us to develop a `Detect_Line_Position` function that will "indicate which line maze possibility has been detected by displaying different RGB LED colors". This function was implemented using switch cases, be located in the `main.c` file and should follow the table below. This function can be seen in the code block diaplyes just below the table 

![Detect_Line_Position](./Images/DetectLinePosition_Table.png)

***Detect_Line_Position Function***

```c 
void Detect_Line_Position(uint8_t reflectance_sensor_data){
    
    switch(reflectance_sensor_data){
        
        case 0x18:
        printf("Center");
        LED1_Output(RED_LED_OFF);
        LED2_Output(RGB_LED_GREEN);
        break;
        
        case 0x1C:
        printf("Slightly Left from Center");
        LED1_Output(RED_LED_OFF);
        LED2_Output(RGB_LED_YELLOW);
        break;
        
        case 0x38:
        printf("Slightly Right from Center");
        LED1_Output(RED_LED_OFF);
        LED2_Output(RGB_LED_PINK);
        break;
                
                
        case 0x01:
        printf("Far Left from Center");
        LED1_Output(RED_LED_OFF);
        LED2_Output(RGB_LED_WHITE);
        break;

        case 0x80:
        printf("Far Right from Center");
        LED1_Output(RED_LED_OFF);
        LED2_Output(RGB_LED_SKY_BLUE);
        break;
        
                
        case 0xF8:
        printf("Left Turn"); 
        LED1_Output(RED_LED_ON);
        LED2_Output(RGB_LED_WHITE);
        break;
        
        
        case 0x1F:
        printf("Right Turn");
        LED1_Output(RED_LED_ON);
        LED2_Output(RGB_LED_SKY_BLUE);
        break;
                
                
        case 0xFF:
        printf("T-Intersection");
        LED1_Output(RED_LED_ON);
        LED2_Output(RGB_LED_BLUE);
        break;
                
        
        case 0x00:
        printf("Dead End");
        LED1_Output(RED_LED_ON);
        LED2_Output(RGB_LED_RED);
        break;

        
        default:
        printf("Unknown sensor pattern: 0x%02X\n",reflectance_sensor_data);
        LED1_Output(RED_LED_OFF);
        LED2_Output(RGB_LED_OFF);
        break;
    
    }
    
}
```

### Known Issues or Limitations: 

During testing, the `Print_Binary` function did not always print the full 8-bit binary representation. The original implementation used a `while (quotient > 0)` loop, which stopped extracting bits once the remaining value reached zero. As a result, leading zeros were dropped (for example, 5 printed as 101 instead of 0000_0101), and an input of 0 printed nothing. This was resolved by replacing the while loop with a fixed for loop that always iterates eight times, matching the width of a `uint8_t`.

### Author Contributions:
Jamal B. helped with consulting and answering questions that came up during lab time. Code generated individually.






### Refrences 

1. https://www.youtube.com/shorts/OYP0pa50a0Q

1. MSP432P401R SimpleLink Microcontroller LaunchPad Development Kit User's Guide - [Link](https://docs.rs-online.com/3934/A700000006811369.pdf)

1. MSP432P401R Datasheet - [Link](https://www.ti.com/lit/ds/slas826e/slas826e.pdf)

1. MSP432P4xx SimpleLink Microcontrollers Technical Reference Manual - [Link](https://web.archive.org/web/20200402132841/http:/www.ti.com/lit/ug/slau356i/slau356i.pdf)
