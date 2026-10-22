/**
 * @file main.c
 * @brief Main source code for the Reflectance Sensor program.
 *
 * This file contains the main entry point and function definitions for the Reflectance Sensor program.
 * It interfaces with the following:
 *  - User LEDs of the TI MSP432 LaunchPad
 *  - 8-Channel QTRX Sensor Array module
 *
 * To verify the pinout of the user buttons and LEDs, refer to the MSP432P401R SimpleLink Microcontroller LaunchPad Development Kit User's Guide
 * Link: https://docs.rs-online.com/3934/A700000006811369.pdf
 *
 * @author
 */

#include <stdint.h>
#include "msp.h"
#include "inc/Clock.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/GPIO.h"
#include "inc/Reflectance_Sensor.h"
#include "inc/Print_Binary.h"

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
        LED2_Output(RGB_LED_BLUE);
        break;

        
        default:
        printf("Unknown sensor pattern: 0x%02X\n",reflectance_sensor_data);
        LED1_Output(RED_LED_OFF);
        LED2_Output(RGB_LED_OFF);
        break;
    
    }
    
}


int main(void)
{
    // Initialize the 48 MHz Clock
    Clock_Init48MHz();

    // Initialize the built-in red LED and the RGB LEDs
    LED1_Init();
    LED2_Init();

    // Initialize the reflectance sensor
    Reflectance_Sensor_Init();

    // Initialize EUSCI_A0_UART
    EUSCI_A0_UART_Init_Printf();

    // Initialize a local variable to store the data read from the reflectance sensor
    uint8_t reflectance_sensor_data = 0;

    while(1)
    {
        reflectance_sensor_data = Reflectance_Sensor_Read(1000);
        //Print_Binary(reflectance_sensor_data);
        Detect_Line_Position(reflectance_sensor_data);
        Clock_Delay1ms(10);
    }
}
