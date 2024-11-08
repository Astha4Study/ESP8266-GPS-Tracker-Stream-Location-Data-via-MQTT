#include <ESP8266WiFi.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "ThingSpeak.h"

// GPS Configuration
TinyGPSPlus gps;
#define GPS_BAUDRATE 9600

// Initialize SoftwareSerial for GPS on D6 (TX) and D5 (RX)
SoftwareSerial gpsSerial(D5, D6); // RX, TX

String lat_data, lng_data;

// Wi-Fi and ThingSpeak Configuration
const char* ssid = "xxx"; // Replace with your Wi-Fi SSID
const char* password = "xxx"; // Replace with your Wi-Fi password
WiFiClient client;
unsigned long myChannelNumber = xxx;  // Replace with your Channel ID
const char* myWriteAPIKey = "xxx"; // Replace with your Write API Key

// Interval to send data to ThingSpeak
unsigned long previousMillis_ts = 0;
const long ts_update_interval = 20000;

void setup() {
  Serial.begin(115200);          // Serial monitor
  gpsSerial.begin(GPS_BAUDRATE); // Serial for GPS

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read data from GPS
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        lat_data = String(gps.location.lat(), 6);
        lng_data = String(gps.location.lng(), 6);
        Serial.print("Latitude: "); Serial.println(lat_data);
        Serial.print("Longitude: "); Serial.println(lng_data);
      } else {
        Serial.println("Invalid GPS data");
      }
    }
  }

  // Send data to ThingSpeak every set interval
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_ts >= ts_update_interval) {
    previousMillis_ts = currentMillis;

    // Check Wi-Fi connection
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Reconnecting to Wi-Fi...");
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
    }

    // Send data to ThingSpeak
    ThingSpeak.setField(1, lat_data); // Latitude field
    ThingSpeak.setField(2, lng_data); // Longitude field
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    
    if (x == 200) {
      Serial.println("Data successfully sent to ThingSpeak.");
    } else {
      Serial.println("Failed to send data. Error: " + String(x));
    }
  }
}
