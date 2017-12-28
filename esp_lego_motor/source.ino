
#include <ESP8266WiFi.h>
#include ".wifi.h"


WiFiServer server(80);


void motorStop() {
  digitalWrite(D5, LOW); digitalWrite(D6, LOW); digitalWrite(D7, LOW);
  digitalWrite(D0, LOW); digitalWrite(D1, LOW); digitalWrite(D2, LOW);
}
void motorForward() {
  digitalWrite(D5, HIGH); digitalWrite(D6, LOW); digitalWrite(D7, HIGH);
  digitalWrite(D0, LOW); digitalWrite(D1, HIGH); digitalWrite(D2, HIGH);
  delay(1000); motorStop();
}
void motorBackward() {
  digitalWrite(D5, LOW); digitalWrite(D6, HIGH); digitalWrite(D7, HIGH);
  digitalWrite(D0, HIGH); digitalWrite(D1, LOW); digitalWrite(D2, HIGH);
  delay(1000); motorStop();
}

void motorLeft() {
  digitalWrite(D5, HIGH); digitalWrite(D6, LOW); digitalWrite(D7, HIGH);
  digitalWrite(D0, HIGH); digitalWrite(D1, LOW); digitalWrite(D2, HIGH);
  delay(500); motorStop();
}
void motorRight() {
  digitalWrite(D5, LOW); digitalWrite(D6, HIGH); digitalWrite(D7, HIGH);
  digitalWrite(D0, LOW); digitalWrite(D1, HIGH); digitalWrite(D2, HIGH);
  delay(500); motorStop();
}


void setup() {

  Serial.begin(115200);
  delay(10);

  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT); // EN1,2

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT); // EN3,4

  motorStop();

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

  if (request.indexOf("/FORWARD") != -1) motorForward();
  else if (request.indexOf("/BACKWARD") != -1) motorBackward();
  else if (request.indexOf("/LEFT") != -1) motorLeft();
  else if (request.indexOf("/RIGHT") != -1) motorRight();

  // Return the response

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<br><br>");
  client.println("<a href=\"/FORWARD\"\"><button>FORWARD</button></a>");
  client.println("<a href=\"/BACKWARD\"\"><button>BACKWARD</button></a><br />");
  client.println("<br>");
  client.println("<a href=\"/LEFT\"\"><button>LEFT</button></a>");
  client.println("<a href=\"/RIGHT\"\"><button>RIGHT</button></a><br />");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

