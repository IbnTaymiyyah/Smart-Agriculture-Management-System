#include <ESP8266WiFi.h>
#include <DHT.h>

#define WIFI_SSID "farmer123" 
#define WIFI_PASSWORD "password123"

#define DHTPIN 2    
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();  

  WiFiClient client;
  if(client.connect("api.farmcloud.com",80)) {
   String data = "temperature="+String(t)+"&humidity="+String(h);
   client.print("POST /sensor HTTP/1.1\n");
   client.print("Host: api.farmcloud.com\n"); 
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(data.length());
   client.print("\n");
   client.print("\n");
   client.print(data);
  }
  delay(10000);
}

/*This code is for an ESP8266 microcontroller board, commonly used for IoT (Internet of Things) projects. It's designed to read temperature and humidity data from a DHT11 sensor and then send this data to a server hosted at api.farmcloud.com.*/