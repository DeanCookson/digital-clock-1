
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned long backlightTimer = 0;
volatile boolean lightswitch = false;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);
  pinMode(18, INPUT);
  attachInterrupt(5, backlight, LOW);
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
}

void loop() {
  int deltime = 100;
  tmElements_t tm;
  
  // put your main code here, to run repeatedly:
  if (RTC.read(tm)) {
    lcd.setCursor(4,0);
    print2digits(tm.Hour);
    lcd.print(":");
    print2digits(tm.Minute);
    lcd.print(":");
    print2digits(tm.Second);
    lcd.setCursor(3,1);
    print2digits(tm.Month);
    lcd.print("/");
    print2digits(tm.Day);
    lcd.print("/");
    lcd.print(tmYearToCalendar(tm.Year));
  }
  if (lightswitch)
  {
    backlightTimer = millis();
    lightswitch = false;
  }
  if (backlightTimer > millis()) {
    backlightTimer = 0;
  }
  if ((backlightTimer + 5100) > millis() && ! (backlightTimer == 0))
  {
    digitalWrite(8, HIGH);
  } else
  {
    digitalWrite(8, LOW);
  }
  delay(deltime);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}

void backlight() {
  lightswitch = true;
}
