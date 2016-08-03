#include "Ultrasonic.h"

Ultrasonic ultrasonic (11, 10);//11 trigger 10 echo

long distancia;
int tempoDelay;
bool serial;
bool flagTemp;

void setup(){
	// Serial para debug, mudar valor para true em caso de querer debugar o codigo
	serial = false;
	if(serial)
		Serial.begin(9600);

	// Instanciar pinos
	pinMode(13, OUTPUT);   // Led de funcionamento
	pinMode(12,  INPUT);   // Botao de alteracao da distancia
	pinMode(11,  INPUT);   // Sensor ultrasonico (trigger)
	pinMode(10,  INPUT);   // Sensor ultrasonico (echo)
	pinMode( 9, OUTPUT);   // Led de alerta de proximidade

	// Led de funcionamento
	digitalWrite(13, HIGH);

	// Instancias iniciais
	distancia = calibracao();
	tempoDelay = 20000;
	flagTemp = true;
}

void loop(){
	// Verificar se o botao de calibracao esta ativo, se sim, alterar a calibracao
	while(digitalRead(12) == 1){
		distancia = calibracao();
		flagTemp = true;
		digitalWrite(9, LOW);

		// Testar a nova calibracao
		if(obterDistancia() <= distancia){
			digitalWrite(9, HIGH);
		}else{
			digitalWrite(9, LOW);
		}

		// Debug
		if(serial){
			Serial.write(distancia);
			Serial.write(" | ");
			Serial.write((int)obterDistancia());
			Serial.write("\n");
		}

		delay(100);
		digitalWrite(9, LOW);
	}

	// Verifica se deve ligar a led de aviso
	if(flagTemp && obterDistancia() <= distancia){
		digitalWrite( 9, HIGH);
		delay(tempoDelay);

		// Desligar a led de aviso para economizar energia
		if(obterDistancia() <= distancia){
			digitalWrite( 9,  LOW);
			flagTemp = false;
		}

	}else{
		digitalWrite( 9,  LOW);
		delay(tempoDelay);
		if(obterDistancia() > distancia){
			flagTemp = true;
		}
	}

	// Debug
	if(serial){
		Serial.write((int)distancia);
		Serial.write(" | ");
		Serial.write((int)obterDistancia());
		Serial.write("\n");
	}

	delay(250);
}

// Metodo para calibrar o sistema de acordo com o valor do potenciometro
long calibracao(){
	return (long)(analogRead(A0)/10 + 5);
}

// Metodo para calcular a distancia usando o sensor
float obterDistancia(){
	long microsec = ultrasonic.timing();
	return ultrasonic.convert(microsec, Ultrasonic::CM);
}
