#include "avr/io.h"
#include <math.h>  
#include <stdlib.h>
#include <util/delay.h>

#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
int RMS(int repeat);
void ADC_Init();
long lerADC();
void print(char *msg);
float to_analog(int val);

int main( void )
{
	USART_Init ( MYUBRR );
	ADC_Init();
	//USART_Transmit(recieved+1);
		
	int val = 0;
	float val_analog = 0.0;
    while(1) {
        val = RMS(30);    //accumulate x mesures. Recomended x=30;
		val_analog = to_analog(val);
		char buffer [50];
		char buffer_analog [10];
		itoa (val,buffer,10); // converte int em string
		dtostrf(val_analog,3, 2, buffer_analog);// converte float em string

		print("Digital: ");
		print(buffer);
		USART_Transmit('\n');
		USART_Transmit('\r');

		print("Analog: ");
		print(buffer_analog);
		USART_Transmit('\n');
		USART_Transmit('\r');
        _delay_ms(300);
    }
    return 0;
} // main

float to_analog(int val){
	return 5.0*val/1024;
}

void print(char *msg){
	for(char *inputPtr = msg; *inputPtr; ++inputPtr)
	{
		USART_Transmit(*inputPtr);
	}

}

void ADC_Init(){
	//configura o clock a ser usado para o conversor ADC usando um divisor de 128
	//com isso: 16000000/128 = 125Khz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	//configura a tensão de referência para AVCC
	ADMUX |= (1 << REFS0);
	
	//habilita o ADC
	ADCSRA |= (1 << ADEN);
	
	//inicia a medição do ADC
	ADCSRA |= (1 << ADSC);
	
	//por padrão ele já vai ler do canal 0 (ADC0)
	//se precisar trocar tem que alterar os bits 0 a 4 do registrador ADMUX
}

long lerADC(){
	//inicia a medição do ADC
	ADCSRA |= (1 << ADSC);
	long leitura = 0;
	leitura = ADCL;
	leitura |= (ADCH << 8);
	
	return leitura;
}

int RMS(int repeat){
	int i = 1;
	// tem que ser long por causa do tamanho máximo da variável, int não dá
	long accumulated= 0L;
    do {
        long digital_value = lerADC();//read(analog_value);   //convert the analog-value (voltage) to digital one (0-1024)
        accumulated = accumulated+ (digital_value*digital_value);      //accumulate all the digital-values “repeat” times
        i++;
    } while(repeat >=i);
    
    long average = accumulated / repeat;
    return sqrt(average);
}

void USART_Init(unsigned int ubrr){
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
} // USART_Init


void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

 
