#include "../env.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

#ifndef MQTT_H
#define MQTT_H


class MQTT
{
public:
    String clientId;
    WiFiClient espClient;
    bool mqttStatus;
    PubSubClient* client = new PubSubClient(espClient);
    
    bool connectMQTT();
    static void callback(char* topic, byte* payload, unsigned int length);

    MQTT(String);
    ~MQTT();

};

MQTT::MQTT(String clientId)
:clientId(clientId)
{

}

MQTT::~MQTT()
{
}


bool MQTT::connectMQTT(){
  byte tentativa = 0;
  client->setServer(MQTT_BROKER, MQTT_PORT);
  client->setCallback(callback);
  
  do
  {
    
    clientId += String(WiFi.macAddress());

    if(client->connect(clientId.c_str(), MQTT_USER_NAME, MQTT_PASSWORD)){
      Serial.println("Exito na conexão:");
      Serial.printf("Cliente %s conectado ao broker\n", clientId.c_str());
      mqttStatus = true;
    } else {
      Serial.println("Falha na conexão com o broker");
      Serial.print("conexão: ");
      Serial.print(client->state());
      Serial.printf("\nTentativa: %i", tentativa);
      delay(1000);
    } 
    tentativa++;
  } while (!client->connected() && tentativa < 5);

  if(tentativa < 5){
    client->publish(TOPIC, "{teste: 'funcionando', 'json'}");
    client->subscribe(TOPIC);
    return 1;
  } else{
      Serial.println("Não conectado");
      return 0;
  }
}

void MQTT::callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Nova mensagem no tópico: ");
  Serial.println(topic);
  Serial.println("Mensagem:");
  for (unsigned int i = 0 ; i < length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println("\n ------------------------------");
};


#endif
