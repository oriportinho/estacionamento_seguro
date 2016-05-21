//#include <LiquidCrystal.h>

#include "Ultrasonic.h"

Ultrasonic ultrasonic (11, 10);//11 trigger 10 echo
//LiquidCrystal lcd(12,11,5,4,3,2);

long distancia;
int tempoDelay;
boolean flagTemp;
boolean flagDisplay = false;

void setup(){

	/*
	if(flagDisplay()){
		lcd.begin(16,2);
		lcd.clear();
		lcd.print("test");
		delay(1000);
	}
	*/

	Serial.begin(9600);

	pinMode(13, OUTPUT);   //Led de funcionamento
	pinMode(12,  INPUT);   //Botao de alteracao da distancia
	//pinMode(11,  INPUT); //sensor ultrasonico
	//pinMode(10,  INPUT); //sensor ultrasonico
	pinMode(9 , OUTPUT);   //Led de alerta de proximidade

	digitalWrite(13, HIGH);

	distancia = calibracao();
	
	tempoDelay = 20000;
	flagTemp = true;
}

long calibracao(){
	return (long)(analogRead(A0)/10 + 5);
}

float obterDistancia(){
	long microsec = ultrasonic.timing();
	return ultrasonic.convert(microsec, Ultrasonic::CM);
}

void loop(){
	while(digitalRead(12) == 1){ //verificar se deve mudar a calibracao
		distancia = calibracao();

		if(obterDistancia() <= distancia){
			digitalWrite(9, HIGH);
		}else{
			digitalWrite(9, LOW);
		}
		
		Serial.write(distancia);
		Serial.write(" | ");
		Serial.write((int)obterDistancia());
		Serial.write("\n");
		delay(250);
	}

	if(obterDistancia() <= distancia && flagTemp){ //verificar se deve ligar a led de aviso
		digitalWrite(9, HIGH);
		
		delay(tempoDelay);
		if(obterDistancia() <= distancia){ // desligar a led de aviso 2 mim depois para economizar energia
			digitalWrite(9, LOW);
			flagTemp = false;
		}
		
	}else{
		digitalWrite(9, LOW);
		delay(1000);
		if(obterDistancia() > distancia){
			flagTemp = true;
		}
	}
	
	if(flagDisplay){ //mostrar a tela
		//mostrarTela();
	}


	Serial.write((int)distancia);
	Serial.write(" | ");
	Serial.write((int)obterDistancia());
	Serial.write("\n");
	delay(250);
}

/*
void mostrarTela(){
	float cmMsec;
	long microsec = ultrasonic.timing();
	cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
	inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(cmMsec);
	lcd.setCursor(0,1);
	lcd.print(inMsec);
	
	Serial.print("Distancia em cm: ");
	Serial.print(cmMsec);
	Serial.print(" - Distancia em polegadas: ");
	Serial.print(inMsec);
	Serial.print("\n");
}
*/