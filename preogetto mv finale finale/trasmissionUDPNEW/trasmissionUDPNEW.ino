
/*this program sends udp packets to a connecting client*/
// author: gabrieleOrtolani
// DATE: 20/11/2022

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>




#ifndef STASSID
#define STASSID "FASTWEB-1-EDWWABMyi4Fl"
#define STAPSK  "3MGr9bSCD2"
#endif

MPU6050 mpu;

const int mpu_addr = 0x68;

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "ack\r\n";       // a string to send back


int16_t gx, gy, gz;
int16_t ax, ay, az;

int startPin = D2;
int DISARM = D3;


int dist, pwm;

int T,t, sampleTime, tConnection;

int connected = 0;
int packetSize;
int notConnected;


WiFiUDP Udp;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  mpu.initialize();

  pinMode(startPin, OUTPUT);
  pinMode(DISARM, INPUT);
  digitalWrite(startPin, LOW);  

    
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("...");
  }

  Udp.begin(localPort);
  Serial.print("Server started at IP ");
  Serial.println(WiFi.localIP());



  T = millis();
  sampleTime = 60; //milliseconds

  while(packetSize == 0) {
    packetSize = Udp.parsePacket();
  }
  connected = 1;
  digitalWrite(startPin, HIGH); 
  tConnection = millis(); 
}


void loop() {

  t = millis();

  if (Serial.available()>=sizeof(int)*2){
      dist = Serial.read();
      pwm = Serial.read();
  } 

    
  if((t-T)>=sampleTime){
    //Serial.println(t-T);
    char packetBuffer[128];


    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    snprintf(packetBuffer, sizeof(packetBuffer), "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%ld\t%d", ax, ay, az, gx, gy, gz, dist,(long)t-tConnection, pwm);
    
    
    if (connected) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(packetBuffer);
      Udp.endPacket();   
    }
    while(packetSize>0){
        packetSize = Udp.parsePacket();
    }
    packetSize=0;
    T = millis();
  }

}
