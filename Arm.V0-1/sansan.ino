

void sanboot() {

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.invertDisplay(true);
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  //display.display();
  //delay(500); // Pause for 2 seconds
  display.invertDisplay(false);

  // Clear the buffer
  display.clearDisplay();
  /*
    // Draw a single pixel in white
    display.drawPixel(64, 32, SSD1306_WHITE);

    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000); */

  //testdrawstyles();    // Draw 'stylized' characters
  rndmlines();
  testscrolltext();    // Draw scrolling text
  testdrawbitmap();    // Draw a small bitmap image

  // Invert and restore display, pausing in-between

  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
}

void rndmlines() {
  display.clearDisplay();
  Serial.println("Love pancakes");
  for (int j = 0 ; j <= 128 ; j++ ) {
    Serial.println("fucker of gooses");
    display.clearDisplay();
    int w = 0;
    int ww = 0;
    int zz = 0;
    int z = 0;
    w = random(0, 128);
    z = random(0, 64);
    ww = random(0, 128);
    zz = random(0, 64);
    display.drawLine(ww, zz , w, z , SSD1306_WHITE);
    display.display();
    delay(100);
  }
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(3000);
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setCursor(0, 16);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.println(F("Fucked"));
  display.display();      // Show initial text
  delay(50);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(500);
  display.startscrollleft(0x00, 0x07);
  delay(500);
  display.stopscroll();
  delay(500);
  display.startscrolldiagright(0x00, 0x07); //(0x00, 0x00) to translate text upper
  delay(500);
  display.startscrolldiagleft(0x00, 0x07);
  delay(500);
  display.stopscroll();
  delay(1);
}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  display.startscrolldiagright(0x00, 0x00);
  delay(5000);
}

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for (f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    //icons[f][YPOS]   = -LOGO_HEIGHT;

    icons[f][YPOS]   = 15;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for (;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for (f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(20);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for (f = 0; f < NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        //icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][YPOS]   = 15;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}
