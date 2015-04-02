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

#include "uart.h"
#include "main.h"
#include "ppm.h"
#include "adc.h"

//arduino pinout: http://www.jameco.com/Jameco/workshop/JamecoBuilds/arduinocircuit_fig12.jpg

//stdout to uart
static FILE mystdout = FDEV_SETUP_STREAM( uart_putc_s, NULL, _FDEV_SETUP_WRITE );

void ppm_to_pwm(uint8_t ppm_channel, uint8_t pwm_channel){
	//convert to 8bit 0...255:
	uint16_t input = ppm_data[ppm_channel];
	//expected input is 1000-2000us
	//limit to this in case of out of bounds values:
        input = max(1000, min(2000, input));

	//rescale from 1000..2000 -> 0..255
        input = ((input - 1000)*65) / (1000L*65/255);

	printf("IN[%d] = %5d -> %3d (%d)\n",ppm_channel,ppm_data[ppm_channel],input,pwm_channel);

	//set value:
	pwm_set(pwm_channel, (uint8_t)input);
}

int main(void) {
	uart_init();
	stdout = &mystdout;
	printf("- ppm2analog debug output -\n");
 
   	ppm_init();
	pwm_init();

	//enable ints
	sei();
	
	//enable adc with ints enabled
	adc_init();

	while(1){
		//printf("INPUT : %5d %5d %5d %5d\n",ppm_data[0], ppm_data[1], ppm_data[2], ppm_data[3]);
		//printf("ADC IN: "); for(uint8_t i=0; i<8; i++) printf("%3d ",adc_data[i]); printf("\n");
		delay_ms(10);
		ppm_to_pwm(0, 0);
		ppm_to_pwm(1, 1);
		ppm_to_pwm(2, 2);
		ppm_to_pwm(3, 3);
	}
	

}

