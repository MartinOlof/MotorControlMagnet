#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define ADC_VALUE 614 // 307 = 1,5V 410 = 2V 512 = 2,5V 614 = 3V 717 = 3,5V 819 = 4V 922 = 4,5V 1024 = 5V, Inställd på 3V, byt ut värdet för att ändra
#define IN_A PORTB |= (1 << PB5)
#define IN_B PORTB |= (1 << PB3)
#define PWM PORTB |= (1 << PB0)
#define CS PORTB |= (1 << PB1)
#define SEL0 PORTB |= (1 << PB2)

uint16_t adcConvert();
void setupADC();


int main(void){

  setupADC();

  while(1){
    uint16_t val = adcConvert();
    if(val >= ADC_VALUE){
      IN_A;
    }
    else{
      IN_B;
    }
    
  }
  
}



void setupADC{
  ADMUX |= (0 << MUX0) | (1 << MUX1) | (0 << MUX2) | (0 << MUX3); //ADC2 PB4
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
  DIDR0 = (1 << ADC1D)
  ADMUX |= (0 << REFS0);
}

uint16_t adcConvert(){

  int Ain, AinLow;
  ADCSRA |= (1 << ADSC);

  while(ADCSRA &(ADIF) == 0);

  AinLow = (int) ADCL;
  Ain = ADCH*256;

  Ain += AinLow;

  return Ain;
  
}
