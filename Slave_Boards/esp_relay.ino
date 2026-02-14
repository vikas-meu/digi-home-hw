#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

#define LIGHT_PIN 26
#define FAN_PIN   27

WebServer server(80);

/* ================= SETUP ================= */

void setup() {
  Serial.begin(115200);

  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  /* ===== ROUTES ===== */

  server.on("/", handleRoot);

  server.on("/light_on", []() {
    digitalWrite(LIGHT_PIN, HIGH);
    server.send(200, "text/plain", "Light ON");
  });

  server.on("/light_off", []() {
    digitalWrite(LIGHT_PIN, LOW);
    server.send(200, "text/plain", "Light OFF");
  });

  server.on("/fan_on", []() {
    digitalWrite(FAN_PIN, HIGH);
    server.send(200, "text/plain", "Fan ON");
  });

  server.on("/fan_off", []() {
    digitalWrite(FAN_PIN, LOW);
    server.send(200, "text/plain", "Fan OFF");
  });

  server.on("/all_on", []() {
    digitalWrite(LIGHT_PIN, HIGH);
    digitalWrite(FAN_PIN, HIGH);
    server.send(200, "text/plain", "All ON");
  });

  server.on("/all_off", []() {
    digitalWrite(LIGHT_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
    server.send(200, "text/plain", "All OFF");
  });

  server.begin();
}

/* ================= LOOP ================= */

void loop() {
  server.handleClient();
}

/* ================= WEB PAGE ================= */

void handleRoot() {

  String html = "<html><head><title>ESP32 Control</title></head><body>";
  html += "<h2>ESP32 Home Control</h2>";

  html += "<p><a href='/light_on'><button>Light ON</button></a></p>";
  html += "<p><a href='/light_off'><button>Light OFF</button></a></p>";

  html += "<p><a href='/fan_on'><button>Fan ON</button></a></p>";
  html += "<p><a href='/fan_off'><button>Fan OFF</button></a></p>";

  html += "<p><a href='/all_on'><button>All ON</button></a></p>";
  html += "<p><a href='/all_off'><button>All OFF</button></a></p>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}
