#include "VarSpeedServo.h"

VarSpeedServo servo1;   //four servos defined
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;

int potpin1 = 0;        //Définir le port A0 d'entrée horizontale du joystick gauche
int potpin2 = 1;        //Définissez le joystick gauche pour entrer le port A1 dans le sens vertical
int potpin3 = 2;        //Définir le port d'entrée droite du joystick horizontal A2
int potpin4 = 3;        //Définissez le joystick droit pour entrer le port A3 verticalement.

int val1;
int val2;
int val3;
int val4;

static int base = 70;         //Définit l'angle initial du servo de base à 70
static int minibras = 110;    //Définir l'angle initial du servo de base à 110
static int bras = 100;        //Définir l'angle initial du grand appareil à 100
static int pince = 80;        //Définir l'angle initial du servo de patte à 80

int salute = 0;

void setup()
{
  Serial.begin(9600);
  servo1.attach(11);          //definition de l'attache de chaque servo sur les bornes 11 ect
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);

  servo1.write(70);     //base                             maz
  servo2.write(110);    //bras
  servo3.write(100);    //mini bras
  servo4.write(80);     //pince 80-120

  //Serial.begin(9600);
}
void loop()
{
  if (salute == 0)
  {
    Serial.println("Hi master ^^");
    salute = 42 ;
  }
  /////Contrôle de base///////
  val1 = analogRead(potpin1);         //de 10 à 170

  if (val1 < 100)
  {
    base = base - 1;
    if (base <= 10)
    {
      base = 10;
    }
    Serial.print("base : ");
    Serial.println(base);
    servo1.write(base);

    delay(50);
  }
  if (val1 > 900)
  {
    Serial.print("base : ");
    Serial.println(base);
    base = base + 1;
    if (base >= 170)
    {
      base = 170;
    }
    servo1.write(base);

    delay(50);
  }

  //////Bras de commande de direction///////
  val2 = analogRead(potpin2);     //10 à 170

  if (val2 > 900)
  {
    minibras = minibras - 1;
    if (minibras <= 10)
    {
      minibras = 10;
    }
    Serial.print("minibras : ");
    Serial.println(minibras);
    servo2.write(minibras);

    delay(50);
  }
  if (val2 < 100)
  {
    Serial.print("minibras : ");
    Serial.println(minibras);
    minibras = minibras + 1;
    if (minibras >= 170)
    {
      minibras = 170;
    }
    servo2.write(minibras);

    delay(50);
  }

  //////Commande de direction à gros bras///////
  val3 = analogRead(potpin3);              //10 to170


  if (val3 < 100)
  {
    bras = bras - 1;
    if (bras <= 10)
    {
      bras = 10;
    }
    Serial.print("bras : ");
    Serial.println(bras);
    servo3.write(bras);

    delay(50);
  }
  if (val3 > 900)
  {
    Serial.print("bras : ");
    Serial.println(bras);
    bras = bras + 1;
    if (bras >= 170)
    {
      bras = 170;
    }
    servo3.write(bras); 

    delay(50);
  }

  //////Servocommande griffe///////
  val4 = analogRead(potpin4);               //80 to 130

  if (val4 < 100)
  {
    pince = pince - 1;
    if (pince <= 80)
    {
      pince = 80;
    }
    Serial.print("pince : ");
    Serial.println(pince);
    servo4.write(pince);


    delay(50);
  }
  if (val4 > 900)
  {
    Serial.print("pince : ");
    Serial.println(pince);
    pince = pince + 1;
    if (pince >= 130)
    {
      pince = 130;
    }
    servo4.write(pince);

    delay(50);
  }

}
