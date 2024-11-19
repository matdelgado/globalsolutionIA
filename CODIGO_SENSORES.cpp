#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const int ldrPin = 34;  // LDR 
const int potPin = 35;  // potenciômetro 
const int DHT_PIN = 27; // DHT22 

WiFiClient espClient;
PubSubClient client(espClient);

DHTesp dhtSensor;

String solarPanels[] = {
  "JA Solar 450W", 
  "Canadian Solar 500W", 
  "Trina Solar 400W", 
  "SunPower 470W", 
  "LONGi Solar 540W"
};
const int numPanels = sizeof(solarPanels) / sizeof(solarPanels[0]);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client_" + String(WiFi.macAddress());
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22); // Configuração do DHT22
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  String selectedPanel = solarPanels[random(0, numPanels)];

  int ldrValue = analogRead(ldrPin);
  Serial.print("LDR Sensor Value (Raw): ");
  Serial.println(ldrValue);
  client.publish("monitoring/sensor/ldr", String(ldrValue).c_str());

  int potValue = analogRead(potPin);
  float consumoKW = map(potValue, 0, 4095, 0, 10000) / 1000.0; // Converte para faixa de 0 a 10 kW
  Serial.print("Consumo (kW): ");
  Serial.println(consumoKW);
  client.publish("monitoring/sensor/energy", String(consumoKW).c_str());

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  String temp = String(data.temperature, 2);
  String hum = String(data.humidity, 1);

  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(hum);

  client.publish("monitoring/sensor/temperature", temp.c_str());
  client.publish("monitoring/sensor/humidity", hum.c_str());
  client.publish("monitoring/sensor/solar_panel", selectedPanel.c_str());

  Serial.print("Selected Solar Panel: ");
  Serial.println(selectedPanel);

  delay(5000);
}
