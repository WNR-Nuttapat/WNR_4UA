#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

// REPLACE WITH YOUR EVENT NAME AND API KEY - open the documentation: https://ifttt.com/maker_webhooks
const char* eventname = "REPLACE_WITH_YOUR_EVENT_NAME";
const char* eventapi = "REPLACE_WITH_YOUR_API_KEY";

String serverName = "http://maker.ifttt.com/trigger/" + String(eventname) + "/with/key/" + String(eventapi);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  //Value to sent to IFTTT
  float value1=millis()/1000;
  int value2=random(40);
  char value3[]="TEST";
  
  // Send an HTTP POST request every 10 seconds
  delay(10000);
  
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Data to send with HTTP POST
    String httpRequestData = "value1=" + String(value1) + "&value2=" + String(value2) + "&value3=" + String(value3);
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }

}
