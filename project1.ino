#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include "index.h";
#define LED 2
#define ServoPin 14
const char *ssid = "PRAKASHREDDY";
const char *password = "prakash123";
Servo myservo;
ESP8266WebServer server(80);
void handleServo(){
  String POS = server.arg("servoPOS");
  int pos = POS.toInt();
  myservo.write(pos);
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  digitalWrite(LED,!(digitalRead(LED)));
  server.send(200, "text/plane","");
}
void handleRoot() {
 String s = MAIN_page;
 server.send(200, "text/html", s);
}
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  pinMode(LED,OUTPUT);
  myservo.attach(ServoPin);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/",handleRoot);
  server.on("/setPOS",handleServo);
  server.begin();  
}
void loop() {
 server.handleClient();
}
