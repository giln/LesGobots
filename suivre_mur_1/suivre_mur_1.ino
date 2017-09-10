#include <Arduino.h>
#include <Wire.h>
//#include <SoftwareSerial.h>

int cpt_aller;
int cpt_retour;
double distance;
const int numLectures = 3;
double lectures[numLectures];
int indice;
double total;

float getDistance(){
    digitalWrite(A5,  LOW);
    delayMicroseconds(2);
    digitalWrite(A5, HIGH);
    delayMicroseconds(10);
    digitalWrite(A5, LOW);
    return pulseIn(A4, HIGH, 30000)/58.0;
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
    analogWrite(5, vitesse/3);
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
    analogWrite(5, vitesse);
    analogWrite(11, vitesse/3);
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
    //Serial.begin(115200);
    cpt_aller = 0;
    cpt_retour = 0;
    indice = 0;
    total = 0;
    
    for (int i=0; i<numLectures; i++)
      lectures[i] = getDistance();
      
    pinMode(A5, OUTPUT);
    pinMode(A4, INPUT);
    pinMode(5, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
}

void loop()
{
    total = total - lectures[indice];
    lectures[indice] = getDistance();
    total = total + lectures[indice];
    indice = indice + 1;
    if (indice >= numLectures)
      indice = 0;

    distance = total / (double)numLectures;
    
    //Serial.println(distance);
    
    if((distance) > (150))
    {
        cpt_aller += 1;
        if((cpt_retour) > (3))
        {
            cpt_retour = 0;
            cpt_aller = 0;
            avancer(170);
            _delay(0.5);
            arret();
            _delay(10);
        }
        else
        {
            if((cpt_aller) > (3))
            {
                cpt_aller = 0;
                avancerSurLaDroite(170);
                _delay(0.01);
            }
            else
            {
                tournerADroite(170);
                _delay(0.1);
                arret();
            }
        }
    }
    else
    {
        if((distance) > (60))
        {
            cpt_aller = 0;
            avancerSurLaDroite(170);
            _delay(0.01);
        }
        else
        {
            if((distance) > (40))
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
                    avancerSurLaGauche(170);
                    _delay(0.01);
                }
                else
                {
                    if((distance) > (0))
                    {
                        if((cpt_aller) > (0))
                        {
                            cpt_retour += 1;
                        }
                        else
                        {
                            cpt_retour = 0;
                        }
                        tournerAGauche(170);
                        _delay(0.2);
                        arret();
                    }
                }
            }
        }
        _delay(0.001);
    }
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

