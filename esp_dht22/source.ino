
#include <ESP8266WiFi.h>
#include ".wifi.h"
#include <ESP8266HTTPClient.h>
#include <DHT.h> // /Applications/Arduino.app/Contents/Java/libraries/


//WiFiServer server(80);

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define SERVER "http://10.0.1.6:8080/"

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

  // POST data

  char uri[512];
  snprintf(uri, 512, "%s/?h=%.2f&t=%.2f&i=%.2f", SERVER, h, t, i);
  Serial.println(uri);

  HTTPClient http;
  http.begin(SERVER);
  //http.addHeader("Content-Type", "application/json");

  int httpCode = http.GET();
//  client.print("{");
//  client.print("\"humidity\":"); client.print(h); client.print(",");
//  client.print("\"temperature\":"); client.print(t); client.print(",");
//  client.print("\"heatIndex\":"); client.print(i); client.print(",");
//  client.print("\"mac\":\""); client.print(WiFi.macAddress()); client.print("\"");
//  client.print("}");

  // Sleep deep

  ESP.deepSleep(5e6); // five seconds

//  // Start the server
//
//  server.begin();
//  Serial.println("Server started");
//
//  // Print the IP address
//
//  Serial.println();
//  Serial.println(WiFi.macAddress());
//  Serial.print("http://");
//  Serial.print(WiFi.localIP());
//  Serial.println("/");
}

void loop() {

//  // Check if a client has connected
//
//  WiFiClient client = server.available();
//  if ( ! client) return;
//
//  // Wait until the client sends some data
//
//  //Serial.println("new client");
//  while ( ! client.available()) delay(1);
//
//  // Display request
//
//  String request = client.readStringUntil('\r');
//
//  // https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/WiFiClient.h
//
//  Serial.print(request); Serial.print(" from ");
//  Serial.print(client.remoteIP()); Serial.print(":");
//  Serial.print(client.remotePort());
//
//  client.flush();
//
//  // Match the request
//
////  if (request.indexOf("/FORWARD") != -1) motorForward();
////  else if (request.indexOf("/BACKWARD") != -1) motorBackward();
////  else if (request.indexOf("/LEFT") != -1) motorLeft();
////  else if (request.indexOf("/RIGHT") != -1) motorRight();
//
//  // read sensor
//
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  float i = dht.computeHeatIndex(t, h, false);
//  Serial.print(" -- ");
//  Serial.print(h); Serial.print(" % / ");
//  Serial.print(t); Serial.print(" C / ");
//  Serial.print(i); Serial.print(" C");
//  Serial.println();
//
//  // Return the response
//
//  client.println("HTTP/1.1 200 OK");
//  client.println("Content-Type: application/json");
//  client.println(""); //  do not forget this one
//  client.print("{");
//  client.print("\"humidity\":"); client.print(h); client.print(",");
//  client.print("\"temperature\":"); client.print(t); client.print(",");
//  client.print("\"heatIndex\":"); client.print(i); client.print(",");
//  client.print("\"mac\":\""); client.print(WiFi.macAddress()); client.print("\"");
//  client.print("}");
}

