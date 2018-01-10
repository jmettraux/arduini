
#include <ESP8266WiFi.h>
#include ".wifi.h"
#include <ESP8266HTTPClient.h>
#include <DHT.h> // /Applications/Arduino.app/Contents/Java/libraries/


//WiFiServer server(80);

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define SERVER "http://10.0.1.6:8080/"

#define DEEP_SLEEP_TIME 60 // seconds

DHT dht(D3, DHTTYPE);


void setup() {

  //pinMode(D3, INPUT);

  // Kick in serial

  Serial.begin(115200);
  Serial.setTimeout(2000);

  while ( ! Serial) {}

  dht.begin();
  delay(500);

  Serial.print("\nawake...");

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float i = dht.computeHeatIndex(t, h, false);
  Serial.print(" -- ");
  Serial.print(h); Serial.print(" % / ");
  Serial.print(t); Serial.print(" C / ");
  Serial.print(i); Serial.print(" C");
  Serial.println();

  // Connect to WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to "); Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    // TODO limit attempts
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print(WiFi.macAddress());
  Serial.print(" connected as ");
  Serial.println(WiFi.localIP());

  // well, GET data

  HTTPClient http;

  String uri = SERVER;
  uri += "?h="; uri += h;
  uri += "&t="; uri += t;
  uri += "&i="; uri += i;
  uri += "&m="; uri += WiFi.macAddress();
  Serial.println(uri);

  http.begin(uri);
  //http.addHeader("Content-Type", "application/json");

  int httpCode = http.GET();

  // Sleep deep

  ESP.deepSleep(DEEP_SLEEP_TIME * 1e6);
}

void loop() {
}

