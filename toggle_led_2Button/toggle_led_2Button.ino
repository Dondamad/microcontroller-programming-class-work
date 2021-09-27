const int BUTTON_ON_PIN = 2;
const int BUTTON_OFF_PIN = 3;
const int LED_PIN = 13;
const int Buzzer_Pin = 12;

int BUTTON_ON_STATE;		
int BUTTON_OFF_STATE;
int Status = 0;		//led off
void setup()
{
	pinMode(BUTTON_ON_PIN, INPUT_PULLUP);
	pinMode(BUTTON_OFF_PIN, INPUT_PULLUP);
	pinMode(LED_PIN, OUTPUT);
	pinMode(Buzzer_Pin, OUTPUT);

}

void loop()
{
	BUTTON_ON_STATE = digitalRead(BUTTON_ON_PIN);
	BUTTON_OFF_STATE = digitalRead(BUTTON_OFF_PIN);

	if (Status == 0 && BUTTON_ON_STATE == LOW)		// if led off and press on button
	{
		digitalWrite(LED_PIN, HIGH);
		buzzer();
		Status = 1;
	}
	if (Status == 1 && BUTTON_OFF_STATE == LOW)		// if led on and press off button
	{
		digitalWrite(LED_PIN, LOW);
		buzzer();
		Status = 0;
	}
}

void buzzer()
{
	tone(Buzzer_Pin, 1200);
	delay(10);
	noTone(Buzzer_Pin);
}