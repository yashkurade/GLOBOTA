/*
  ESP8266 OTA Update Template (Password Protected)
  ------------------------------------------------
  This template provides a reusable structure for ESP8266 projects
  where OTA firmware updates must remain functional after every upload.

  ➤ Replace placeholders like:
      <WIFI_SSID>
      <WIFI_PASSWORD>
      <OTA_USERNAME>
      <OTA_PASSWORD>

  ➤ Put all your main logic inside:
      // --- USER PROJECT CODE HERE ---
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

// ---------------- WIFI CREDENTIALS ----------------
const char* ssid = "<WIFI_SSID>";
const char* password = "<WIFI_PASSWORD>";
// --------------------------------------------------

// ---------------- OTA LOGIN -----------------------
const char* update_username = "<OTA_USERNAME>";
const char* update_password = "<OTA_PASSWORD>";
// --------------------------------------------------

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup() {
  Serial.begin(115200);
  delay(300);

  // ---- Setup GPIO if needed (optional) ----
  // Example:
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, HIGH);

  // ---- Connect to WiFi ----
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // ---- OPTIONAL HOMEPAGE ----
  server.on("/", []() {
    server.send(200, "text/html",
      "<h3>ESP8266 OTA Template Running</h3>"
      "<p><a href='/update'>Go to OTA Update</a></p>"
    );
  });

  // ---- OTA WEB UPDATE (Password Protected) ----
  httpUpdater.setup(&server, "/update", update_username, update_password);

  // ---- Start Web Server ----
  server.begin();

  Serial.println("HTTP Server Started");
  Serial.print("OTA Update Page: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/update");
}

void loop() {
  server.handleClient();  // IMPORTANT: keeps OTA webpage alive

  // ============================================================
  //                 --- USER PROJECT CODE HERE ---
  //    Write your normal project logic inside this section.
  //    Example (remove this block before using):
  //
  //    if (millis() - lastToggle >= 1000) {
  //      lastToggle = millis();
  //      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  //    }
  //
  // ============================================================
}
