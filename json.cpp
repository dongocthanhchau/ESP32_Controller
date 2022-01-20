#include "Arduino.h"
#include "ArduinoJson.h"
#include "json.h"
#include "devices.h"

void jsonDeserialize(char* json)//char* json, String &to, String &text,int &function, String &messageId)
{
  //const size_t capacity = JSON_ARRAY_SIZE(40) + 20*JSON_OBJECT_SIZE(10) + 200;
  StaticJsonDocument<768> doc;


//  const char* json = "[{\"value\":100,\"type\":\"O1\",\"time\":100},{\"value\":0,\"type\":\"O2\",\"time\":100},{\"value\":100,\"type\":\"O3\",\"time\":100},{\"value\":0,\"type\":\"O4\",\"time\":100},{\"value\":100,\"type\":\"O5\",\"time\":0},{\"value\":0,\"type\":\"O6\",\"time\":0}]";

  deserializeJson(doc, json);
  for (JsonObject item : doc.as<JsonArray>()) {

    int value = item["value"]; // 100, 100, 100, 100, 100, 100, 100, 100
    const char* type = item["type"]; // "O1", "O2", "O3", "O4", "O5", "O6", "O7", "O8"
    int time = item["time"]; // 7, 6, 5, 4, 3, 2, 1, 0
    if (strstr(type,"O1")!=NULL){
       deviceSet(1, value, time);
    } else
    if (strstr(type,"O2")!=NULL){
       deviceSet(2, value, time);
    } else
    if (strstr(type,"O3")!=NULL){
       deviceSet(3, value, time);
    } else
    if (strstr(type,"O4")!=NULL){
       deviceSet(4, value, time);   
    } else
    if (strstr(type,"O5")!=NULL){
       deviceSet(5, value, time);
    } else
    if (strstr(type,"O6")!=NULL){
       deviceSet(6, value, time);
    } else
    if (strstr(type,"O7")!=NULL){
       deviceSet(7, value, time);
    } else
    if (strstr(type,"O8")!=NULL){
       deviceSet(8, value, time);
    } 
  }
//  JsonObject root = doc[0];
//  if (doc[0].isNull()) return;
//  int value = root["value"]; // 100
//  int time = root["time"]; // 100
//  const char* type = root["type"];
//  if (strstr(type,"O1")!=NULL)
//    deviceSet(1, value, time);
//    else if (strstr(type,"O2")!=NULL)
//          deviceSet(2, value, time);
//          else if (strstr(type,"O3")!=NULL)
//                deviceSet(3, value, time);
//                else if (strstr(type,"O4")!=NULL)
//                      deviceSet(4, value, time);
//                      else if (strstr(type,"O5")!=NULL)
//                            deviceSet(5, value, time);
//                            else if (strstr(type,"O6")!=NULL)
//                                  deviceSet(6, value, time);

                                  
//  if (doc[1].isNull()) return;             
//  root = doc[1];
//  value = root["value"]; 
//  time = root["time"]; 
//  type = root["type"];
//  if (strstr(type,"O2")!=NULL)
//    deviceSet(2, value, time);
//    else if (strstr(type,"O3")!=NULL)
//          deviceSet(3, value, time);
//          else if (strstr(type,"O4")!=NULL)
//                deviceSet(4, value, time);
//                else if (strstr(type,"O5")!=NULL)
//                      deviceSet(5, value, time);
//                      else if (strstr(type,"O6")!=NULL)
//                            deviceSet(6, value, time);
//                            else if (strstr(type,"O1")!=NULL)
//                                  deviceSet(1, value, time);


    
    
//  if (doc[2].isNull()) return;
//  root = doc[2];
//  value = root["value"]; 
//  time = root["time"]; 
//  type = root["type"];
//  if (strstr(type,"O3")!=NULL)
//    deviceSet(3, value, time);
//    else if (strstr(type,"O4")!=NULL)
//          deviceSet(4, value, time);
//          else if (strstr(type,"O5")!=NULL)
//                deviceSet(5, value, time);
//                else if (strstr(type,"O6")!=NULL)
//                      deviceSet(6, value, time);
//                      else if (strstr(type,"O1")!=NULL)
//                            deviceSet(1, value, time);
//                            else if (strstr(type,"O2")!=NULL)
//                                  deviceSet(2, value, time);
//  if (doc[3].isNull()) return;
//  root = doc[3];
//  value = root["value"]; 
//  time = root["time"]; 
//  type = root["type"];
//  if (strstr(type,"O4")!=NULL)
//    deviceSet(4, value, time);
//    else if (strstr(type,"O5")!=NULL)
//          deviceSet(5, value, time);
//          else if (strstr(type,"O6")!=NULL)
//                deviceSet(6, value, time);
//                else if (strstr(type,"O1")!=NULL)
//                      deviceSet(1, value, time);
//                      else if (strstr(type,"O2")!=NULL)
//                            deviceSet(2, value, time);
//                            else if (strstr(type,"O3")!=NULL)
//                                  deviceSet(3, value, time);
//  if (doc[4].isNull()) return;
//  root = doc[4];
//  value = root["value"]; 
//  time = root["time"]; 
//  type = root["type"];
//  if (strstr(type,"O5")!=NULL)
//    deviceSet(5, value, time);
//    else if (strstr(type,"O6")!=NULL)
//          deviceSet(6, value, time);
//          else if (strstr(type,"O1")!=NULL)
//                deviceSet(1, value, time);
//                else if (strstr(type,"O2")!=NULL)
//                      deviceSet(2, value, time);
//                      else if (strstr(type,"O3")!=NULL)
//                            deviceSet(3, value, time);
//                            else if (strstr(type,"O4")!=NULL)
//                                  deviceSet(4, value, time);
//  if (doc[5].isNull()) return;
//  root = doc[5];
//  value = root["value"]; 
//  time = root["time"]; 
//  type = root["type"];
//  if (strstr(type,"O6")!=NULL)
//    deviceSet(6, value, time);
//    else if (strstr(type,"O1")!=NULL)
//          deviceSet(1, value, time);
//          else if (strstr(type,"O2")!=NULL)
//                deviceSet(2, value, time);
//                else if (strstr(type,"O3")!=NULL)
//                      deviceSet(3, value, time);
//                      else if (strstr(type,"O4")!=NULL)
//                            deviceSet(4, value, time);
//                            else if (strstr(type,"O5")!=NULL)
//                                  deviceSet(5, value, time);
//  if (doc[6].isNull()) return;
//  root = doc[6];
//  value = root["value"]; 
//  time = root["time"]; 
//  type = root["type"];
//  if (strstr(type,"O7")!=NULL)
//    deviceSet(7, value, time);
//    else if (strstr(type,"O1")!=NULL)
//          deviceSet(1, value, time);
//          else if (strstr(type,"O2")!=NULL)
//                deviceSet(2, value, time);
//                else if (strstr(type,"O3")!=NULL)
//                      deviceSet(3, value, time);
//                      else if (strstr(type,"O4")!=NULL)
//                            deviceSet(4, value, time);
//                            else if (strstr(type,"O5")!=NULL)
//                                  deviceSet(5, value, time);
//  if (doc[7].isNull()) return;
//  root = doc[7];
//  value = root["value"]; 
//  time = root["time"]; 
//  type = root["type"];
//  if (strstr(type,"O8")!=NULL)
//    deviceSet(8, value, time);
//    else if (strstr(type,"O1")!=NULL)
//          deviceSet(1, value, time);
//          else if (strstr(type,"O2")!=NULL)
//                deviceSet(2, value, time);
//                else if (strstr(type,"O3")!=NULL)
//                      deviceSet(3, value, time);
//                      else if (strstr(type,"O4")!=NULL)
//                            deviceSet(4, value, time);
//                            else if (strstr(type,"O5")!=NULL)
//                                  deviceSet(5, value, time);
//  //old
//  const size_t capacity = JSON_OBJECT_SIZE(10) + 500;
//  DynamicJsonDocument doc(capacity);
//  //const char* json = "{\"from\":\"sender_name String\",\"to\":\"recv_number String\",\"text\":\"message_content String\",\"function\":101,\"messageId\":\"String\"}";
//  deserializeJson(doc, json);
//  const char* t = doc["to"]; // "recv_number String"
//  to = t;
//  const char* te = doc["text"]; // "message_content String"
//  text = te;
//  int func = doc["function"]; // 101
//  function = func;
//  const char* m = doc["messageId"]; // "String"
//  messageId = m;
}

String jsonSerialize(int v1,long t1,int v2,long t2,int v3,long t3,int v4,long t4,int v5,long t5,int v6,long t6,int v7,long t7,int v8,long t8)//String num,int id,String stt,String messageId)
{
  const size_t capacity = JSON_ARRAY_SIZE(20) + 20*JSON_OBJECT_SIZE(10);
  DynamicJsonDocument doc(capacity);

  JsonObject doc_0 = doc.createNestedObject();
  doc_0["value"] = v1;// 100;
  doc_0["type"] = "O1";
  doc_0["time"] = t1;//100;

  JsonObject doc_1 = doc.createNestedObject();
  doc_1["value"] = v2;//0;
  doc_1["type"] = "O2";
  doc_1["time"] = t2;//100;

  JsonObject doc_2 = doc.createNestedObject();
  doc_2["value"] = v3;//100;
  doc_2["type"] = "O3";
  doc_2["time"] = t3;//100;

  JsonObject doc_3 = doc.createNestedObject();
  doc_3["value"] = v4;//0;
  doc_3["type"] = "O4";
  doc_3["time"] = t4;//100;
  
  JsonObject doc_4 = doc.createNestedObject();
  doc_4["value"] = v5;//100;
  doc_4["type"] = "O5";
  doc_4["time"] = t5;//0;

  JsonObject doc_5 = doc.createNestedObject();
  doc_5["value"] = v6;//0;
  doc_5["type"] = "O6";
  doc_5["time"] = t6;//0;

  JsonObject doc_6 = doc.createNestedObject();
  doc_6["value"] = v7;//0;
  doc_6["type"] = "O7";
  doc_6["time"] = t7;//0;

  JsonObject doc_7 = doc.createNestedObject();
  doc_7["value"] = v8;//0;
  doc_7["type"] = "O8";
  doc_7["time"] = t8;//0;

  String dat;
  serializeJson(doc, dat);
//  Serial.println(dat);
  return dat;
}

void SPIFFSjsonDeserialize(const char*json, String &deviceID, String &ssid, String &password, String &ipaddress, String &host, String &port, String &username, String &pass, String &status, String &command, String &result)
{
  const size_t capacity = JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(10) + 250;
  DynamicJsonDocument doc(capacity);

  //const char* json = "{\"device\":{\"deviceID\":\"12DWR\"},\"wifi\":{\"ssid\":\"YOURSOLUTION\",\"password\":\"yoursolution\",\"ipaddress\":\"192.168.3.127\"},\"mqtt\":{\"host\":\"cretabase.kbvision.tv\",\"port\":\"1883\",\"username\":\"leiioxwr\",\"password\":\"98NW8KaE_FCH\",\"topic\":{\"status\":\"/status\",\"command\":\"/cmd\",\"result\":\"/result\"}}}";

  deserializeJson(doc, json);

  const char* device_deviceID = doc["device"]["deviceID"]; // "12DWR"
  deviceID = String(device_deviceID);
  
  JsonObject wifi = doc["wifi"];
  const char* wifi_ssid = wifi["ssid"]; // "YOURSOLUTION"
  ssid = String(wifi_ssid);
  const char* wifi_password = wifi["password"]; // "yoursolution"
  password = String (wifi_password);
  const char* wifi_ipaddress = wifi["ipaddress"]; // "192.168.3.127"
  ipaddress = String(wifi_ipaddress);

  JsonObject mqtt = doc["mqtt"];
  const char* mqtt_host = mqtt["host"]; // "cretabase.kbvision.tv"
  host = String(mqtt_host);
  const char* mqtt_port = mqtt["port"]; // "1883"
  port = String(mqtt_port);
  const char* mqtt_username = mqtt["username"]; // "leiioxwr"
  username = String(mqtt_username);
  const char* mqtt_password = mqtt["password"]; // "98NW8KaE_FCH"
  pass = String(mqtt_password);
  
  JsonObject mqtt_topic = mqtt["topic"];
  const char* mqtt_topic_status = mqtt_topic["status"]; // "/status"
  status = String(mqtt_topic_status);
  const char* mqtt_topic_command = mqtt_topic["command"]; // "/cmd"
  command = String(mqtt_topic_command);
  const char* mqtt_topic_result = mqtt_topic["result"]; // "/result"
  result = String(mqtt_topic_result);
}
String SPIFFSjsonSerialize(String deviceID, String ssid, String password, String ipaddress, String host, String port, String username, String pass, String status, String command, String result)
{
  const size_t capacity = JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(10);
  DynamicJsonDocument doc(capacity);  

  JsonObject device = doc.createNestedObject("device");
  device["deviceID"] = deviceID;//"12DWR";

  JsonObject wifi = doc.createNestedObject("wifi");
  wifi["ssid"] = ssid;//"YOURSOLUTION";
  wifi["password"] = password;//"yoursolution";
  wifi["ipaddress"] = ipaddress;//"192.168.3.127";

  JsonObject mqtt = doc.createNestedObject("mqtt");
  mqtt["host"] = host;//"cretabase.kbvision.tv";
  mqtt["port"] = port;//"1883";
  mqtt["username"] = username;//"leiioxwr";
  mqtt["password"] = pass;//"98NW8KaE_FCH";

  JsonObject mqtt_topic = mqtt.createNestedObject("topic");
  mqtt_topic["status"] = status;//"/status";
  mqtt_topic["command"] = command;//"/cmd";
  mqtt_topic["result"] = result;//"/result";
  
  String dat;
  serializeJson(doc, dat);
  return dat;
//serializeJson(doc, Serial);
}
String sensorSerialize(float temp, float humid, float ec, float ph, float light, float wind, float soil)
{
  const size_t capacity = JSON_ARRAY_SIZE(10) + 10*JSON_OBJECT_SIZE(3);
  DynamicJsonDocument doc(capacity);

  JsonObject doc_0 = doc.createNestedObject();
  doc_0["value"] = light;
  doc_0["type"] = "I1";

  JsonObject doc_1 = doc.createNestedObject();
  doc_1["value"] = ph;
  doc_1["type"] = "I2";

  JsonObject doc_2 = doc.createNestedObject();
  doc_2["value"] = temp;
  doc_2["type"] = "I3";

  JsonObject doc_3 = doc.createNestedObject();
  doc_3["value"] = humid;
  doc_3["type"] = "I4";

  JsonObject doc_4 = doc.createNestedObject();
  doc_4["value"] = soil;
  doc_4["type"] = "I5";

  JsonObject doc_5 = doc.createNestedObject();
  doc_5["value"] = ec;
  doc_5["type"] = "I6";

  JsonObject doc_6 = doc.createNestedObject();
  doc_6["value"] = wind;
  doc_6["type"] = "I7";
  String st;
  serializeJson(doc, st);
  return st;
}
