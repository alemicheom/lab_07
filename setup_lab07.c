/*
 * File:   setup_lab07.c
 * Author: aleja
 *
 * Created on April 4, 2022, 9:53 PM
 */


#include <xc.h>

void setup(void){
    ANSEL = 0;
    ANSELH = 0;                 // I/O digitales
    
    OSCCONbits.IRCF = 0b0110; // 4MHz
    OSCCONbits.SCS = 1;       // Oscilador interno
    
    //OSCCONbits.IRCF = 0b0101;   // 2MHz
    //OSCCONbits.SCS = 1;         // Oscilador interno
    
    TRISA = 0;                  // PORTA salida
    PORTA = 0; 
   
    TRISB = 0b00000011;       // PORTB inputs     
    PORTB = 0; 
    
    // contador tmr0
    TRISC = 0;                  // PORTC salida
    PORTC = 0; 
    
    // contador displays
    TRISD = 0;                  // PORTD salida
    PORTD = 0; 
    
     // banderas displays
    TRISE = 0;                  // PORTD salida
    PORTE = 0; 
    
    
    // TMR0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA  = 0;
    OPTION_REGbits.PS   = 0b0111;    
    
    
    // PULL UP
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    
    // interrupciones PORTB 
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    
    //interrupciones 
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.RBIF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;
}

