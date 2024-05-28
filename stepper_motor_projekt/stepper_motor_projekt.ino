#include <Arduino.h>

//určení pinů pro řduino
#define in1 4  //piny pro L298N modul
#define in2 5
#define in3 6
#define in4 7
#define encoder0PinA 2  //piny rotačního enkodéru
#define encoder0PinB 3

int A = HIGH;  //proměná pro změnu směru
int B = LOW;

//opakující se smyčka
void setup() {
  pinMode(in1, OUTPUT);  //definice pinů pro L298N modul
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT); 
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoder, CHANGE);  //tato část spustí "void doencoder" pouze pokud nastane změna na enkodéru
} 

//tato smyška se jednou spustí po jednom pohybu enkodéru
void doEncoder(){ 
if(digitalRead(encoder0PinB) == digitalRead(encoder0PinA)){  //tato část rozhoduje jestli se enkodér otáčí vpčed nebo vzat
    A = LOW;
    B = HIGH;
   Serial.println("vpřed");  //upravení cyklusu vpřed
  }
  else{
    A = HIGH;
    B = LOW;
    Serial.println("vzad");  //upravení cyklusu vzat
  }
   
  digitalWrite(in1, HIGH);  //cyklus krokáče který se ovlivnujě na zísadě hořejšího rozpoznání
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(5);

  digitalWrite(in1, A);
  digitalWrite(in2, B);
  digitalWrite(in3, B);
  digitalWrite(in4, A);
  delay(5);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(5);

  digitalWrite(in1, B);
  digitalWrite(in2, A);
  digitalWrite(in3, A);
  digitalWrite(in4, B);
  delay(5);
}

void loop(){}  //bez loopu arduino ide nás nenechá nahrát code, tato část nemá jiný účel