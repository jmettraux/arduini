
#include <ESP8266WiFi.h>
#include ".wifi.h"
#include <DHT.h> // /Applications/Arduino.app/Contents/Java/libraries/


WiFiServer server(80);

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(D3, DHTTYPE);


void setup() {

  //pinMode(D3, INPUT);

  // Kick in serial
  Serial.begin(115200);
  dht.begin();

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {

  // Check if a client has connected

  WiFiClient client = server.available();
  if ( ! client) return;

  // Wait until the client sends some data

  Serial.println("new client");
  while ( ! client.available()) delay(1);

  // Read the first line of the request

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

//  if (request.indexOf("/FORWARD") != -1) motorForward();
//  else if (request.indexOf("/BACKWARD") != -1) motorBackward();
//  else if (request.indexOf("/LEFT") != -1) motorLeft();
//  else if (request.indexOf("/RIGHT") != -1) motorRight();

  // read sensor

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("-- ");
  Serial.print(h); Serial.print(" %  / ");
  Serial.print(t); Serial.println(" C");

  // Return the response

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println(""); //  do not forget this one
  client.print("{");
  client.print("\"humidity\":"); client.print(h); client.print(",");
  client.print("\"temperature\":"); client.print(t);
  client.print("}");

  //delay(1);
//  Serial.println("Client disconnected");
//  Serial.println("");
}

