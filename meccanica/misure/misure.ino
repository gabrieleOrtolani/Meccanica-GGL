/**
 ******************************************************************************
 * @file    X_NUCLEO_IKS01A3_HelloWorld.ino
 * @author  SRA
 * @version V1.0.0
 * @date    February 2019
 * @brief   Arduino test application for the STMicrolectronics X-NUCLEO-IKS01A3
 *          MEMS Inertial and Environmental sensor expansion board.
 *          This application makes use of C++ classes obtained from the C
 *          components' drivers.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


// Includes
#include <LSM6DSOSensor.h>
#include <LIS2DW12Sensor.h>
#include <LIS2MDLSensor.h>
#include <LPS22HHSensor.h>
#include <STTS751Sensor.h>
#include <HTS221Sensor.h>
#include <Servo.h>

#ifdef ARDUINO_SAM_DUE
#define DEV_I2C Wire1
#elif defined(ARDUINO_ARCH_STM32)
#define DEV_I2C Wire
#elif defined(ARDUINO_ARCH_AVR)
#define DEV_I2C Wire
#else
#define DEV_I2C Wire
#endif
#define SerialPort Serial


// Components
LSM6DSOSensor AccGyr(&DEV_I2C);
LIS2DW12Sensor Acc2(&DEV_I2C);
LIS2MDLSensor Mag(&DEV_I2C);


//hc-sr04
#define trigPin 6
#define echoPin 7
#define pinAlimenta 8
long durata, cm;

// servo 
Servo servo;


//for comunication
int32_t data[2][3];

void setup() {
  // Led.
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize serial for output.
  SerialPort.begin(115200);
  //setting hcsr04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinAlimenta, OUTPUT);
  digitalWrite(pinAlimenta, HIGH);

  // Initialize I2C bus.
  DEV_I2C.begin();
  
  // setup acc ang gyr
  AccGyr.begin();
  AccGyr.Enable_X();
  AccGyr.Enable_G();
  Acc2.begin();
  Acc2.Enable_6D_Orientation();
  Acc2.Enable_X();
  Mag.begin();
  Mag.Enable();

  //servo
  servo.attach(3);

}
void loop2() {
  // Led blinking.
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
 // Serial.print("begin");


  // Read accelerometer and gyroscope.
  uint8_t xl;
  uint8_t xh;
  uint8_t yl;
  uint8_t yh;
  uint8_t zl;
  uint8_t zh;
  int32_t accelerometer[3];
  int32_t gyroscope[3];
  int8_t *orientation[2];
  AccGyr.Get_X_Axes(accelerometer);
  AccGyr.Get_G_Axes(gyroscope);
  AccGyr.Enable_6D_Orientation(*orientation[2]);
  
  Acc2.Get_6D_Orientation_XL(&xl);
  Acc2.Get_6D_Orientation_XH(&xh);
  Acc2.Get_6D_Orientation_YL(&yl);
  Acc2.Get_6D_Orientation_YH(&yh);
  Acc2.Get_6D_Orientation_ZL(&zl);
  Acc2.Get_6D_Orientation_ZH(&zh);


  AccGyr.Get_6D_Orientation_XL(&xl);
  AccGyr.Get_6D_Orientation_XH(&xh);
  AccGyr.Get_6D_Orientation_YL(&yl);
  AccGyr.Get_6D_Orientation_YH(&yh);
  AccGyr.Get_6D_Orientation_ZL(&zl);
  AccGyr.Get_6D_Orientation_ZH(&zh);

  // Output data.

  SerialPort.print(" | Acc[mg]: ");

  SerialPort.print(accelerometer[0]);
  SerialPort.print(",");


  SerialPort.print(accelerometer[1]);
  SerialPort.print(",");
  int value  = accelerometer[0];
  //digiservo(value);


  SerialPort.print(accelerometer[2]);
  SerialPort.print("; ");


  SerialPort.print(xl);
  SerialPort.print(",");

  SerialPort.print(xh);
  SerialPort.print(";");

  SerialPort.print(yl);
  SerialPort.print(",");

  SerialPort.print(yh);
  SerialPort.print(";");

  SerialPort.print(zl);
  SerialPort.print(",");

  SerialPort.print(zh);
  SerialPort.print("; ");

  
 
  SerialPort.print(gyroscope[0]);
  SerialPort.print(",");

  SerialPort.print(gyroscope[1]);
  SerialPort.print(",");  

  SerialPort.print(gyroscope[2]);
  SerialPort.print(";\n"); 

}

void digiservo(int val){
    val = map(val, 0,0,180,0);
    servo.write(val);
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
}


void hcsr04(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  durata = pulseIn(echoPin, HIGH);
  cm = durata / 58; // per i pollici la formula è durata / 148;
  SerialPort.print(cm);
  SerialPort.print(";\n");
}