#include "constants.h"


bool wifiConnect() {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.hostname(devicename);
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        while (WiFi.waitForConnectResult() != WL_CONNECTED) {
            delay(5000);
            // ESP.restart();
            return false; // not connected
         }

        // MDNS.begin(devicename); // set by ArduinoOTA
        ArduinoOTA.setHostname(devicename);
        ArduinoOTA.begin();
    }
    return true; // connected
}


void mqttConnect() {
    if (WiFi.status() == WL_CONNECTED) {
        if (!client.connected()) {
            if (client.connect(devicename, mqtt_status_topic, 0, true, "{\"status\": \"error\", \"value\": -1}")) {
                client.publish(mqtt_status_topic, "{\"status\": \"connected\", \"value\": 1}", true);
                mqttSubscribe();
            } else {
                delay(5000);
            }
        }    }
}


void callback(char* topic, byte* payload, unsigned int length) {
    char json[100];

    // Copy payload to read/write array
    for (int i = 0; i < length; i++) {
        json[i] = payload[i];
    }

    // Parse JSON
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success())
    {
        return; // parse error
    }

    int value = root["value"];
    String stopic = String(topic);
    int endpointIndex = stopic.lastIndexOf('/') + 1; // get character after last '/'
    mqttCallback(stopic.substring(endpointIndex), value); // use only topic part after last '/'
}


void setup() {
    // Serial.begin(115200);
    setupPins();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}


void loop() {
    wifiConnect();
    if (!client.connected()) {
        mqttConnect();
    }
    client.loop();
    ArduinoOTA.handle();
    loopAction();
}
