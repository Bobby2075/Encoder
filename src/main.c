#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"

int main(void) {    

  uart_init(); // open the communication to the microcontroller
	io_redirect(); // redirect input and output to the communication    
  unsigned int time, deltaTime;
  TCCR1A = 0x00;
  DDRB &= ~0x01;
  PORTB |= 0x01;
  TIFR1 = (1 << ICF1);
  TCCR1B = (1 << ICNC1) | (1 << ICES1) | (1 << CS12) | (1 << CS10);

/*while (1)
{
  while ((TIFR1&(1<<ICF1)) == 0);
  time = ICR1;
  TIFR1 = (1<<ICF1);
  
  while ((TIFR1&(1<<ICF1)) == 0);

  time = ICR1 - time;
  
  printf("time is: %d", time);
}*/

  
  TCNT1 = 0;  

  while (1)
  {
    printf("\nTIFR1: %d ICF1: %x\nTCNT1: %d ICR1: %d\n", TIFR1, ICF1, TCNT1, ICR1);

    time = ICR1;
    deltaTime = time - ICR1;
    printf("Time: %d\n", time);
    TCNT1 = 0;
    ICR1 = 0;
    TIFR1 |= (1 << OCF1A) | (1 << ICF1);


    
    _delay_ms(1000);
  }
  


  return 0;

}