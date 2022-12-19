#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

int val;

unsigned int localPort = 8080;     
char n[256];

char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "Check the led on the board\n";       // a string to send back
WiFiUDP Udp;
int i = 0;

// Network SSID
const char* ssid = "FASTWEB-1-EDWWABMyi4Fl";
const char* password = "3MGr9bSCD2";
int check;




void setup() {
  Serial.begin(9600);


  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  //WiFi.hostname("ard") ;
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
 
  while (WiFi.status() != WL_CONNECTED) {
    i++;
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.printf("\nUDP server on port %d\n", localPort);
  Udp.begin(localPort);
  
}
 
void loop() {
  Serial.read(n,256);
  Serial.print(n);
  Serial.write("a",1);
  if(check= Udp.parsePacket()){
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Serial.read(n,256);
    Serial.print(n);
    
    Udp.write(n);
    memset(n,0,256);
    
    Udp.endPacket();
  }

  }
