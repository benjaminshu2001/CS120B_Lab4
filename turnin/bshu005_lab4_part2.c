/*	Author: bshu005
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Wait, Inc, IncDepressed, Dec, DecDepressed, Reset} State;


void Tick_Counter() {
    unsigned char tempA0 = PINA & 0x01;
    unsigned char tempA1 = PINA & 0x02;
    switch(State) {
        case Start:
            State = Wait;
            break;
        case Wait:
            if(tempA0 && !tempA1) {
                State = Inc;
            }
            else if(!tempA0 && tempA1) {
                State = Dec;
            }
            else if(tempA0 && tempA1) {
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
            if(tempA0) {
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
            if(tempA1) {
                State = DecDepressed;
            }
            else {
                State = Wait;
            }
            break;
        case Reset:
            if(tempA0 && tempA1) {
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
        case Wait:
            break;
        case Inc:
            break;
        case IncDepressed:
            if(PORTC < 0x09) {
                PORTC = PORTC + 1;
            }
            break;
        case Dec:
            break;
        case DecDepressed:
            if(PORTC < 0x00) {
                PORTC = PORTC - 1;
            }
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
    DDRB = 0xFF; PORTB = 0x00;

    while (1) {
        Tick_Counter();
    }
    return 0;
}
