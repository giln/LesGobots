#include <Arduino.h>
#include <Wire.h>
//#include <SoftwareSerial.h>

int cpt_aller;
double distance;
double distanceFront;
double angle;
int vitesse;
int sens;

float getDistance() {
  digitalWrite(A5,  LOW);
  delayMicroseconds(2);
  digitalWrite(A5, HIGH);
  delayMicroseconds(10);
  digitalWrite(A5, LOW);
  return pulseIn(A4, HIGH, 30000) / 58.0;
}

float getDistanceFront() {
  digitalWrite(A3,  LOW);
  delayMicroseconds(2);
  digitalWrite(A3, HIGH);
  delayMicroseconds(10);
  digitalWrite(A3, LOW);
  return pulseIn(A2, HIGH, 30000) / 58.0;
}

void avancer(double vitesse)
{
  analogWrite(11, vitesse);
  digitalWrite(8, 1);
  digitalWrite(9, 0);
}

void arret()
{
  analogWrite(11, 0);
}


void tournerADroite(double angle)
{
  analogWrite(5, angle);
  digitalWrite(6, 1);
  digitalWrite(7, 0);
}

void tournerAGauche(double angle)
{
  analogWrite(5, angle);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
}

void setup() {
  Serial.begin(115200);
  cpt_aller = 0;

  pinMode(A5, OUTPUT);
  pinMode(A4, INPUT);

  pinMode(A3, OUTPUT);
  pinMode(A2, INPUT);

  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  angle = 0;
  vitesse = 255;
  avancer(vitesse);
  sens = 1;
}

void loop()
{
  /*
    tournerAGauche(255);
    delay(500);
    tournerADroite(255);
    delay(500);
  */
  distance = getDistance();

  Serial.println(distance);
  if (distance > 0)
  {
    if (distance < 50)
    {
      tournerAGauche(180);
    }
    else
    {
      if (distance > 70)
      {
        tournerADroite(180);
      }
      else
      {
        tournerAGauche(0);
      }
    }
  }
  delay(10);

  _loop();
}

void _delay(float seconds) {
  long endTime = millis() + seconds * 1000;
  while (millis() < endTime)_loop();
}

void _loop() {

}

