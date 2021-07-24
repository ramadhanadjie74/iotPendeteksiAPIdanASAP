//ETHERNET
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);
EthernetClient client;
char server[] = "kriot.in";

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10 * 1000;

//SENSOR API
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

//SENSOR ASAP
int mq2 = A0;
int nilaiAsap;

String statusApi;
String statusAsap;
String lokasi = "Sumedang";

int countApi;
int countAsap;

int buzzer = 2;

void setup() {
  Serial.begin(9600);

  ethernet();

  //SENSOR API
  pinMode(api1, INPUT);
  pinMode(api2, INPUT);
  pinMode(api3, INPUT);
  pinMode(api4, INPUT);
  pinMode(api5, INPUT);

  //BUZZER
  pinMode(buzzer, OUTPUT);
}

void loop() {
  //SENSOR API
  nilaiApi1 = digitalRead(api1);
  nilaiApi2 = digitalRead(api2);
  nilaiApi3 = digitalRead(api3);
  nilaiApi4 = digitalRead(api4);
  nilaiApi5 = digitalRead(api5);
  //  Serial.print(nilaiApi1);
  //  Serial.print(nilaiApi2);
  //  Serial.print(nilaiApi3);
  //  Serial.print(nilaiApi4);
  //  Serial.println(nilaiApi5);

  if (nilaiApi1 == 1 || nilaiApi2 == 1 || nilaiApi3 == 1 || nilaiApi4 == 1 || nilaiApi5 == 1 ) {
    statusApi = "Ada%20Api";
    digitalWrite(buzzer, HIGH);
    countApi++;
    if (countApi == 1) {
      httpRequest1();
    }
  }
  if (nilaiApi1 == 0 & nilaiApi2 == 0 & nilaiApi3 == 0 & nilaiApi4 == 0 & nilaiApi5 == 0 ) {
    statusApi = "Tidak%20Ada%20Api";
    countApi = 0;
  }

  //SENSOR GAS
  nilaiAsap = analogRead(mq2);
  nilaiAsap = map(nilaiAsap, 50, 1023, 0, 2000);
  if (nilaiAsap < 0) {
    nilaiAsap = 0;
  }
  Serial.println(nilaiAsap);
  if (nilaiAsap > 10) {
    statusAsap = "Ada%20Asap";
    digitalWrite(buzzer, HIGH);
    countAsap++;
    if (countAsap == 1) {
      httpRequest2();
    }
  }
  if (nilaiAsap < 10) {
    statusAsap = "Tidak%20Ada%20Asap";
    countAsap = 0;
  }

  if (nilaiApi1 == 0 & nilaiApi2 == 0 & nilaiApi3 == 0 & nilaiApi4 == 0 & nilaiApi5 == 0  & nilaiAsap < 10) {
    digitalWrite(buzzer, LOW);
  }

  //ETHERNET
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest1();
    delay(500);
    httpRequest2();
  }

}

void httpRequest1() {
  client.stop();
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.print("GET /flame/input.php?sensor=Flame%20Sensor&lokasi=");
    client.print(lokasi);
    client.print("&ip=");
    client.print(ip);
    client.print("&status=");
    client.print(statusApi);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    lastConnectionTime = millis();
  } else {

    Serial.println("connection failed");
  }
}

void httpRequest2() {
  client.stop();
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    client.print("GET /flame/input.php?sensor=Sensor%20Asap&lokasi=");
    client.print(lokasi);
    client.print("&ip=");
    client.print(ip);
    client.print("&status=");
    client.print(statusAsap);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
    lastConnectionTime = millis();
  } else {

    Serial.println("connection failed");
  }
}

void ethernet() {
  while (!Serial) {
    ;
  }
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1);
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    Ethernet.begin(mac, ip, myDns);
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
    ip = Ethernet.localIP();
  }
  delay(1000);
}
