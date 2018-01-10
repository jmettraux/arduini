
#include <ESP8266WiFi.h>
#include ".wifi.h"
#include <ESP8266HTTPClient.h>
#include <DHT.h> // /Applications/Arduino.app/Contents/Java/libraries/


//WiFiServer server(80);

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define SERVER "http://10.0.1.6:8080/"

#define DEEP_SLEEP_TIME 9 // minutes

DHT dht(D3, DHTTYPE);


void setup() {

  //pinMode(D3, INPUT);

  // Kick in serial

  Serial.begin(115200);
  Serial.setTimeout(2000);

  while ( ! Serial) {}

  dht.begin();

  Serial.print("\nawake...");

  // Connect to WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to "); Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  for (int i = 0; i < 21; i++) {
    delay(500);
    Serial.print(".");
    if (WiFi.status() == WL_CONNECTED) break;
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println();
    Serial.print(WiFi.macAddress());
    Serial.print(" connected as ");
    Serial.println(WiFi.localIP());
  }

  // well, GET data

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float i = dht.computeHeatIndex(t, h, false);
  //Serial.print(" -- ");
  //Serial.print(h); Serial.print(" % / ");
  //Serial.print(t); Serial.print(" C / ");
  //Serial.print(i); Serial.print(" C");
  //Serial.println();

  String uri = SERVER;
  uri += "?h="; uri += h;
  uri += "&t="; uri += t;
  uri += "&i="; uri += i;
  uri += "&m="; uri += WiFi.macAddress();

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(uri);

    for (int i = 0; i < 3; i++) {

      int httpCode = http.GET();

      Serial.print(uri);
      Serial.print(" returned ");
      Serial.println(httpCode);

      if (httpCode == 200) break;

      delay(500);
    }
  }

  // Sleep deep

  ESP.deepSleep(DEEP_SLEEP_TIME * 60 * 1e6);
}

void loop() {
}

