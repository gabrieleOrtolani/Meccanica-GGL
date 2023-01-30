
/*this program sends udp packets to a connecting client*/
// author: gabrieleOrtolani && gabrieleiacovacci
// DATE: 20/12/2022

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "AutomazioneTesisti"
#define STAPSK  "nicosia456"
#endif
bool first_cicle = true;
unsigned int localPort = 8888;      // local port to listen on
int PIN_ENABLE_ARDUINO = 2;
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "ack\r\n";       // a string to send back
char* ip_a;


WiFiUDP Udp;

void setup() {
 // pinMode(PIN_ENABLE_ARDUINO, OUTPUT);
  digitalWrite(PIN_ENABLE_ARDUINO, LOW);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Udp.begin(localPort);


  Serial.print(WiFi.localIP());
  //delay(7000);
    


}

void loop() {
  
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    //digitalWrite(PIN_ENABLE_ARDUINO,HIGH);
    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    if (Serial.available() >= (7 * sizeof(int )) + sizeof(float) ) {
    // leggi 8 interi dalla seriale
      
      int val1 = Serial.read();//accX
      int val2 = Serial.read();//accY
      int val3 = Serial.read();//accZ
      int val4 = Serial.read();//gyrX
      int val5 = Serial.read();//gyrY
      int val6 = Serial.read();//gyrZ
      int val7 = Serial.read();//distanza
      float val0 = Serial.read();//tempo

      char data[32];
      //Serial.print(val0);
      /*preparo il pacchetto*/
      sprintf(data,"%d %d  %d  %d  %d  %d  %d  %f", val1, val2, val3, val4, val5, val6, val7, val0);
      Udp.write(data);
      Serial.println(data);
      
      Udp.endPacket();
    
  }
  }
  
}
