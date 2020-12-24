/*
  https://github.com/bigjohnson/powerlinecheck

  Cont time from last power line fail.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#define SECONDO 1010 // durata di un secondo in millisecondi

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned long oldmillis;
unsigned long newmillis;
unsigned char secondi = 0;
unsigned char minuti = 0;
unsigned char ore = 0;
unsigned long giorni = 0;
unsigned int limite = SECONDO;
bool scatto = false;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("      d  h  m  s");
  //         9999999
  oldmillis = millis();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(13, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() % 1000);
  //indenta(millis() % 1000, 3);
  //if ( millis() % 1000 == 0 ) {
  if ( giorni < 9999999 || ore < 23 || minuti < 59 || secondi < 59 ) {
    newmillis = millis();
    if (newmillis < oldmillis && scatto == false) {
      oldmillis = newmillis;
      limite = 295;
      scatto = true;
    }
    //if ( millis() % 1000 == 0 ) {
    if ((oldmillis + limite) <= newmillis) {
      //    oldmillis = newmillis;
      oldmillis = oldmillis + 1000;
      secondi++;
      scatto = false;
      limite = SECONDO;
      if (secondi == 60) {
        secondi = 0 ;
        minuti++;
        if ( minuti == 60) {
          minuti = 0;
          ore++;
          if (ore == 24) {
            ore = 0;
            giorni++;
            if ( giorni == 1000) {
              giorni = 0;
            }
            lcd.setCursor(0, 1);
            //          if ( giorni < 100 ) {
            //            lcd.print(' ');
            //          }
            //          if ( giorni < 10 ) {
            //            lcd.print(' ');
            //          }
            //          lcd.print(giorni);
            indenta(giorni, 7);
          }
          lcd.setCursor(8, 1);
          //        if ( ore < 10 ) {
          //          lcd.print(' ');
          //        }
          //        lcd.print(ore);
          indenta(ore, 2);
        }
        lcd.setCursor(11, 1);
        //      if ( minuti < 10 ) {
        //        lcd.print(' ');
        //      }
        //      lcd.print(minuti);
        indenta(minuti, 2);
      }
      lcd.setCursor(14, 1);
      //    if ( secondi < 10 ) {
      //      lcd.print(' ');
      //    }
      //    lcd.print(secondi);
      indenta(secondi, 2);
    }
  }
}

void indenta(int cifra, int indenta) {
  indenta = indenta - 1;
  unsigned long controllo = 10;
  if ( indenta > 0 ) {
    for ( int fai = 0; fai < indenta; fai++) {
      if ( cifra < controllo ) {
        lcd.print(' ');
      }
      controllo = controllo * 10;
    }
  }
  lcd.print(cifra);
}
