#include "conf_usb.h"

const int received = 7;
const int sended = 6;
unsigned int stateSended = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(received, INPUT);
  pinMode(sended, OUTPUT);
}

void loop() {
  const int stateReceived = digitalRead(received);

  Serial.print("\n");
  Serial.print("sended: ");
  Serial.print(stateSended);
  Serial.print("received: ");
  Serial.print(stateReceived);
  Serial.print("\n");

  stateSended -= 1;
}
