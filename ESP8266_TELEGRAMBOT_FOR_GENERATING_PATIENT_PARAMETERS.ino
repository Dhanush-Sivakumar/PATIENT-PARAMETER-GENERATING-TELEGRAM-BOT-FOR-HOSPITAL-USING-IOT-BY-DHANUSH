#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>
#include "DHT.h"
#define DHTPIN 4 
#define DHTTYPE DHT11  

const char* ssid = "DHANUSH";
const char* password = "DHANUSH";

#define BOTtoken "7197022155:AAFSmM09XqZy16Nt9WFe2epvvj-G6hAqn-c"  


#define CHAT_ID "1595272548"


#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
DHT dht(DHTPIN, DHTTYPE);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;




void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
   
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
   
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

      if (text == "/start")
      {
        String welcome = "DS hospital parameter generator\n";
        welcome += "/1 : PATIENT 1 \n";
        welcome += "/2 : PATIENT 2 \n";
        welcome += "/3 : PATIENT 3 \n";
        welcome += "/4 : PATIENT 4 \n";
        welcome += "/5 : PATIENT 5 \n";
        bot.sendMessage(chat_id, welcome, "Markdown");
      }
      if (text == "/1")
      {   
          String msg = "TOKEN : 1 \nTemperature is ";
          msg += msg.concat(temperatureC);
          msg += " C\n";
          msg += "Humidity is ";
          msg += msg.concat(humidity);
          msg +=" %\n";
          msg += "Heart Rate is ";
          msg += msg.concat(bpm);
          msg +=" BPM\n";
          bot.sendMessage(chat_id,msg, ""); 
         
      }
      if (text == "/2")
      {  
         
          String msg = "TOKEN : 2 \nTemperature is ";
          msg += msg.concat(temperatureC);
          msg += " C\n";
          msg += "Humidity is ";
          msg += msg.concat(humidity);
          msg +=" %\n";
          msg += "Heart Rate is ";
          msg += msg.concat(bpm);
           msg +=" BPM\n";
          bot.sendMessage(chat_id,msg, ""); 
          
      }
      if (text == "/3")
      {  
          
          String msg = "TOKEN : 3 \nTemperature is ";
          msg += msg.concat(temperatureC);
          msg += " C\n";
          msg += "Humidity is ";
          msg += msg.concat(humidity);
          msg +=" %\n";
          msg += "Heart Rate is ";
          msg += msg.concat(bpm);
           msg +=" BPM\n";
          bot.sendMessage(chat_id,msg, ""); 
         
      }
      if (text == "/4")
      {  
          
          String msg = "TOKEN : 4 \nTemperature is ";
          msg += msg.concat(temperatureC);
          msg += " C\n";
          msg += "Humidity is ";
          msg += msg.concat(humidity);
          msg +=" %\n";
          msg += "Heart Rate is ";
          msg += msg.concat(bpm);
           msg +=" BPM\n";
          bot.sendMessage(chat_id,msg, ""); 
         
      }
      if (text == "/5")
      {  
         
          String msg = "TOKEN : 5 \nTemperature is ";
          msg += msg.concat(temperatureC);
          msg += " C\n";
          msg += "Humidity is ";
          msg += msg.concat(humidity);
          msg +=" %\n";
          msg += "Heart Rate is ";
          msg += msg.concat(bpm);
           msg +=" BPM\n";
          bot.sendMessage(chat_id,msg, "");
        
      }

    
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");     
    client.setTrustAnchors(&cert); 
  #endif

  
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
