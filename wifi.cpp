#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif


#include "wifi.h"

#include <DNSServer.h>
#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <String.h>
#include "ESPAsyncWebServer.h"
#include "html.h"
#include "AsyncJson.h"
#include "json.h"
#include <HTTPClient.h>
#include <WiFiUdp.h>
#include "config.h"
#include "blynk.h"

String ssid = "Config-";
String pass = "";
String wifist="";
int n,_n;

AsyncWebServer Aserver(80);
DNSServer dnsServer;

const char* PARAM_MESSAGE = "message";

class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    wifiScanString();
    response->print(pageWifiA);
    response->print(wifist);
    response->print(pageWifiB);
    request->send(response);
  }
};
void wificfReqHandle(void)
{
  wifiScanString();
  Aserver.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", pageWifiA+wifist+pageWifiB);
  });
}
void mqttcfReqHandle(void)
{
  Aserver.on("/mqtt", HTTP_GET, [](AsyncWebServerRequest *request){
    pagemqttCf.replace("hostvalue",getData("host"));
    pagemqttCf.replace("portvalue",getData("port"));
    pagemqttCf.replace("uservalue",getData("username"));
    pagemqttCf.replace("passvalue",getData("pass"));
    pagemqttCf.replace("statusvalue",getData("status"));
    pagemqttCf.replace("cmdvalue",getData("command"));
    pagemqttCf.replace("resultvalue",getData("result"));
    pagemqttCf.replace("deviceID",getData("deviceID"));
    request->send(200, "text/html", pagemqttCf);
  });
}
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/html", page404);
}
void wifiReqHandle(void)
{
  Aserver.on("/wificf", HTTP_GET, [](AsyncWebServerRequest *request){
      ssid = request->getParam("ssid")->value();
      pass = request->getParam("pass")->value();
      request->send(200, "text/html", pageRestart);
      //request->redirect("http://"+WiFi.localIP()+"/wifi");
      vTaskDelay(2000/portTICK_PERIOD_MS);
      //Serial.println(ssid);
      //Serial.println(pass);
      //WiFi.end();
      changeData("ssid",ssid);
      changeData("password",pass);
      //WiFi.begin(ssid.c_str(), pass.c_str());
      //Serial.println("CONNECTING TO "+ssid);
      //vTaskDelay(2000/portTICK_PERIOD_MS);
      //while (WiFi.status() != WL_CONNECTED) {
//        //delay(500);        
      //}
      //delay(5000);
      
      ESP.restart();
    });
}
void mqttReqHandle(void)
{
  Aserver.on("/mqttcf", HTTP_GET, [](AsyncWebServerRequest *request){
      String ho= request->getParam("host")->value();
      String po= request->getParam("port")->value();
      String us= request->getParam("user")->value();
      String pa= request->getParam("pass")->value();
      String st= request->getParam("stat")->value();
      String cm= request->getParam("cmnd")->value();
      String re= request->getParam("rest")->value();
      
      request->send(200, "text/html", pageRestart);
      
      vTaskDelay(2000/portTICK_PERIOD_MS);
      changeData("host",ho);
      changeData("port",po);
      changeData("username",us);
      changeData("pass",pa);
      changeData("status",st);
      changeData("command",cm);
      changeData("result",re);
      delay(100);
      ESP.restart();
    });
}
void mainReqHandle(void)
{
  
  Aserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", pageMain);
  });
}
//===========================================================================================//
// Begin with this things


//End Fix Code Here
//===============================================================//

void wifiScanString(void)
{
    
    n = WiFi.scanNetworks();
    Serial.print("SCANNED");
    Serial.println(n);
    //delay(1000);
    if (n>0)
    {
      _n = n;
      wifist ="";
      for (int i=0; i < n; ++i)
      {
        wifist+="<option value=\""+String(WiFi.SSID(i))+"\">"+String(WiFi.SSID(i))+"</option>";
        delay(10);
      }
    }
}


void ApMode(void)
{
  static bool ap = false;
  if (ap) return;
  ap = true;
  WiFi.disconnect();
  while (_n<=0) 
  {
    Serial.println("Scanning...");
    wifiScanString();
  }
  static long tim = millis();
  setDelay(1);
//  while (WiFi.status()==!WL_SCAN_COMPLETED);
  WiFi.begin(" "," ");
  delay(1000);
  WiFi.mode(WIFI_AP);
  String WFSSID = getData("deviceID");
  WFSSID.toUpperCase();
  ssid += WFSSID;
  WiFi.softAP(ssid.c_str(), pass.c_str());
  wifiReqHandle();
  wificfReqHandle();
  mqttcfReqHandle();
  mqttReqHandle();
  mainReqHandle();
  //dnsServer.start(53, "*", WiFi.softAPIP());
  //Aserver.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);

  
  Aserver.begin();
  
//----------------------------------------------  
  //Aserver.onNotFound(notFound);
  MDNS.addService("http", "tcp", 80);
 
  Serial.println("AP Mode");
  while (1)
  {
    dnsServer.processNextRequest();
    if (millis()-tim>300000) ESP.restart();
    //if (millis()%1000<5) Serial.println(".");
    //vTaskDelay(100/portTICK_PERIOD_MS);
  }
}
bool wifiInit(void)
{
  //WiFi.mode( WIFI_MODE_NULL );
  //delay(1000);
  unsigned long t= millis();
  WiFi.mode(WIFI_STA);
  WiFi.begin(getData("ssid").c_str(),getData("password").c_str());
  Serial.print("CONNECTING TO...");
  Serial.println(getData("ssid"));
  Serial.println(getData("password"));
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      //WiFi.begin(getData("ssid").c_str(),getData("password").c_str());
      Serial.print(".");
      if (millis()-t>120000) 
      {
        WiFi.disconnect();
        delay(100);
        wifiScanString();
        ApMode();
        return 0;
        break;     
      }
  }
  Serial.println();
  Serial.println("CONNECTED to: "+WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip.toString());
  if (!MDNS.begin(getData("deviceID").c_str())) return 0;
  
//----------------------------------------------
//HTTP Req Handle
  wificfReqHandle();
  wifiReqHandle();
  mqttcfReqHandle();
  mqttReqHandle();
  mainReqHandle();
  
//----------------------------------------------  
  //Aserver.onNotFound(notFound);
  Aserver.begin();
  MDNS.addService("http", "tcp", 80);
  changeData("ipaddress",ip.toString());
  return 1;
}
