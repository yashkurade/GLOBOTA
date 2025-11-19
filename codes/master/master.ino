/*
  ESP8266 OTA Bootloader (Initial Firmware)
  -----------------------------------------
  This is the first firmware you flash using USB.

  After flashing this:
    ➤ Connect to WiFi
    ➤ Open the OTA Update page
    ➤ Upload new firmware wirelessly (with password)
    ➤ All future firmware must include OTA code again!

  Replace placeholders:
      <WIFI_SSID>
      <WIFI_PASSWORD>
      <OTA_USERNAME>
      <OTA_PASSWORD>
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

// ---------------- WIFI CREDENTIALS ----------------
const char* ssid = "<WIFI_SSID>";
const char* password = "<WIFI_PASSWORD>";
// --------------------------------------------------

// -------- OTA LOGIN CREDENTIALS --------
const char* update_username = "<OTA_USERNAME>";
const char* update_password = "<OTA_PASSWORD>";
// ---------------------------------------

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup() {
  Serial.begin(115200);
  delay(300);

  // ---- Connect WiFi ----
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // ---- SIMPLE HOMEPAGE ----
  server.on("/", []() {
    server.send(200, "text/html",
      "<html><body>"
      "<h2>ESP8266 OTA Bootloader</h2>"
      "<p>Device is ready for wireless firmware update.</p>"
      "<p><a href='/update'>Go to OTA Update Page</a></p>"
      "</body></html>"
    );
  });

  // ---- PASSWORD-PROTECTED OTA PAGE ----
  httpUpdater.setup(&server, "/update", update_username, update_password);

  // ---- Start Server ----
  server.begin();

  Serial.println("HTTP Server Started.");
  Serial.print("Home Page: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  Serial.print("OTA Update Page: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/update");
}

void loop() {
  server.handleClient();  // required to keep OTA page running
}
