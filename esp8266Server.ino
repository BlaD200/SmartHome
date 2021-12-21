#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <GParser.h>
#include <SoftwareSerial.h>

const char* ssid = "Iron_Tony";
const char* password = "irony140800";

bool ledState = 0;
const int ledPin = 2;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

SoftwareSerial mySerial(2, 3); // RX, TX

void alertClients() {
  ws.textAll("alert");
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "alert") == 0) {
      ledState = !ledState;
      alertClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        // Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        // Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        // Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup(){
  Serial.begin(9600);
  mySerial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    // Serial.println("Connecting to WiFi..");
  }

  // Serial.println(WiFi.localIP());

  initWebSocket();

  server.begin();
}

void loop() {
  ws.cleanupClients();
  digitalWrite(ledPin, ledState);

  if (mySerial.available()) {
    char str[30];
    int len = mySerial.readBytesUntil(';', str, 30);
    str[len] = 0;
    Serial.println(str);

    if (strcmp(str, "alert") == 0) {
      alertClients();
    } else if (str != "") {
      GParser data(str, '|');
      int amount = data.split();
      if (amount != 2)
        return;
        
      float temperature = data.getFloat(0);
      float humidity = data.getFloat(1);
      
      String result = "data";
      result += String(temperature) + "|" + String(humidity);
      ws.textAll(result);
    }
  }

  if (Serial.available()) {
    static bool light = true;
    digitalWrite(2, light ? HIGH : LOW);
    digitalWrite(3, light ? LOW : HIGH);
    light = !light;
    Serial.println(light);
    
    char str[30];
    int len = Serial.readBytesUntil(';', str, 30);
    str[len] = 0;
    mySerial.write("hello;");
  }
}
