#include <OneWire.h>
OneWire ds(3);
byte data[9];
int temp = 0;
float temp1 = 0.0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  read_tem();
  Serial.println(temp1, 1);
  delay(1000);
}

void read_tem()
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
  temp1 = temp * 0.0625;
}