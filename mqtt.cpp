#include <WiFi.h>
#include <PubSubClient.h>
#include "json.h"
#include "mqtt.h"
#include "config.h"

//const char* mqtt_server = "cretabase.kbvision.tv";
//#define mqtt_port 1883
//#define MQTT_USER "leiioxwr"
//#define MQTT_PASSWORD "98NW8KaE_FCH"
//#define MQTT_SMS_RESULT "/result"
//#define MQTT_CMD "/cmd"
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void reconnect() {
  // Loop until we're reconnected
  //Serial.println(WiFi.status());
//  if (WiFi.status() == WL_DISCONNECTED) return;
//  if (WiFi.status() == WL_NO_SHIELD) return;
//  if (WiFi.status() == WL_CONNECT_FAILED) return;
  if (WiFi.isConnected()) {
    unsigned long t;
    t = millis();
    while (!client.connected()||client.state()!=0) {
      Serial.print("Connecting to MQTT...");
    // Create a random client ID
      String clientId = "ESP32Client-";
      clientId += getData("deviceID");
    // Attempt to connect
      if (client.connect(clientId.c_str(),getData("username").c_str(),getData("pass").c_str())) {
        Serial.println("connected");
        t = millis();
        String cmdTopic = getData("command");
        cmdTopic.replace("%%ID%%",getData("deviceID"));
        client.subscribe(cmdTopic.c_str());
        client.subscribe(cmdTopic.c_str());
        Serial.println(cmdTopic);
      } else {
        Serial.println(client.state());
      
        if (millis()-t>30000&&client.state()!=0){
		      Serial.println("CAN'T CONNECT TO MQTT");
		      Serial.println("RESETTING, PLEASE WAIT...");
		      ESP.restart();
	      }
    }
    delay(5000);
  }
    }
}
void publishData(const char *topic,const char *serialData){
  if (WiFi.status() != WL_CONNECTED) return;
  
  if (!client.connected()) {
    reconnect();
  }
  Serial.print("PUBLISH: \"");
  Serial.println(topic);
//  Serial.print("\" : \"");
//  Serial.print(serialData);
//  Serial.println("\"");
  client.publish(topic, serialData);
}
void controlcallback(char* topic, byte *payload, unsigned long length)
{

  String data;
  for (unsigned long i=0;i<length;i++) {
    data += String((char)payload[i]);
  }
//  Serial.println(length);
//  Serial.println("RECEIVED:");
//  Serial.println(data);
//  Serial.println(topic);
  
      char* dat = &data[0];
      jsonDeserialize(dat);
      
}
void MQTTsetup() {
  String host = getData("host");
  const char* mqtt_server =  host.c_str();
  client.setServer(mqtt_server, getData("port").toInt());
  client.setCallback(controlcallback);
  reconnect();
}

void MQTTloop(void)
{
 client.loop();
 if (!client.connected()) {
    reconnect();
  }	
}
