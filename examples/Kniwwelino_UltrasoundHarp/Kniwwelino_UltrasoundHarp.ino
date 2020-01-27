#include <Kniwwelino.h>
#include <NewPing.h> //https://bitbucket.org/teckel12/arduino-new-ping/

int value;

NewPing hcsr04_D5D5(D5, D5, 200);

// Beschreibe diese Funktion …
void playTone() {
  if (value == 0) {
    Kniwwelino.playTone(D6, 0 /*Silence*/);
  } else if (value <= 10) {
    Kniwwelino.playTone(D6, NOTE_C4);
  } else if (value <= 20) {
    Kniwwelino.playTone(D6, NOTE_D4);
  } else if (value <= 30) {
    Kniwwelino.playTone(D6, NOTE_E4);
  } else if (value <= 40) {
    Kniwwelino.playTone(D6, NOTE_F4);
  } else if (value <= 50) {
    Kniwwelino.playTone(D6, NOTE_G4);
  } else if (value <= 60) {
    Kniwwelino.playTone(D6, NOTE_A4);
  } else if (value <= 70) {
    Kniwwelino.playTone(D6, NOTE_B4);
  }
  Kniwwelino.sleep((unsigned long) 100);
}


void setup() {
  //Initialize the Kniwwelino Board
  Kniwwelino.begin("UltrasoundHarp", true, true, false); // Wifi=true, Fastboot=true, MQTT Logging=false

  pinMode(D6, OUTPUT); //Buzzer against GND

  value = 0;
  Kniwwelino.MATRIXdrawIcon(String("B0000001010000001000101110"));

}

void loop() {
  value = hcsr04_D5D5.ping_cm();
  Kniwwelino.RGBsetColorEffect(String(Kniwwelino.RGBhue2Hex((value * 2))), RGB_ON, -1);
  playTone();

  Kniwwelino.loop(); // do background stuff...
}
