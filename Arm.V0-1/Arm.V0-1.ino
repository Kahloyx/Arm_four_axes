 /*Little improvements by Kahloyx kahloyx@gmail.com 2020*/


#include "VarSpeedServo.h"

VarSpeedServo servo1;   //Definition of 4 servos in the LibVarSpeedServo
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;

int axeX1 = 0;        //Def of horizontal axe left joystick pin to read
int axeY1 = 1;        //Def of vertical axe left joystick pin to read
int axeX2 = 2;        //Def of horizontal axe right joystick pin to read
int axeY2 = 3;        //Def of vertical axe right joystick pin to read

int X1;                   //Buffer for sticks values
int Y1;
int X2;
int Y2;

static int base = 70;         //
static int minibras = 110;    //
static int bras = 100;        //
static int pince = 80;        //

int Globinit = 0;

void setup()
{
  Serial.begin(9600);
  servo1.attach(11);          //Physical declaration of the 4 servos to work w/
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);

  servo1.write(70);     //base
  servo2.write(110);    //bras
  servo3.write(100);    //mini bras
  servo4.write(80);     //pince 80-120

  Serial.begin(9600);
}
void loop()
{
  if (Globinit == 0)                    //Only run once to know that the code is running
  {
    Serial.println("Hi master ^^");  //Only for my unsized ego ^^
    Globinit = 42 ;
  }
                                         ////////Base Movement///////
  X1 = analogRead(axeX1);

  if (X1 < 100)
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
  if (X1 > 900)
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
  Y1 = analogRead(axeY1);

  if (Y1 > 900)
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
  if (Y1 < 100)
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
  X2 = analogRead(axeX2);


  if (X2 < 100)
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
  if (X2 > 900)
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

                                           //////Hook///////
  Y2 = analogRead(axeY2);

  if (Y2 < 100)
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
  if (Y2 > 900)
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
