#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

const int SAMPLES= 10;

#define CLIENT "ESP RFID"        
#define TYPE "ESP32"              

RTC_DATA_ATTR char name[15] = CLIENT;

StaticJsonDocument<500> doc;

const int LM35 = 13; 
float reading; 

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverName = "http://localhost:3000/users";

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to: ");
  Serial.print(ssid);
  Serial.print(" with password: ");
  Serial.println(password);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sensorTemp();
  delay(10000);
  Serial.println("Posting...");
  postData();
  serializeJsonPretty(doc, Serial);
  Serial.println("Done.");
}

float sensorTemp() {
  reading = (float(analogRead(LM35))*5/(1023))/0.01;

  doc["temperature"] = reading;

  return reading;
}

void postData() {     
      if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");

      String json;
      serializeJson(doc["temperature"], json);
      Serial.println("Dados armazenados para o POST");
      Serial.println(json);
      int httpResponseCode = http.POST(json);
      Serial.println("POSTED");
      Serial.println(httpResponseCode);
      }
}
