//#include <LiquidCrystal.h>

#include <Ultrasonic.h>

Ultrasonic ultrasonic (11, 10);//11 trigger 10 echo
//LiquidCrystal lcd(12,11,5,4,3,2);

long distancia;
int tempoDelay;
boolean flagTemp;

void setup(){
  //lcd.begin(16,2);
  //lcd.clear();
  //lcd.print("test");
  //delay(1000);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(13, HIGH);
  //Serial.begin(9600);
  //Serial.println("Lendo dados do sensor...");
  distancia = 15.0;
  tempoDelay = 20000;
  flagTemp = true;
}

float obterDistancia(){
  long microsec = ultrasonic.timing();
  return ultrasonic.convert(microsec, Ultrasonic::CM);
}

void loop(){
  //float cmMsec;//, inMsec;
  //long microsec = ultrasonic.timing();
  //cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  //inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  if(obterDistancia() <= distancia && flagTemp){
    digitalWrite(9, HIGH);
    
    delay(tempoDelay);
    if(obterDistancia() <= distancia){
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
  
  /*
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(cmMsec);
  lcd.setCursor(0,1);
  lcd.print(inMsec);
  
  */
  //Serial.print("Distancia em cm: ");
  //Serial.print(cmMsec);
  //Serial.print(" - Distancia em polegadas: ");
  //Serial.print(inMsec);
  //Serial.print("\n");
  
  delay(250);
}
