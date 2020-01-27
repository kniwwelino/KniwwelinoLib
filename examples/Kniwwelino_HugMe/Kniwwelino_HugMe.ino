#include <Kniwwelino.h>

int value;

void setup() {
  //Initialize the Kniwwelino Board
  Kniwwelino.begin("HugMe", true, true, false); // Wifi=true, Fastboot=true, MQTT Logging=false
  pinMode(A0, INPUT);

  value = 0;
  Kniwwelino.MATRIXdrawIcon("B0000001010000001000101110");
}

void loop() {
  value = map(analogRead(A0), 0, 400, 0, 255);
  Kniwwelino.RGBsetColorEffect(String(Kniwwelino.RGBhue2Hex(value)), RGB_ON, -1);
  if (value < 128) {
    Kniwwelino.MATRIXdrawIcon("B0000001010000000111010001");
  } else if (value < 200) {
    Kniwwelino.MATRIXdrawIcon("B0000001010000001111100000");
  } else {
    Kniwwelino.MATRIXdrawIcon("B0000001010000001000101110");
  }

  Kniwwelino.loop(); // do background stuff...
}
