#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

const char ssid[] = "SRC 24G";        // your network SSID (name)
const char pass[] = "src@internet";   // your network password

int statusCode = 0;

unsigned long lastTime = 0;
unsigned long timerDelay = 16000;

WiFiClient  client;

//---------READ Channel Details---------//
unsigned long counterChannelNumber =  256260;            // Channel ID
const char * myCounterReadAPIKey = "LONYHGWF45SQPAZ9"; // Read API Key
const int FieldNumber1 = 1;

//---------WRITE Channel Details---------//
unsigned long myChannelNumber = 258107;
const char * myWriteAPIKey = "YG38R9PND90YE66S";
String strs[8]={"0","0","0","0","0","0","0","0"};
int StringCount = 0;
int prv=0;
void setup()
{
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  Serial.begin(9600);

  delay(1000);
}

void loop()
{
  //----------------- Network -----------------//
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    //Serial.print(ssid);
    delay(1000);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Conn.. to Wi-Fi");
    Serial.println("Succesfully.");
    
    
  }
 
  //---------------- Channel 1 ----------------//
  int temp = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    if(temp !=prv)
    {
    Serial.write(temp);
    prv=temp;
    }
  }
  
  delay(100);
  
//
if (Serial.available()) 
{
String rcv = Serial.readStringUntil('\n');

if ((millis() - lastTime) > timerDelay) 
{

   StringCount=0;
     while (rcv.length() > 0)
  {
    int index = rcv.indexOf(',');
    if (index == -1) // No space found
    {
      strs[StringCount++] = rcv;
      break;
    }
    else
    {
      strs[StringCount++] = rcv.substring(0, index);
      rcv = rcv.substring(index+1);
    }
  }
    
 ThingSpeak.setField(1, strs[0]);
 ThingSpeak.setField(2, strs[1]);
 ThingSpeak.setField(3, strs[2]);
 ThingSpeak.setField(4, strs[3]);
 ThingSpeak.setField(5, strs[4]);
 ThingSpeak.setField(6, strs[5]);
 ThingSpeak.setField(7, strs[6]);
 ThingSpeak.setField(8, strs[7]);
 int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
 if(x == 200){
  delay(10);
  }
else{
  delay(10);
  }
  lastTime = millis();
 }
 
}
  delay(1000);
 
}


 
