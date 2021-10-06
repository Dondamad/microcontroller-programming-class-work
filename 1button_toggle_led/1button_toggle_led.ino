const int BUTTON_PIN = 2;
const int LED_PIN = 9;
const int Buzzer_Pin = 12;

int BUTTON_STATE;
int oldBUTTON_STATE;
bool LED_STATE = 0; //led off
void setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    pinMode(Buzzer_Pin, OUTPUT);
}

void loop()
{
    oldBUTTON_STATE = BUTTON_STATE;
    BUTTON_STATE = digitalRead(BUTTON_PIN);

    if (oldBUTTON_STATE == HIGH && BUTTON_STATE == LOW)
    {
        if (LED_STATE == LOW){
            LED_STATE = HIGH;
            digitalWrite(LED_PIN, LED_STATE);
            buzzer(1);
        }else{
            LED_STATE = LOW;
            digitalWrite(LED_PIN, LED_STATE);
            buzzer(2);
        }
    }
}

void buzzer(int count)
{
    for (int i = 0; i < count; i++)
    {
        digitalWrite(Buzzer_Pin, HIGH);
        delay(100);
        digitalWrite(Buzzer_Pin, LOW);
        delay(200);
    }
}
