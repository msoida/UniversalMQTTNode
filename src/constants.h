#include <mainTop.h>

const char* ssid     = "SSID";
const char* password = "PASS";
const char* devicename = "DEVICENAME";

const char* mqtt_server = "SERVER";
const char* mqtt_status_topic = "STATUS_TOPIC";

// const uint8_t examplePin = 99;
// OneButton exampleButton(88, false); // OneButton(int pin, int activeLow)

// ------------------------------------------------------------------------- /


void setupPins() {
    // setupPin(examplePin, OUTPUT, LOW);
    // setupPin(examplePin, INPUT);
    // exampleButton.setPressTicks(1500);
    // exampleButton.attachClick(exampleFunction);
}


void mqttSubscribe() {
    // client.subscribe("topic/example");
}


void mqttCallback(String topic, int value) {
    if (topic == "example") {
        if (value > 0) {
            // setPin(examplePin, LOW);
        } else {
            // setPin(examplePin, HIGH);
        }
    }
}


void loopAction() {
    //   exampleButton.tick();
}


// ------------------------------------------------------------------------- /
