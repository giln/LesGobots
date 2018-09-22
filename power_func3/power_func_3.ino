#include <Arduino.h>
#include <Wire.h>

//#define DEBUG

#ifdef DEBUG
  #include <SoftwareSerial.h>
  #define DEBUG_PRINT(x)  Serial.print (x)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

const double minArche = 50;
const double maxArche = 190;
const int maxTours = 1;
const int maxZeros = 3;
const int delaiLectureHaut = 5000;
const int distanceMin1 = 25;
const int distanceMin2 = 50;
const int distanceMax1 = 100;
const int distanceMax2 = 125;

int cpt_aller;
double distance;
double distanceHaut;
int compteTour;
bool lireHaut;
long top;
bool marche;
double angle;
int vitesse;
int sens;
int compteurZeros;
int compteurHaut;

float getDistance(){
    digitalWrite(A5,  LOW);
    delayMicroseconds(2);
    digitalWrite(A5, HIGH);
    delayMicroseconds(10);
    digitalWrite(A5, LOW);
    return pulseIn(A4, HIGH, 30000)/58.0;
}

float getDistanceHaut(){
    digitalWrite(A3,  LOW);
    delayMicroseconds(2);
    digitalWrite(A3, HIGH);
    delayMicroseconds(10);
    digitalWrite(A3, LOW);
    return pulseIn(A2, HIGH, 30000)/58.0;
}

void avancer(double vitesse)
{
    analogWrite(11, vitesse);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
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

void setup()
{
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
    cpt_aller = 0;
    compteTour = 0;
    lireHaut = false;
    top = top = millis();
    marche = true;
    compteurZeros = 0;
    compteurHaut = 0;
    
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

    DEBUG_PRINTLN("loop +++++++++++++++++++++++++++++++++++++");
    
    DEBUG_PRINT("lireHaut : ");
    DEBUG_PRINTLN(lireHaut);

    DEBUG_PRINT("compteTour : ");
    DEBUG_PRINTLN(compteTour);

    if (compteTour == maxTours + 1) // si on a fait le bon nombre de tours on s'arrete ( + 1 pour passage de l'arche du premier tour qui ne compte pas)
    {
        marche = false;
        _delay(0.5);
        arret();
    }
    
    if ((lireHaut == false) && (millis() > top+delaiLectureHaut)) // on attend 5 secondes après une détection de l'arche avant de lire vers le haut à nouveau
    {
        lireHaut = true;
    }

    if (lireHaut == true)
    {
        distanceHaut = getDistanceHaut();
 
        DEBUG_PRINT("distanceHaut : ");
        DEBUG_PRINTLN(distanceHaut);

        if ((distanceHaut > minArche) && (distanceHaut < maxArche)) // on passe sous la ligne d'arrivée = on détecte l'arche
        {
            compteurHaut = compteurHaut + 1;
        }
        else
        {
            compteurHaut = 0;
        }

        if (compteurHaut > 3)
        {
            lireHaut = false;
            top = millis();
            compteTour = compteTour + 1;
            compteurHaut = 0;
        }
    }

    if (marche == true) // on avance toujours sauf si on a atteint le nombre de tours défini
    {
    distance = getDistance();

        if (distance == 0)
        {
          compteurZeros = compteurZeros + 1;
        }
        else
        {
          compteurZeros = 0;
        }

        if (compteurZeros > maxZeros) // si on lit plusieurs 0 à la suite, le mur est loin : on simule la distance max
        {
          distance = distanceMax2;
        }

        
        if (distance>0) 
{
        DEBUG_PRINT("Distance à droite : ");
        DEBUG_PRINTLN(distance);
  if (distance < distanceMin1)
  {
    
      tournerAGauche(180);
  }
  else if (distance < distanceMin2)
  {
    tournerAGauche(120);
  }
  else if (distance < distanceMax1)
  {
    tournerAGauche(0);
  }
  else if (distance < distanceMax2)
  {
    tournerADroite(120);
  }
  else
  {
    tournerADroite(180);
  }
  
}

#ifdef DEBUG
 delay(100);
#else
 delay(10);
#endif
 
    }
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

