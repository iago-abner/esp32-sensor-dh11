#include <WiFi.h>
#include <MQTT.h>
#include "DHT.h"

#define DHT11PIN 16

DHT dht(DHT11PIN, DHT11);
WiFiClient net;
MQTTClient client;

const char* ssid = "Iago_2.4GHz";
const char* password = "iago82465";

void connect(){
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());

  Serial.print("Connecting to Client..");
  while (!client.connect("client", "user", "pass")) { 
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");
  
  }

void setup() {
  
  Serial.begin(115200);

  dht.begin();
  
  WiFi.begin(ssid, password); 

  client.begin("test.mosquitto.org", net);
  
  connect();
}
  
void loop() {
  
  client.loop();
  delay(100);

  if(!client.connected()){
    connect();
    }
    
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(hum);
  
  client.publish("/iot/temp", String(temp));
  client.publish("/iot/hum", String(hum));
  delay(5000);
}
