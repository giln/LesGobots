#include <Arduino.h>
#include <Wire.h>
//#include <SoftwareSerial.h>

int cpt_aller;
double distance;
double distanceFront;

float getDistance(){
    digitalWrite(A5,  LOW);
    delayMicroseconds(2);
    digitalWrite(A5, HIGH);
    delayMicroseconds(10);
    digitalWrite(A5, LOW);
    return pulseIn(A4, HIGH, 30000)/58.0;
}

float getDistanceFront(){
    digitalWrite(A3,  LOW);
    delayMicroseconds(2);
    digitalWrite(A3, HIGH);
    delayMicroseconds(10);
    digitalWrite(A3, LOW);
    return pulseIn(A2, HIGH, 30000)/58.0;
}

void avancer(double vitesse)
{
    analogWrite(5, vitesse);
    analogWrite(11, vitesse);
    digitalWrite(6, 1);
    digitalWrite(7, 0);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
}

void arret()
{  
    analogWrite(5, 0);
    analogWrite(11, 0);
}

void avancerSurLaDroite(double vitesse)
{  
    analogWrite(5, vitesse/4);
    analogWrite(11, vitesse);
    digitalWrite(6, 1);
    digitalWrite(7, 0);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
}

void tournerADroite(double vitesse)
{
    analogWrite(5, vitesse);
    analogWrite(11, vitesse);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
}

void avancerSurLaGauche(double vitesse)
{
    analogWrite(5, 255);
    analogWrite(11, vitesse);
    digitalWrite(6, 1);
    digitalWrite(7, 0);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
}

void tournerAGauche(double vitesse)
{
    analogWrite(5, vitesse);
    analogWrite(11, vitesse);
    digitalWrite(6, 1);
    digitalWrite(7, 0);
    digitalWrite(8, 1);
    digitalWrite(9, 0);
}

void setup(){
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
}

void loop()
{
    distanceFront = getDistanceFront();
    Serial.println(distanceFront);

    if ((distanceFront < 20) && (distanceFront > 0))
    {
        tournerAGauche(170);
        _delay(0.2);
    }
    else
    {
        
        distance = getDistance();
        
        //Serial.println(distance);
        
        if((distance) > (80))
        {
            if((cpt_aller) > (3))
            {
                tournerADroite(170);
                _delay(0.1);
            }
            else
            {
                cpt_aller = 0;
                avancerSurLaDroite(255);
                _delay(0.01);
            }
            cpt_aller += 1;
        }
        else
        {
            if((distance) > (50))
            {
                cpt_aller = 0;
                avancer(255);
                _delay(0.01);
            }
            else
            {
                if((distance) > (20))
                {
                    cpt_aller = 0;
                    avancerSurLaGauche(map(distance,20,50,80,200));
                    _delay(0.01);
                }
                else
                {
                    if((distance) > (0))
                    {
                        tournerAGauche(170);
                        _delay(0.2);
                        avancer(170);
                        _delay(0.2);
                    }
                }
            }   
        }
    }
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

