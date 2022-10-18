#include <wifi.h>
#include <HTTPClient.h>

const int LM35 = A0;
float temperature;

const char *ssid = "";
const char *password = ""; 
const char *server = "http://ip:porta/endpoint" 

void setup(){
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
}

void loop(){
  temperature = (float(analogRead(LM35))*5/(1023))/0.01;
  
  if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    http.begin(client, server);
    http.addHeader("Content-Type", "application/json");

    char *temperature = static_cast<chat *>(malloc(sizeof(char) * 8));

    Serial.print(temperature);
    Serial.println(WiFi.localIP());
    
    int responseCode = http.POST(temperature);
    if (responseCode <= 0){
      Serial.println('Error');
    }

    http.end;
    delete temperature;

    delay(5000);
  }
}