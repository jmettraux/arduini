
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
  delay(250); motorStop();
}
void motorRight() {
  digitalWrite(D5, LOW); digitalWrite(D6, HIGH); digitalWrite(D7, HIGH);
  digitalWrite(D0, LOW); digitalWrite(D1, HIGH); digitalWrite(D2, HIGH);
  delay(250); motorStop();
}


void setup() {

  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT); // EN1,2

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT); // EN3,4

  motorStop();

  // Kick in serial
  Serial.begin(115200);
  delay(10);

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
  client.println("<head>");
  client.println("<style>");
  client.println("  body {");
  client.println("    font-size: 200%;");
  client.println("  }");
  client.println("  table {");
  client.println("    width: 100%;");
  client.println("  }");
  client.println("  td {");
  client.println("    width: 49%;");
  client.println("    text-align: center;");
  client.println("    height: 7em;");
  client.println("    pointer: cursor;");
  client.println("    color: white;");
  client.println("  }");
  client.println("  td.forward {");
  client.println("    background-color: blue;");
  client.println("  }");
  client.println("  td.backward {");
  client.println("    background-color: green;");
  client.println("  }");
  client.println("  td.left {");
  client.println("    background-color: green;");
  client.println("  }");
  client.println("  td.right {");
  client.println("    background-color: blue;");
  client.println("  }");
  client.println("</style>");
  client.println("</head>");

  client.println("<table>");
  client.println("  <tr>");
  client.println("    <td class=\"forward\" onclick=\"forward();\">FORWARD</td>");
  client.println("    <td class=\"backward\" onclick=\"backward();\">BACKWARD</td>");
  client.println("  </tr>");
  client.println("  <tr>");
  client.println("    <td class=\"left\" onclick=\"left();\">LEFT</td>");
  client.println("    <td class=\"right\" onclick=\"right();\">RIGHT</td>");
  client.println("  </tr>");
  client.println("</table>");
  client.println("<script>");
  client.println("  function forward() { window.location.href = '/FORWARD'; }");
  client.println("  function backward() { window.location.href = '/BACKWARD'; }");
  client.println("  function left() { window.location.href = '/LEFT'; }");
  client.println("  function right() { window.location.href = '/RIGHT'; }");
  client.println("</script>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

