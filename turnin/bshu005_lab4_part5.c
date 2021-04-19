/*	Author: bshu005
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Wait, Pound, PoundRelease, PressY, YRelease, Locked, Wait2} State;


void Tick_Lock() {
    //tempA0 = PINA & 0x01; //X
    //unsigned char tempA1 = PINA & 0x02; //Y
    //unsigned char tempA2 = PINA & 0x04; //#
    //unsigned char tempA7 = PINA & 0x80; //lock from inside
    switch(State) {
        case Start:
            State = Wait;
            break;
        case Wait:
            if(PINA == 0x04) {
                State = Pound;
            }
            else {
                State = Wait;
            }
            break;
        case Pound:
            if(PINA == 0x04) {
                State = Pound;
            }
            else if(PINA == 0x00){
                State = PoundRelease;
            }
            else {
                State = Wait;
            }
            break;
        case PoundRelease:
            if(PINA == 0x00) {
                State = PoundRelease;
            }
            else if(PINA == 0x02) {
                State = PressY;
            }
            else {
                State = Wait;
            }
            break;
        case PressY:
            if(PINA == 0x02) {
                State = PressY;
            }
            else if(PINA == 0x00){
                State = YRelease;
            }
            break;
        case YRelease:
            if(PINA == 0x80) {
                State = Wait;
            }
            else if(PINA == 0x00){
                State = YRelease;
            }
            else if(PINA == 0x04) {
                State = Locked;
            }
            break;
        case Locked:
            if(PINA == 0x80) {
                State = Wait;
            }
            else if(PINA == 0x00) {
                State = Wait2;
            }
            else if(PINA == 0x04) {
                State = Locked;
            }
            break;
        case Wait2:
            if(PINA == 0x00) {
                State = Wait2;
            }
            else if(PINA == 0x80 || PINA == 0x02) {
                State = Wait;
            }
            else {
                State = YRelease;
            }
            break;
    }
    switch(State) {
        case Start:
            PORTB = 0x00;
            break;
        case Wait:
            PORTB = 0x00;
            break;
        case Pound:
            break;
        case PoundRelease:
            break;
        case PressY:
            PORTB = 0x01;
            break;
        case YRelease:
            break;
        case Locked:
            break;
        case Wait2:
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
