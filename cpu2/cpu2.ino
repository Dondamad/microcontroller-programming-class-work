char bb[10];
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup()
{
  lcd.begin(20, 4);
  // lcd.print("test");
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; Serial.available() ; i++)
  {
    bb[i] = Serial.read();
  }
  Serial.println(bb);

  lcd.print(atof(bb));
  
  delay(1000);
  lcd.clear();
}