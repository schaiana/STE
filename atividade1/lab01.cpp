#include <avr/io.h>

void ligaLed1(){
	//liga led / coloca como HIGH pino 8 (PH5)
	PORTH |= (1 << PIN5);
}

void desligaLed1(){
	//desliga led / coloca como LOW pino 8 (PH5)
	PORTH &= ~(1 << PIN5);
}

void ligaLed2(){
	//liga led pino 9 (PH6)
	PORTH |= (1 << PIN6);
}

void desligaLed2(){
	//desliga led pino 9 (PH6)
	PORTH &= ~(1 << PIN6);
}

void loop(){
	while(true){
		if(!(PINE & (1 << PIN4))){ //compara o botão, se pressionado
			ligaLed1(); //liga o led
		} else { // se não pressionado, desliga o led
			desligaLed1();
		}
		if(PINE & (1 << PIN5)){ //compara o botão, se pressionado
			ligaLed2(); //liga o led
		} else { // se não pressionado, desliga o led
			desligaLed2();
		}
	}
}

void configuraPinos(){
	//pino 8 (PH5) led - output
	DDRH |= (1 << DD5);
	//pino 9 (PH6) led - output
	DDRH |= (1 << DD6);

	//pino 2 (PE4) botao - input
	DDRE &= ~(1 << DD4);
	//pino 3 (PE5) botao - input
	DDRE &= ~(1 << DD5);

}

int main(void){
	configuraPinos();
	loop();
}
