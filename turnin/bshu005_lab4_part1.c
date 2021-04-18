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

enum SM1_States {SM1_Start, SM1_Press1, SM1_Wait, SM1_Press2} SM1_STATE;

void Tick_LED() {
    unsigned char tempA = PINA & 0x01;
        switch(SM1_STATE) {
            case SM1_Start:
                SM1_STATE = SM1_Press1;
                break;
            case SM1_Press1:
                if(tempA == 0x01) {
                    SM1_STATE = SM1_Press1;
                }
                else {
                    SM1_STATE = SM1_Wait;
                }
                break;
            case SM1_Wait:
                if(tempA == 0x01) {
                    SM1_STATE = SM1_Wait;
                }
                else if(tempA == 0x00) {
                    SM1_STATE = SM1_Press2;
                }
                else {
                    SM1_STATE = SM1_Wait;
                }
                break;
            case SM1_Press2:
                if(tempA == 0x01) {
                    SM1_STATE = SM1_Press1;
                }
                else {
                    SM1_STATE = SM1_Wait;
                }
                break;
            default:
                SM1_STATE = SM1_Start;
                break;
        }
        switch(SM1_STATE) {
            case SM1_Start:
                PORTB = 0x01;
                break;
            case SM1_Press1:
                PORTB = 0x01;
                break;
            case SM1_Wait:
                break;
            case SM1_Press2:
                PORTB = 0x02;
                break;
            default:
                PORTB = 0x01;
                break;
        }
    }

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    while (1) {
        Tick_LED();
    }
    return 1;
}
