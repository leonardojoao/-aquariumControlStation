#include <ESP8266WiFi.h>

#include <NTPClient.h>
#include <WiFiUdp.h>
 
const char* ssid     = "VIVO-FB2C";
const char* password = "33D77EFB2C";     

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

int wifiStatus;

void setup() {
  pinMode(D6,OUTPUT);

  Serial.begin(115200);
  delay(200);

  // Iniciar ligação à rede
  Serial.print("A ligar à rede ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(-10800);
}   
 
void loop() {
  
  wifiStatus = WiFi.status();

  if(wifiStatus == WL_CONNECTED){
    Serial.println("");
    Serial.println("O seu nodeMCU está ligado!");  
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    timeClient.update();

    int currentHour = timeClient.getHours();
    Serial.print("Hour: ");
    Serial.println(currentHour); 
    
    int currentMinute = timeClient.getMinutes();
    Serial.print("Minutes: ");
    Serial.println(currentMinute); 

    if (currentHour > 10 && currentHour < 15) {
      analogWrite(D6,900);
    }else{
      analogWrite(D6,0);
    }
          
  }else{
    Serial.println("");
    Serial.println("Upsss...o seu nodeMCU não se consegue ligar...");
  }
  delay(1000); 
}

//https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/
