
/*this program sends udp packets to a connecting client*/
// author: gabrieleOrtolani
// DATE: 20/11/2022

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "yourSSID"
#define STAPSK  "wireless key"
#endif

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "ack\r\n";       // a string to send back

WiFiUDP Udp;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    //Serial.println(packetBuffer);

      // send a reply, to the IP address and port that sent us the packet we received
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  if (Serial.available() >= 6 * sizeof(int)) {
    // leggi 6 interi dalla seriale
      int val1 = Serial.read();
      int val2 = Serial.read();
      int val3 = Serial.read();
      int val4 = Serial.read();
      int val5 = Serial.read();
      int val6 = Serial.read();
      int val7 = Serial.read();

      char data[32];
      Serial.print(val1);
      sprintf(data, "%d,%d,%d;%d,%d,%d,%d;", val1, val2, val3, val4, val5, val6, val7);
      Serial.println(data);
      Udp.write(data);
      Udp.endPacket();
    
  }
  }
}
