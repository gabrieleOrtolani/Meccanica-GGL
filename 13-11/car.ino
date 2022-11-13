
//#include <Servo.h>          //standard library for the servo
//#include <NewPing.h>        //for the Ultrasonic sensor function library.

#include <LSM6DSOSensor.h>
#include <LIS2DW12Sensor.h>
#include <LIS2MDLSensor.h>
#include <LPS22HHSensor.h>
#include <STTS751Sensor.h>
#include <HTS221Sensor.h>
//L298N motor control pins
#define LeftMotorForward 2
 #define LeftMotorBackward 3
 #define RightMotorForward 5
 #define RightMotorBackward 4

#define DEV_I2C Wire

LSM6DSOSensor AccGyr(&DEV_I2C);
LIS2DW12Sensor Acc2(&DEV_I2C);
LIS2MDLSensor Mag(&DEV_I2C);

int32_t data[2][3];

//Servo servo_motor; 

void setup(){
  Serial.begin(115200);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);


  //Serial.begin(115200);
  //servo_motor.attach(9); //our servo pin
  DEV_I2C.begin();
  AccGyr.begin();
  AccGyr.Enable_X();
  AccGyr.Enable_G();
}

void loop(){


  AccGyr.Get_X_Axes(data[0]);
  AccGyr.Get_G_Axes(data[1]);

  for(int i = 0; i<2; i++){
    for(int j = 0; j<3; j++){
      Serial.print(data[i][j], DEC);
      if(j<2){
        Serial.write(",",1);
        }
    }
    Serial.write(";",1);
  }
  Serial.write("\n",1);
  delay(10);

  analogWrite(RightMotorForward, 55);
  analogWrite(LeftMotorForward, 155);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);

  
}

