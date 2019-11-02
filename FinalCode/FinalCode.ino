#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const unsigned char PROGMEM resistance [] = {
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x06, 0x04, 0x00, 0x00, 0x0F, 0x88,
0x00, 0x00, 0x18, 0xD0, 0x00, 0x00, 0x38, 0x60, 0x00, 0x00, 0x6C, 0x30, 0x00, 0x00, 0xC6, 0x18,
0x00, 0x00, 0x83, 0x08, 0x00, 0x01, 0x81, 0x8C, 0x00, 0x03, 0x00, 0xCC, 0x00, 0x07, 0x80, 0x78,
0x00, 0x0C, 0xC0, 0x30, 0x00, 0x18, 0x60, 0x60, 0x00, 0x38, 0x30, 0xC0, 0x00, 0x6C, 0x1B, 0x80,
0x01, 0xC6, 0x0E, 0x00, 0x03, 0x03, 0x0C, 0x00, 0x07, 0x01, 0x98, 0x00, 0x0D, 0x80, 0xF0, 0x00,
0x18, 0xC0, 0x60, 0x00, 0x30, 0x60, 0xC0, 0x00, 0x30, 0x31, 0x80, 0x00, 0x10, 0x19, 0x00, 0x00,
0x18, 0x0F, 0x00, 0x00, 0x0C, 0x06, 0x00, 0x00, 0x06, 0x0C, 0x00, 0x00, 0x0B, 0x18, 0x00, 0x00,
0x11, 0xF0, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
};
const unsigned char PROGMEM led [] = {
0x00, 0x07, 0xE0, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x78, 0x1E, 0x00,
0x00, 0xE0, 0x07, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x01, 0xC0, 0x03, 0x80,
0x01, 0xC0, 0x03, 0x80, 0x01, 0xC0, 0x03, 0x80, 0x01, 0xC0, 0x03, 0x80, 0x01, 0xC0, 0x03, 0x80,
0x01, 0xC0, 0x03, 0x80, 0x01, 0xC0, 0x03, 0x80, 0x07, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xE0,
0x07, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00,
0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00,
0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00, 0x00, 0x1C, 0x38, 0x00
};
const unsigned char PROGMEM continuity [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1F, 0xF8, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0xC0, 0x0F, 0xFF, 0xFF, 0xF0,
0x1F, 0xC0, 0x03, 0xF8, 0x7F, 0x00, 0x00, 0xFE, 0xFC, 0x00, 0x00, 0x3F, 0xF8, 0x07, 0xE0, 0x1F,
0xF0, 0x3F, 0xFC, 0x0F, 0x00, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xFF, 0x80, 0x03, 0xF0, 0x0F, 0xC0,
0x07, 0xC0, 0x03, 0xE0, 0x03, 0x80, 0x01, 0xC0, 0x01, 0x0F, 0xF0, 0x80, 0x00, 0x1F, 0xF8, 0x00,
0x00, 0x3F, 0xFC, 0x00, 0x00, 0x3C, 0x3C, 0x00, 0x00, 0x38, 0x1C, 0x00, 0x00, 0x01, 0x80, 0x00,
0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char PROGMEM battery [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xF0, 0x40, 0x00, 0x00, 0x10, 0x47, 0x3C, 0xE0, 0x18,
0x47, 0xBD, 0xE0, 0x18, 0x45, 0xA5, 0xA0, 0x1E, 0x45, 0xA5, 0xA0, 0x1A, 0x45, 0xA5, 0xA0, 0x1A,
0x45, 0xA5, 0xA0, 0x1A, 0x45, 0xA5, 0xA0, 0x1A, 0x45, 0xA5, 0xA0, 0x1E, 0x47, 0xBD, 0xE0, 0x18,
0x47, 0x3C, 0xE0, 0x18, 0x40, 0x00, 0x00, 0x10, 0x3F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char PROGMEM ppwwmm [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0xFF, 0xBE, 0x00, 0x3F, 0xE0, 0x1F, 0x00, 0x02, 0x21, 0xE3, 0x00, 0x33, 0x30, 0x31, 0x00,
0x02, 0x20, 0x73, 0x00, 0x23, 0x18, 0x33, 0x80, 0x02, 0x3C, 0x71, 0x80, 0x66, 0x98, 0x67, 0x80,
0x02, 0x3E, 0x31, 0xBE, 0x66, 0x9C, 0x45, 0x80, 0x02, 0x3E, 0x39, 0xFF, 0xC7, 0xDC, 0xE9, 0x80,
0x02, 0x3E, 0x38, 0xE1, 0xCF, 0xF7, 0x89, 0x80, 0x02, 0x30, 0x7C, 0xE1, 0xCF, 0x23, 0x91, 0x80,
0x02, 0x20, 0xEC, 0xD1, 0x8E, 0x33, 0x31, 0x80, 0x02, 0x60, 0xE4, 0x40, 0x9E, 0x33, 0x31, 0x80,
0x02, 0x3F, 0xC6, 0x4C, 0x9E, 0x39, 0x71, 0x80, 0x02, 0x3F, 0x86, 0x4C, 0xBA, 0x3F, 0xF1, 0x80,
0x02, 0x30, 0x02, 0x5E, 0xBA, 0x3F, 0xF1, 0x80, 0x02, 0x70, 0x03, 0x5E, 0xB2, 0x37, 0xF1, 0x80,
0x03, 0xB0, 0x03, 0x7E, 0xF2, 0x33, 0x91, 0x80, 0x03, 0xF0, 0x01, 0xFB, 0xF3, 0xF0, 0x1F, 0x80,
0x00, 0xE0, 0x00, 0x70, 0xC0, 0xE0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char PROGMEM ime [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0x00, 0x3F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF8, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xE0, 0xFF, 0xF9, 0xFF, 0x00, 0xFF, 0xFD, 0xFF, 0xFC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x7E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0xE7, 0xF9, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x1F, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0xFF, 0xE0, 0x3F, 0xC7, 0xFF, 0xEF, 0xDF, 0x80, 0x0F, 0x80, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0x3F, 0xC0, 0x1F, 0x83, 0xE7, 0xC3, 0x0F, 0x00, 0x07, 0x80, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0x1F, 0x80, 0x0F, 0x03, 0x83, 0xC3, 0x06, 0x00, 0x07, 0x80, 0x00, 0x00,
0x00, 0x00, 0x03, 0x8E, 0x1F, 0x9C, 0x07, 0x03, 0x83, 0x83, 0x8E, 0x00, 0x03, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0x8F, 0x0F, 0x9C, 0x07, 0x01, 0x83, 0x83, 0x8E, 0x0F, 0x83, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0x9F, 0x87, 0x3C, 0x07, 0x00, 0x03, 0x87, 0x9C, 0x1F, 0xC3, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0x9F, 0x87, 0x1C, 0x06, 0x00, 0x03, 0x07, 0x3C, 0x1F, 0xC3, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xDF, 0x87, 0x00, 0x02, 0x0C, 0x03, 0x06, 0x3E, 0x1F, 0xC1, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xCF, 0x82, 0x00, 0x02, 0x0E, 0x03, 0x00, 0x3E, 0x1F, 0xC1, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xCF, 0x82, 0x1C, 0x06, 0x0E, 0x03, 0x06, 0x1E, 0x1F, 0xC3, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x82, 0x3C, 0x06, 0x0E, 0x06, 0x07, 0x0E, 0x0F, 0x83, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0x00, 0x1C, 0x06, 0x0E, 0x06, 0x07, 0x8F, 0x07, 0x03, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0x04, 0x1C, 0x0E, 0x0E, 0x07, 0x03, 0x8F, 0x80, 0x07, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0x0E, 0x1C, 0x0E, 0x0E, 0x07, 0x03, 0x0F, 0x80, 0x0F, 0x80, 0x00, 0x00,
0x00, 0x00, 0x01, 0xC0, 0x1E, 0x18, 0x1E, 0x1E, 0x0F, 0x83, 0x0F, 0xE0, 0x3F, 0x80, 0x00, 0x00,
0x00, 0x00, 0x01, 0xE0, 0x3F, 0xFF, 0xFF, 0xFF, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xF8, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFB, 0xFF, 0xF7, 0xFF, 0xFC, 0xFF, 0xFC, 0x7F, 0xE0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


int ms=300;
int raw= 0;
float Vin= 0;
float Vout= 0;
float R1= 0;
float R2= 2000;
int val = 0;
float buffer= 0;
float vin2 = 0;

void setup(){                 
  pinMode(5,INPUT_PULLUP); // button
  pinMode(4 ,INPUT_PULLUP); // button
  pinMode(3,INPUT_PULLUP); // button
  pinMode(13,OUTPUT);
  attachInterrupt(1, selector, FALLING);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   // initializing the library
  display.clearDisplay(); // clear off the display
  display.drawBitmap(0, 0,  ime, 128, 32, 1);
  display.display();
  delay(700);
  display.clearDisplay();
  display.display();
           }

int mode=0;
int average=0;
void loop()

{

 // Voltmeter Test
 
 if(mode==0) 
  {
    val = analogRead(A3); 
    vin2 = (val*5.0)/1023; 
    display.clearDisplay(); 
    display.setFont();
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("VOLTMETER");
    display.setFont(&FreeSans9pt7b);
    display.setCursor(0,24);
    display.print(vin2+0.1); // because of marginal error we add 0.1
    display.setCursor(50,24);
    display.print("V");
    display.display();
    delay(500);
  }


  // Resistance Test
  
  if(mode==1)
  {
   display.clearDisplay(); 
   display.setFont();
   display.setCursor(0,0);
   display.print("RESISTANCE");
   display.drawBitmap(96, 0,  resistance, 32, 32, 1);
   raw= analogRead(A2);
   Vin=readVcc();
   buffer= raw * Vin;
   Vout= ((buffer)/1024.0);
   buffer= (Vin/Vout) -1;
   R1= R2 * buffer;
   display.setFont(&FreeSans12pt7b);
   display.setCursor(0,28);
   if(R1<70000)
   display.print(R1);
   if(R1>70000)
   display.print("empty");
   display.display();
   delay(ms);
   }

 // Voltage Drop Test 
  
  if(mode==2) 
  {
   display.clearDisplay();
   display.drawBitmap(96, 0,  led, 32, 32, 1);
   display.setFont();
   display.setCursor(0,0);
   display.print("VOLTAGE DROP");
   raw= analogRead(A2);
   Vin=readVcc();
   buffer= raw * Vin;
   Vout= (buffer)/1024.0;
   display.setFont(&FreeSans12pt7b);
   display.setCursor(0,28);
   if(Vout==0)
   {display.print("0");
   } else{
   display.print(Vin-Vout);
   }
    display.display();
     delay(ms);
  }

   // Analog Test
   
  if(mode==3) 
  {
  display.clearDisplay();
  display.setFont();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("ANALOG");
  display.setCursor(95,0); 
  int sensorRead=analogRead(A0);
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0,24);
  display.print(sensorRead); 
  display.display();
  delay(ms);
 }

// Continuity Test

   if(mode==4)
  {
   display.clearDisplay();
   display.drawBitmap(96, 0,  continuity, 32, 32, 1);
   display.setFont();
   display.setCursor(0,0);
   display.print("CONTINUITY TEST");
   display.setFont(&FreeSans12pt7b);
   display.setCursor(0,28);
   raw = analogRead(A2);
   Vin = readVcc();
   buffer = raw * Vin;
   Vout = (buffer)/1024.0;
   float rez=Vin-Vout;
    if(rez<1)
      {
         tone(6,2250); // for the buzzer
         display.print("Yes");
         digitalWrite(13,1);
      }
     if(rez>1)
     {
     noTone(6);
     digitalWrite(13,0);
     display.print("No");
     }
     display.display();
    }
    
  // Battery 
  
 if(mode==5)
  {
  display.clearDisplay();
  display.drawBitmap(96, 0,  battery, 32, 32, 1);
  display.setFont();
  display.setCursor(0,0);
  display.print("BATERRY");
  display.setFont(&FreeSans12pt7b);
  display.setCursor(0,28);
  float volt2=readVcc();
  display.print(volt2);
  display.setCursor(55,28);
  display.print("V");
  display.display();
  delay(ms);
  }

  // PWM Test
 int pulse=125;
 if(mode==6)
 {
   if(digitalRead(4)==0)
  { if(pulse<255)
  {
    tone(6,1800,10);
    pulse=pulse+2; } 
  }

    if(digitalRead(5)==0)
  { if(pulse>1)
  {
    tone(6,1400,10);
    pulse=pulse-2; } 
     
  }
  int line=0;
  analogWrite(9,pulse);
  display.clearDisplay();
  display.drawBitmap(72, 1,  ppwwmm, 58, 30, 1);
  display.setFont();
  display.setCursor(0,0);
  display.print("PULSE WIDTH");
  display.setFont(&FreeSans12pt7b);
  display.setCursor(0,28);
  display.print(pulse);
  line = map(pulse,0,255,0,128);   
  display.drawLine(0,31,line,31,1); 
  display.display();
  }   


}







void selector()
{

 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 220) 
 {
   mode++;
   tone(6,2250,50);
   if(mode>6)
   mode=0;
 }
 last_interrupt_time = interrupt_time;
    

 
  }
long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return (result/1000); // Vcc in volts
}
