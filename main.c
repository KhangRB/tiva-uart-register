/**
 * main.c
 * UART function
 * write data to COM
 * serial 9600
 */
#include <stdint.h>
#include <string.h>
#include "tm4c123gh6pm.h"

void delay(uint32_t);
void UART0_Transmitter(char);
void serial_print(char[]);
void serial_println(void);

int main(void)
{
    /* system configuration */
    SYSCTL_RCGCGPIO_R |= 0x21;
    SYSCTL_RCGCUART_R |= 0x01;
    delay(100);

    /* UART0 initialization */
    UART0_CTL_R = 0;
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_CC_R = 0;             // select system clock
    UART0_LCRH_R |= 0x60;
    UART0_CTL_R |= 0x301;

    /* GPIOA configuration */
    GPIO_PORTA_DEN_R |= 0x03;
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R |= 0x11;
    delay(100);

    /* main program */
    while(1)
    {
        serial_print("Hello World!");
        serial_println();
        delay(1000000);
    }
}

void delay(uint32_t counter){
    uint32_t i = 0;
    for(i=0; i < counter; i++);
}

void UART0_Transmitter(char data)
{
    while((UART0_FR_R & 0x20) != 0);    /* wait until Tx buffer not full */
    UART0_DR_R = data;                  /* before giving it another byte */
}

void serial_print(char str[])
{
    uint32_t i;
    for(i = 0; i < strlen(str); i++)
    {
        UART0_Transmitter(str[i]);
    }
}

void serial_println()
{
    UART0_Transmitter('\n');
    UART0_Transmitter('\r');
}
