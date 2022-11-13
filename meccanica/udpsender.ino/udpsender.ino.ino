#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

char n[256];

//connection variables
unsigned int localPort = 8080;      // local port to listen on
const char* ssid = "FASTWEB-1-EDWWABMyi4Fl";
const char* password = "3MGr9bSCD2";
WiFiUDP Udp;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "Check the led on the board\n";       // a string to send back
int  packetSize;

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  //WiFi.hostname("ard") ;
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  
  int i = 0;
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

  Serial.println("WiFi connected");

  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.printf("\nUDP server on port %d\n", localPort);
  Udp.begin(localPort);

  int check = 0;
  while(check==0){
    check= Udp.parsePacket();
  }
  Serial.print("begin data transfer");
}

void loop() {
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

  Serial.read(n,256); //Read the serial data and store in var
  Serial.print(n); //Print data on Serial Monitor


  Udp.write(n);
  memset(n,0,256);
  delay(10);
  Udp.endPacket();


}
