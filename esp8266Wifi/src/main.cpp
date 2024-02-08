#include "./classes/MQTT.h"
#include "./classes/WIFI.h"
#include <Arduino.h>

/* #include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//Variáveis de Conexão Wifi
const char* ssid = "Tiago";
const char* password = "12345678";

//MQTT Broker
const char* mqttBroker = "test.mosquitto.org";
const char* topic = "Tiago/teste";
const char* mqttUserName = "";
const char* mqttPassWord = "";
const int mqttPort = 1883;

//Status da conexão
bool mqttStatus = 0;

//
WiFiClient espClient; // Parametro para que o mqtt saiba que a conexão de Wifi retornou com êxito (Verificar enlace de conexão)
PubSubClient client(espClient); //objeto com os métodos de chamada MQTT (Recebe os paramentros de conexão Wifi como atributo)

//Protótipos
bool connectMQTT(); //retorna se a conexão com o broker teve exito
void callback(char* topic, byte* payload, unsigned int length); //retorno de mensagens publicadas no tópico


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("\n Conectando ao Wifi ");

  while (WiFi.status() != WL_CONNECTED )
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n Wifi Conectado \n");
  Serial.println(WiFi.localIP());
  
  mqttStatus = connectMQTT();

  pinMode(A0, INPUT);

}

void loop() {
  static long long pooling;

  if (mqttStatus){
    client.loop();

    for(int i = 0; i < 400; i++){
      int aRead = analogRead(A0);
    }

    if (millis() > pooling+1000){
      pooling = millis();
      Serial.println("Publicando");
      client.publish(topic, "{teste, pooling}");
    }
    delay(10);
  }
}

bool connectMQTT(){
  byte tentativa = 0;
  client.setServer(mqttBroker, mqttPort);
  client.setCallback(callback);
  
  do
  {
    String clientId = "T-aaago";
    clientId += String(WiFi.macAddress());

    if(client.connect(clientId.c_str(), mqttUserName, mqttPassWord)){
      Serial.println("Exito na conexão:");
      Serial.printf("Cliente %s conectado ao broker\n", clientId.c_str());
    } else {
      Serial.println("Falha na conexão com o broker");
      Serial.print("conexão: ");
      Serial.print(client.state());
      Serial.printf("\nTentativa: %i", tentativa);
      delay(1000);
    } 
    tentativa++;
  } while (!client.connected() && tentativa < 5);

  if(tentativa < 5){
    client.publish(topic, "{teste: 'funcionando', 'json'}");
    client.subscribe(topic);
    return 1;
  } else{
      Serial.println("Não conectado");
      return 0;
  }
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Nova mensagem no tópico: ");
  Serial.println(topic);
  Serial.println("Mensagem:");
  for (int i = 0 ; i < length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println("\n ------------------------------");
}; */


MQTT mqtt("T-aaago");
  
void setup(){
  Serial.begin(115200);
  ConnectWifi();
  mqtt.connectMQTT();
}

void loop(){
 if(mqtt.mqttStatus){
    mqtt.client->loop();
 }
}