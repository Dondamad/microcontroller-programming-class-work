/*
 * Author: Sittidach Kaeorawang, 622021129
 * 622021129@tsu.ac.th
 * 
 * Editor: Romadon Damad, 622021126
 */

#include <TimerOne.h>

float   brightness = 0; // 0 ... 99


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

void setup()
{
  Timer1.initialize(500000);
  Timer1.attachInterrupt(brightness_read);
  
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
  seven_segment_ca_2d_print(brightness);
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

void brightness_read() {
  brightness = analogRead(A0) * (99/1024.0) + 0.5; // round up
  if (brightness >= 30) {
     buzzer_set(true);
  }
  else {
    buzzer_set(false);
  }
}

void buzzer_set(bool state) {
  if (buzzer_state == state) {
    return;
  }
  digitalWrite(pin_buzzer, state);
  buzzer_state = state;
}
