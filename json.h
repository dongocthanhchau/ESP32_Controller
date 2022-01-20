#ifndef _json__h_
#define _json__h_
void jsonDeserialize(char* json);
String jsonSerialize(int v1,long t1,int v2,long t2,int v3,long t3,int v4,long t4,int v5,long t5,int v6,long t6,int v7,long t7,int v8,long t8);
void SPIFFSjsonDeserialize(const char*json, String &deviceID, String &ssid, String &password, String &ipaddress, String &host, String &port, String &username, String &pass, String &status, String &command, String &result);
String SPIFFSjsonSerialize(String deviceID, String ssid, String password, String ipaddress, String host, String port, String username, String pass, String status, String command, String result);
String sensorSerialize(float temp, float humid, float ec, float ph, float light, float wind, float soil);
#endif
