#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <OneButton.h>

WiFiClient espClient;
PubSubClient client(espClient);
bool pinValue[100] = { false, };

// ------------------------------------------------------------------------- /


void setupPin(uint8_t pin, uint8_t mode) {
    pinMode(pin, mode);
}


void setupPin(uint8_t pin, uint8_t mode, uint8_t val) {
    pinMode(pin, mode);
    digitalWrite(pin, val);
}


void setPin(uint8_t pin, uint8_t val) {
    digitalWrite(pin, val);
    pinValue[pin] = val;
}


bool togglePin(uint8_t pin) {
    uint8_t val = !pinValue[pin]; // opposite state
    digitalWrite(pin, val);
    pinValue[pin] = val;
    return val;
}


void sendPin(uint8_t val, const char* topic) {
    String payload = String("{\"value\": ") + String(val) + String("}");
    client.publish(topic, payload.c_str(), true);
}


void setPinAndSend(uint8_t pin, uint8_t val, const char* topic) {
    setPin(pin, val);
    sendPin(val, topic);
}


void togglePinAndSend(uint8_t pin, const char* topic) {
    bool val = togglePin(pin);
    sendPin(val, topic);
}
