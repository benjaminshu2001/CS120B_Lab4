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

enum States {Start, Wait, Pound, PoundRelease, PressY, Locked} State;


void Tick_Lock() {
    //tempA0 = PINA & 0x01; //X
    unsigned char tempA1 = PINA & 0x02; //Y
    unsigned char tempA2 = PINA & 0x04; //#
    unsigned char tempA7 = PINA & 0x80; //lock from inside
    switch(State) {
        case Start:
            State = Wait;
            break;
        case Wait:
            if(tempA2 == 0x04) {
                State = Pound;
            }
            else if(tempA7 == 0x80) {
                State = Locked;
            }
            else {
                State = Wait;
            }
            break;
        case Pound:
            if(tempA2 == 0x04) {
                State = PoundRelease;
            }
            else {
                State = Pound;
            }
            break;
        case PoundRelease:
            if(tempA2 == 0x04) {
                State = PoundRelease;
            }
            else {
                State = PressY;
            }
            break;
        case PressY:
            if(tempA1 = 0x02) {
                State = PressY;
            }
            else {
                State = Wait;
            }
            break;
        case Locked:
            if(tempA7 == 0x80) {
                State = Locked;
            }
            else {
                State = Wait;
            }
            break;
    }
    switch(State) {
        case Start:
            PORTC = 0x00;
            break;
        case Wait:
            break;
        case Pound:
            break;
        case PoundRelease:
            break;
        case PressY:
            PORTB = 0x01;
            break;
        case Locked:
            PORTB = 0x00;
            break;
    }              
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    while (1) {
        Tick_Lock();
    }
    return 0;
}
