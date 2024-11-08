# ESP8266-GPS-Tracker-MQTT

This tutorial demonstrates how to use the ESP8266 with a GPS module to send location data (latitude and longitude) to ThingSpeak over Wi-Fi.

### Hardware Setup
1. **Connect the VCC pin** of the GPS module to the **VV** pin of the ESP8266.
2. **Connect the ground (GND) pin** of the GPS module to the **GND** pin of the ESP8266.
3. **Connect the RX pin** of the GPS module to the **TX pin (D6)** of the ESP8266.
4. **Connect the TX pin** of the GPS module to the **RX pin (D5)** of the ESP8266.

### Libraries Required
- `WiFiClient`
- `TinyGPSPlus`
- `SoftwareSerial`
- `ThingSpeak`

### Setting up Thingspeak
1. Create a new channel on ThingSpeak.
2. Add two fields for latitude and longitude.
3. Copy the Channel ID and paste it into myChannelNumber in the code.
4. To get the API Key, go to the API Keys section in your ThingSpeak account and paste the Write API Key into myWriteAPIKey in the code.

### Setting up JavaScript
1. Copy the Channel ID and API keys into (https://api.thingspeak.com/channels/yourChannelID/feeds/last.json?timezone=Asia%2FJakarta&api_key=yourApiKeys) in the mapAPI.js code.
