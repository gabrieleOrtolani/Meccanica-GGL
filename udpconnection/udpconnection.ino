#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

unsigned int localPort = 4444;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "Check the led on the board\n";       // a string to send back
WiFiUDP Udp;

// Network SSID
const char* ssid = "TIM-23323992_AP";
const char* password = "Ilaria1970..";
 
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
 
  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  //WiFi.hostname("ard") ;
  WiFi.begin(ssid, password);

  int i = 0;
  Serial.print("Connecting");
 
  while (WiFi.status() != WL_CONNECTED) {
    if(i%6==0){
      digitalWrite(LED_BUILTIN, LOW);    
    }else if(i%6==3){
      digitalWrite(LED_BUILTIN, HIGH);    
    }
    i++;
    delay(100);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.printf("\nUDP server on port %d\n", localPort);
  Udp.begin(localPort);
  
}
 
void loop() {
  int check= Udp.parsePacket();
  if(check){
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    //Serial.println(packetBuffer);

    if(strcmp(packetBuffer,"1")==0){//\n modify and 10
      digitalWrite(LED_BUILTIN, LOW);
    }
    else if(strcmp(packetBuffer,"0")==0){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }

  }
