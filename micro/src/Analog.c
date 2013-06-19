#include <avr/io.h>

#include "inc/Analog.h"

uint16_t adc_read(uint8_t channel) {
	ADMUX 	= channel;
	ADCSRA	|= _BV(ADSC);
	while(!bit_is_set(ADCSRA,ADIF));
	ADCSRA	|= _BV(ADIF);

	return(ADC);
}

void adc_init(void) {
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); //Enable ADC and set 128 prescale
}
