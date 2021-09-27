# 1 "d:\\OneDrive\\Dondamad\\College_TSU\\1_2564\\MicroController_Prog\\toggle_led\\toggle_led.ino"
const int BUTTON_ON_PIN = 2;
const int BUTTON_OFF_PIN = 3;
const int LED_PIN = 13;
const int Buzzer_Pin = 12;

int BUTTON_ON_STATE;
int BUTTON_OFF_STATE;
int Status = 0;
void setup(){
    pinMode(BUTTON_ON_PIN, 0x2);
    pinMode(BUTTON_OFF_PIN, 0x2);
    pinMode(LED_PIN, 0x1);
   pinMode(Buzzer_Pin, 0x1);
}

void loop(){
    BUTTON_ON_STATE = digitalRead(BUTTON_ON_PIN);
    BUTTON_OFF_STATE = digitalRead(BUTTON_OFF_PIN);


   if (Status == 0 && BUTTON_ON_STATE == 0x0)
    {
        digitalWrite(LED_PIN, 0x1);
       buzzer();
       Status = 1;
    }
  if (Status == 1 && BUTTON_OFF_STATE == 0x0)
    {
        digitalWrite(LED_PIN, 0x0);
     buzzer();
     Status = 0;
    }

}

void buzzer(){
   //digitalWrite(Buzzer_Pin, HIGH);
  tone(Buzzer_Pin, 1200);
   delay(10);
  noTone(Buzzer_Pin);
   //digitalWrite(Buzzer_Pin, LOW);
}
