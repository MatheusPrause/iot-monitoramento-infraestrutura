#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// Configuração dos Pinos
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_PIN 34 // Simulado pelo Potenciômetro
#define BUZZER_PIN 12
#define LED_PIN 14

// Configurações Wi-Fi nativas do Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações MQTT (Broker Público para testes)
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "infra/rack01/dados";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a rede: ");
  Serial.println(ssid);
  // O Wokwi exige o canal 6 para o WiFi funcionar
  WiFi.begin(ssid, password, 6); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado com sucesso!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexao MQTT...");
    String clientId = "ESP32_Rack_";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao Broker!");
    } else {
      Serial.print("Falha, erro=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura dos Sensores
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int gasLevel = analogRead(MQ135_PIN); // Simulação

  if (isnan(t) || isnan(h)) {
    Serial.println("Falha ao ler o sensor DHT22!");
    return;
  }

  // Print no console serial
  Serial.print("Temperatura: "); Serial.print(t);
  Serial.print(" *C | Umidade: "); Serial.print(h);
  Serial.print(" % | Nível de Gás (Simulado): "); Serial.println(gasLevel);

  // Lógica de Atuação: Se passar de 30 graus, liga os alertas
  if (t > 30.0) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000); 
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  // Monta a string JSON para enviar via MQTT
  String payload = "{\"temperatura\": " + String(t) + ", \"umidade\": " + String(h) + ", \"gas\": " + String(gasLevel) + "}";
  client.publish(mqtt_topic, payload.c_str());

  // Delay de 5 segundos para visualização no vídeo
  delay(5000); 
}