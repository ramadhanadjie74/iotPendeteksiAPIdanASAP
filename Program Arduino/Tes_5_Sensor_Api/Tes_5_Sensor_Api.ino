byte api1 = 5;
byte api2 = 6;
byte api3 = 7;
byte api4 = 8;
byte api5 = 9;

int nilaiApi1;
int nilaiApi2;
int nilaiApi3;
int nilaiApi4;
int nilaiApi5;

void setup() {
  Serial.begin(9600);
  pinMode(api1, INPUT);
  pinMode(api2, INPUT);
  pinMode(api3, INPUT);
  pinMode(api4, INPUT);
  pinMode(api5, INPUT);
}

void loop() {
  nilaiApi1 = digitalRead(api1);
  nilaiApi2 = digitalRead(api2);
  nilaiApi3 = digitalRead(api3);
  nilaiApi4 = digitalRead(api4);
  nilaiApi5 = digitalRead(api5);

  Serial.print(nilaiApi1);
  Serial.print(nilaiApi2);
  Serial.print(nilaiApi3);
  Serial.print(nilaiApi4);
  Serial.println(nilaiApi5);

}
