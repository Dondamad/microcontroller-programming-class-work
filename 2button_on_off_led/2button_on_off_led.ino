const int BUTTON_ON_PIN = 2;
const int BUTTON_OFF_PIN = 3;
const int LED_PIN = 9;
const int Buzzer_Pin = 12;

int BUTTON_ON_STATE;
int BUTTON_OFF_STATE;
int Status = 0; //led off
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

	if (!Status && BUTTON_ON_STATE == LOW) // if led off and press on button
	{
		digitalWrite(LED_PIN, HIGH);
		buzzer(1);
		Status = 1;
	}
	if (Status == 1 && BUTTON_OFF_STATE == LOW) // if led on and press off button
	{
		digitalWrite(LED_PIN, LOW);
		buzzer(1);
		Status = 0;
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
