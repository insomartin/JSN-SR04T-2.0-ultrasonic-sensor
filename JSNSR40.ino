/*
  Software serial multple serial test

  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.

  The circuit:
   RX is digital pin 2 (connect to TX of other device)
   TX is digital pin 3 (connect to RX of other device)

  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

  Not all pins on the Leonardo support change interrupts,
  so only the following can be used for RX:
  8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

  created back in the mists of time
  modified 25 May 2012
  by Tom Igoe
  based on Mikal Hart's example

  This example code is in the public domain.

*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
byte ultrasonic[4];

void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);
}

void loop() // run over and over
{
  unsigned int  distance;
  mySerial.write(0x55);
  int timeout = 1000;
  byte count = 0;
  while (1) {
    if (mySerial.available()) {
      char inChar = (char)mySerial.read();
      ultrasonic[count] = inChar;
      count++;
    }
    delay(1);
    timeout--;
    if (timeout == 0) {
      break;
    }
  }
  distance = 256 * ultrasonic[1];
  distance = distance + ultrasonic[2];
  Serial.println(distance);

}
