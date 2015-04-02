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

#include "ppm.h"
#include "uart.h"

//ICP1 = PORTB.0 = PPM INPUT (8)

void ppm_init(){
	//initialise ICP pin as input:
	DDRB &= ~(1<<0);

	//set up timer1
	TCCR1A = 0; //disable pwm
	TCCR1B = (1<<ICES1) | (1<<CS11) | (0<<CS10); //prescaler = 8 -> 0.5usec per tick
        TCCR1C = 0;

	TIFR1 |= (1<<ICF1); //CLEAR pending interrupts
	TIMSK1 |= (1<<ICIE1); //enable compare interrupt

	ppm_state = PPM_STATE_WAIT_FOR_SYNC;
	ppm_channel = 0;

}


ISR(TIMER1_CAPT_vect){
	//fetch length of pulse:
	//counter runs at 0.5us/tick -> divide by two to get us
	uint16_t width = ICR1/2; 
	ww=width;
	
	switch(ppm_state){
		default:
		case(PPM_STATE_WAIT_FOR_SYNC):
			//check if this is a sync pulse:
			if ((width >= PPM_SYNC_WIDTH_MIN) && (width <= PPM_SYNC_WIDTH_MAX)){
				//oh, this is a valid sync pulse!
				ppm_state = PPM_STATE_FETCH_DATA;
				ppm_channel = 0;
			}else{
				//invalid sync pulse, ignore
			}
			break;

		case(PPM_STATE_FETCH_DATA):
			//check if this is a valid data pulse:
			if ((width >= PPM_CHANNEL_WIDTH_MIN) && (width <= PPM_CHANNEL_WIDTH_MAX)){
				//fine, this is a valid dataset
                                ppm_data[ppm_channel] = width;
                                ppm_channel++;

                                if (ppm_channel >= PPM_CHANNELS){
                                        //fine, next is a sync pulse:
                                        ppm_state = PPM_STATE_WAIT_FOR_SYNC;
                                }
                        }else{
                                //invalid data! return to sync
				ppm_state = PPM_STATE_WAIT_FOR_SYNC;
			}
			break;
	}
	TCNT1=0;
}

