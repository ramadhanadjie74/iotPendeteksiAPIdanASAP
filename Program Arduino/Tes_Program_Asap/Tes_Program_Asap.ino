#include <MQ2.h>
int pin = A0;
int smoke;
MQ2 mq2(pin);

void setup() {
  Serial.begin(9600);
  mq2.begin();
}

void loop() {
  float* values = mq2.read(true);
  smoke = mq2.readSmoke();
  Serial.println(smoke);
}
