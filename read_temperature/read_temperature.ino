#include <OneWire.h>
#include <TimerOne.h>

int aa;
float  temperature = 0;

#define SEVEN_SEGMENT_2D_DELAY 10
int pin_number[8] = {12, 11, 5, 8, 7, 13, 2, 6};
int pin_digit[2]  = {10, 9};
int seven_segment_dict[10] = {
  [0] = 0x3F,
  [1] = 0x06,
  [2] = 0x5B,
  [3] = 0x4F,
  [4] = 0x66,
  [5] = 0x6D,
  [6] = 0x7D,
  [7] = 0x07,
  [8] = 0x7F,
  [9] = 0x6F,
};

int pin_buzzer = 3;
bool buzzer_state = false;

OneWire ds(4);
byte data[9];
int temp;

float temp1;

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(500000);
  Timer1.attachInterrupt(temperature_read);
  
  pinMode(pin_number[0], OUTPUT);
  pinMode(pin_number[1], OUTPUT);
  pinMode(pin_number[2], OUTPUT);
  pinMode(pin_number[3], OUTPUT);
  pinMode(pin_number[4], OUTPUT);
  pinMode(pin_number[5], OUTPUT);
  pinMode(pin_number[6], OUTPUT);
  pinMode(pin_number[7], OUTPUT);
  
  pinMode(pin_digit[0], OUTPUT);
  pinMode(pin_digit[1], OUTPUT);

  pinMode(pin_buzzer, OUTPUT);
}

void loop()
{
  seven_segment_ca_2d_print(temperature);
}

void seven_segment_ca_2d_print(int number) {
  seven_segment_2d_write(seven_segment_dict[number % 10], 1, true);
  delay(SEVEN_SEGMENT_2D_DELAY);
  number /= 10;
  seven_segment_2d_write(seven_segment_dict[number % 10], 0, true);
  delay(SEVEN_SEGMENT_2D_DELAY);
}

void seven_segment_2d_write(int number_mask, int number_digit, bool common_cathode) {
  if (!common_cathode) {
    number_mask = ~number_mask;
  }

  digitalWrite(pin_digit[0], common_cathode);
  digitalWrite(pin_digit[1], common_cathode);

  digitalWrite(pin_number[0], number_mask & 1);
  digitalWrite(pin_number[1], number_mask & 2);
  digitalWrite(pin_number[2], number_mask & 4);
  digitalWrite(pin_number[3], number_mask & 8);
  digitalWrite(pin_number[4], number_mask & 16);
  digitalWrite(pin_number[5], number_mask & 32);
  digitalWrite(pin_number[6], number_mask & 64);
  digitalWrite(pin_number[7], number_mask & 128);

  digitalWrite(pin_digit[number_digit], !common_cathode);
}

void temperature_read() {
  temperature = read_tem() + 0.5; // round up
  if (temperature >= 30) {
     buzzer_set(true);
  }
  else {
    buzzer_set(false);
  }
}
float read_tem()
{
  ds.reset();     // If Device ACK on Reset
  ds.write(0xCC); // Skip ROM Command
  ds.write(0x44); // Start Conversion Temp
  ds.reset();     // Re-Start New Command
  ds.write(0xCC); // Skip ROM Command
  ds.write(0xBE); // Read Scratchpad RAM(Temperature Data)

  for (int i = 0; i < 9; i++) // 9 Byte Read Scratchpad RAM
  {
    data[i] = ds.read();
  }

  temp = (data[1] << 8) + data[0];
  return temp * 0.0625;
}

void buzzer_set(bool state) {
  if (buzzer_state == state) {
    return;
  }
  digitalWrite(pin_buzzer, state);
  buzzer_state = state;
}
