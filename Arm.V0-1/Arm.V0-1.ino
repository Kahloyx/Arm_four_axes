/*Little improvements by Kahloyx kahloyx@gmail.com 2020*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     8// Number of snowflakes in the animation example

#define LOGO_HEIGHT   32
#define LOGO_WIDTH    32
static const unsigned char PROGMEM logo_bmp[] = {
  B00000000, B00111111, B11111100, B00000000,
  B00000000, B11110000, B00000011, B10000000,
  B00000011, B00000000, B00000000, B01100000,
  B00000100, B00000000, B00000000, B00010000,
  B00001000, B00000000, B00000000, B00001000,
  B00110000, B00000000, B00000000, B00000110,
  B01000000, B00000000, B00000000, B00000010,
  B10000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000001,
  B10000000, B00000000, B00000000, B00000001,
  B10000111, B11000000, B00000011, B11100001,
  B10011111, B11100000, B00000111, B11111001,
  B10111111, B11110000, B00001111, B11111101,
  B10111110, B01110000, B00001110, B01111101,
  B01111110, B01110000, B00001110, B01111110,
  B01011111, B11100001, B10000111, B11111010,
  B00100111, B11100001, B10000111, B11100100,
  B00100000, B01000011, B11000010, B00000100,
  B01000001, B10000011, B11000001, B10000010,
  B01000100, B00000011, B11000000, B00100010,
  B01000100, B00000000, B00000000, B00100010,
  B01001101, B10000000, B00000001, B11110010,
  B00100101, B00111111, B11111110, B11100100,
  B00100011, B00010010, B00100010, B10000100,
  B00010001, B10010010, B00100011, B00001000,
  B00001000, B01110010, B00100110, B00010000,
  B00000110, B00011111, B11111000, B01100000,
  B00000001, B11000000, B00000011, B10000000,
  B00000000, B00111111, B11111100, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000
};                                                //All the above declarations are made for the i2c oled screen dual color (yellow on top and blue for the rest)


#include "VarSpeedServo.h" //Lib of arm Servos based on the built-in lib of arduino, available on the git repo

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
static int minibras = 100;    //
static int bras = 110;        //
static int pince = 80;        //

int Globinit = 0;

void setup()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  Serial.begin(9600);
  display.clearDisplay();
  display.display();
  display.invertDisplay(true);
  servo1.attach(11);          //Physical declaration of the 4 servos to work w/
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);
                                      //init of servos (bullshiting bc it all move)
  //servo1.write(84);     //base
  //servo2.write(110);    //bras
  //servo3.write(100);    //mini bras
  //servo4.write(80);     //pince 80-120
  delay(500);
  display.invertDisplay(false);
  delay(500);
  display.clearDisplay();
  display.display();
  delay(50);
  display.setTextSize(2);                     // Draw 1X-scale text
  display.setCursor(0, 16);                   //Set cursor in th blue oled screen part
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Hi Kah san"));
  display.display();
  delay(1000);
  display.setCursor(0, 48);
  display.setTextColor(SSD1306_WHITE);
  display.println("Let's go !");
  display.display();
  delay(2000);
  //rndmlines();
}


void loop()
{
  if (Globinit == 0)                    //Only run once to know that the code is running
  {
    Serial.println("Let's start !");
    Globinit = 42 ;
  }
                                                    ////////Base Rotation///////
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
    servo1.write(base, 126);

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

                                                //////Main arm///////
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

                                                            //////Base arm///////
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
