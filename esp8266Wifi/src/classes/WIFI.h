#include <ESP8266WiFi.h>
#include "../env.h"

#ifndef WIFI_H
#define WIFI_H

void ConnectWifi(){
    WiFi.begin(SSID, WIFI_PASSWORD);

    Serial.print("\n Conectando ao Wifi ");

  while (WiFi.status() != WL_CONNECTED )
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n Wifi Conectado \n");
  Serial.println(WiFi.localIP());
  
  return;
}




#endif