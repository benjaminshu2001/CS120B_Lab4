/*	Author: bshu005
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Begin, Wait, Inc, IncDepressed, Dec, DecDepressed, Reset} State;


void Tick_Counter() {
    switch(State) {
        case Start:
            State = Begin;
            break;
        case Begin:
            State = Wait;
            break;
        case Wait:
            if((PINA & 0x01) == 0x01) {
                State = Inc;
            }
            else if((PINA & 0x02) == 0x02) {
                State = Dec;
            }
            else if((PINA & 0x03) == 0x03) {
                State = Reset;
            }
            else {
                State = Wait;
            }
            break;
        case Inc:
            State = IncDepressed;
            break;
        case IncDepressed:
            if((PINA & 0x01) == 0x01) {
                State = IncDepressed;
            }
            else {
                State = Wait;
            }
            break;
        case Dec:
            State = DecDepressed;
            break;
        case DecDepressed:
            if((PINA & 0x02) == 0x02) {
                State = DecDepressed;
            }
            else {
                State = Wait;
            }
            break;
        case Reset:
            if((PINA & 0x03) == 0x03) {
                State = Reset;
            }
            else {
                State = Wait;
            }
            break;
        default:
            State = Start;
            break;
    }
    switch(State) {
        case Start:
            PORTC = 0x07;
            break;
        case Begin:     
            PORTC = 0x07;
            break;
        case Wait:
            break;
        case Inc:
            if(PORTC < 0x09) {
                PORTC = PORTC + 1;
            }
            break;
        case IncDepressed:
            break;
        case Dec:
            if(PORTC > 0x00) {
                PORTC = PORTC - 1;
            }
            break;
        case DecDepressed:
            break;
        case Reset:
            PORTC = 0x00;
            break;
        default:
            PORTC = 0x07;
            break;
    }              
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    while (1) {
        Tick_Counter();
    }
    return 0;
}
