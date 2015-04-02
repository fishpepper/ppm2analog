/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

   author: fishpepper <AT> gmail.com
*/

#include "pwm.h"
#include <avr/io.h>

void pwm_init(){
	//set up output ports:
	//PORTD.6 = channel 0 ( 6)
	//PORTD.5 = channel 1 ( 5)
	//PORTB.3 = channel 2 (11)
	//PORTD.3 = channel 3 ( 3)
	DDRD |= (1<<3) | (1<<5) | (1<<6);
	DDRB |= (1<<3);

	//set up timer0
	TCCR0A |= (1 << WGM01) | (1 << WGM00); //activate fast pwm on timer 0
	TCCR0A |= (1 << COM0A1) | (1<<COM0B1); //set non-inverting mode
        TCCR0B |= (1 << CS00);   //set 64khz fast pwm
	//set up timer2
	TCCR2A = TCCR0A;
	TCCR2B = TCCR0B;

	//set pwms to center:
	for (uint8_t i=0; i<4; i++) pwm_set(i, 127);
}
	

void pwm_set(uint8_t channel, uint8_t value){
	switch(channel){
		default:
		case(0):
			OCR0A = value;
			break;
		case(1):
                        OCR0B = value;
                        break;
		case(2):
                        OCR2A = value;
                        break;
		case(3):
                        OCR2B = value;
                        break;
	}
}


		

