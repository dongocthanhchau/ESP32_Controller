

#include "wifi.h"
#include "blynk.h"
#include "mqtt.h"
#include "NTPClock.h"
#include "config.h"
#include "devices.h"
#include "json.h"
#include <WiFi.h>



#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// define tasks
void TaskBlink( void *pvParameters );
void TaskCountdown( void *pvParameters );
void TaskWifi( void *pvParameters );
void TaskButton( void *pvParameters );
void TaskReport( void *pvParameters );

TaskHandle_t TaskHandleCountdown;
TaskHandle_t TaskHandleWifi;
TaskHandle_t TaskHandleBlink;
TaskHandle_t TaskHandleReport;


void setup() {
  spiffBegin();
  disableCore0WDT();
  disableCore1WDT();
  disableLoopWDT();
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
    setDelay(100);
    xTaskCreatePinnedToCore(
    TaskBlink
    ,  "Blink"   
    ,  1024  
    ,  NULL
    ,  0  
    ,  &TaskHandleBlink 
    ,  0);
  xTaskCreatePinnedToCore(
    TaskButton
    ,  "Button"
    ,  2048  
    ,  NULL
    ,  0  
    ,  NULL 
    ,  0);
  //disableCore0WDT();
  //disableCore1WDT();
  // Setup Task

  
  //////////
  xTaskCreatePinnedToCore(
    TaskCountdown
    ,  "Countdown"   
    ,  20480  
    ,  NULL
    ,  0 
    ,  &TaskHandleCountdown 
    ,  0);
  
  
  
Serial.println("Button Done");
  
  
}

void loop()
{
  // Empty. Things are done in Tasks.
//  if (millis()>43199997)
//    {
//      Serial.println("IT'S "+getTime());
//      Serial.println("RESETTING, PLEASE WAIT...");
//      ESP.restart();
//    }

   vTaskDelay(10000/portTICK_PERIOD_MS);
   String state = "{\"status\":\"Running\",\"deiveID\": " + getData("deviceID") +",\"wifi\":{\"SSID\": \""+getData("ssid")+"\",\"LocalIP\":"+ getData("ipaddress") +" } ,\"time\":" +  getTime() +",\"runtime\":" + String(millis()) +"}";
   String sttTopic = getData("status");
   sttTopic.replace("%%ID%%",getData("deviceID"));
   publishData(sttTopic.c_str(),state.c_str());
   reconnect();
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(WIFI_LED, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    blinkLed(WIFI_LED);   
    vTaskDelay(getDelay());  
  }
}

void TaskWifi(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  NTPInit();
  unsigned long t=0;
  for (;;)
  {
    MQTTloop();
    vTaskDelay(1/portTICK_PERIOD_MS);
//    
//    //Nothing Here
    if (WiFi.status() != WL_CONNECTED) t = millis();
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      setDelay(100);
      WiFi.disconnect();
      WiFi.begin();
      Serial.println("WIFI");
      if (millis()-t>30000) ESP.restart();
    }
  }
}
void TaskCountdown(void *pvParameters)
{
  (void) pvParameters;
  if (wifiInit())
  {
    setDelay(1000);
    Serial.println("WIFI Done");
    MQTTsetup();
  }
  else
  {
    setDelay(5000);
    Serial.println("WIFI Fail"); 
    while(1);
  }
  deviceInit();
  xTaskCreatePinnedToCore(
    TaskReport
    ,  "ReportData"   
    ,  20480  
    ,  NULL
    ,  0 
    ,  &TaskHandleReport 
    ,  0);
  xTaskCreatePinnedToCore(
    TaskWifi
    ,  "Wifi"
    ,  40960  
    ,  NULL
    ,  3 
    ,  &TaskHandleWifi 
    ,  1);
  for (;;)
  {
     countdown();
     vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void TaskReport(void *pvParameters)
{
  (void) pvParameters;
  //String resTopic = "/CON/CON0001/result";//
  for (;;)
  {
    String resTopic = getData("result");
    resTopic.replace("%%ID%%",getData("deviceID"));
    String jsonData;
    jsonData = jsonSerialize(getPin(1),getTime(1),getPin(2),getTime(2),getPin(3),getTime(3),getPin(4),getTime(4),getPin(5),getTime(5),getPin(6),getTime(6),getPin(7),getTime(7),getPin(8),getTime(8));
    publishData(resTopic.c_str(),jsonData.c_str());
    vTaskDelay(2000/portTICK_PERIOD_MS);
  }
}
///do the click button task again
void TaskButton(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  unsigned long t;
  t = millis();
  pinMode(BUTTON,INPUT_PULLUP);
  for(;;){
    if(digitalRead(BUTTON)){
      t = millis();
//      Serial.println("BUTTON");
    }
      vTaskDelay(1000/portTICK_PERIOD_MS);
//    if (millis() - t >8000){
//      //WiFi.disconnect();
//      wifiScanString();
//    }
    if (millis() - t > 10000){
      Serial.println("GOING AP:");
      vTaskDelete(TaskHandleCountdown);
      //vTaskDelete(TaskHandleWifi);
      //vTaskDelete(TaskHandleReport);

      ApMode();
    }
  }
  
//  pinMode(BUTTON, INPUT_PULLUP);
//  int t=-1;
//  for (;;) // A Task shall never return or exit.
//  {
//    //Serial.println(analogRead(BUTTON));
//    if (millis()>10000) {
//    if (analogRead(BUTTON)<5)
//    { 
//    t-=-1;
//    }else t=-1;
//    }
//    vTaskDelay(10/portTICK_PERIOD_MS);
//    if (t==RESET_TIME*100) {
//      wifiScanString();
//      
//      Serial.println("SHORT CLICK");
//    }
//    if ((t==RESET_TIME*160))
//    {
//      WiFi.disconnect();
//      //WiFi.begin(" "," ");
//      
//      //delay(1000);
//      wifiScanString();
//    }
//    if (t>RESET_TIME*200) 
//    {
//      Serial.println("LONG CLICK");
//      WiFi.begin(" "," ");
//      //WiFi.disconnect();
//      delay(1000);
//      wifiScanString();
//      ApMode();
//      t=-1;
//      setDelay(100);
//      vTaskDelay(100000/portTICK_PERIOD_MS);
//    }
    
//    else if (t>10) 
//    {
//      Serial.println("SHORT CLICK");
//      //Do Something
//    }
    
//  }
}
