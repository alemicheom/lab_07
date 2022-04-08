/*
 * File:   delay_lab07.c
 * Author: aleja
 *
 * Created on April 4, 2022, 9:53 PM
 */


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO  oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include <stdint.h>
#include "setup_lab07.h"
        
#define _XTAL_FREQ 4000000
#define _tmr0_value 256


// variables 
uint8_t bandera =  0b001;

uint8_t contador;       //variable que dec e inc con el contador de port C
uint8_t remainder;      // 
uint8_t unidades;       //variable de unidades 
uint8_t decenas;        //variable de decenas 
uint8_t centenas;       //variable de centenas

uint8_t display_1;
uint8_t display_2;
uint8_t display_3;


//interrupcion 


void __interrupt() isr (void)
{
    if (RBIF)
    {
        if (PORTBbits.RB0 == 0)
        {
            PORTA++;
            contador++;
        }
        
        if (PORTBbits.RB1 == 0)
        {
            PORTA--;
            contador--;
        }
        INTCONbits.RBIF = 0;     
            
    }
    
    if (T0IF)
    {
        // incrementa port C en cada interrupción del TMR0
        //PORTC++;
        //INTCONbits.T0IF = 0;
        //TMR0 = _tmr0_value;     
        
       // rutina para multiplexado 
        
                if (bandera ==  0)
                {
                    PORTD = display_3;
                    PORTE = 0b001;
                    bandera = 1;
                    
                }
                
                else if (bandera == 1)
                {
                    PORTD = display_2;
                    PORTE = 0b010; 
                    bandera = 2;
                 
                }
                
                else if (bandera ==  2)
                {
                    PORTD = display_1;
                    PORTE = 0b100 ;  
                    bandera = 0; 
                }
           
             INTCONbits.T0IF = 0; 
     }
    return ;       
}
   

  

void main(void) {
    setup();
    int tabla[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
    
    while(1){
        centenas = contador/100 ;
        remainder = contador % 100;
        decenas = remainder /10;
        unidades = remainder % 10;
        
        display_1 = tabla[unidades];
        display_2 = tabla[decenas];
        display_3 = tabla[centenas];
             
       
    }
    return ;
}
