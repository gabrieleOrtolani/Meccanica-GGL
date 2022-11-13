
// Includes
#include <LSM6DSOSensor.h>
#include <LIS2DW12Sensor.h>
#include <LIS2MDLSensor.h>
#include <LPS22HHSensor.h>
#include <STTS751Sensor.h>
#include <HTS221Sensor.h>
#include <Servo.h>
#include <math.h>

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
float roll, pitch, yaw;
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
void loop() {
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
  pitch = 180 * atan (accelerometer[0]/sqrt(accelerometer[1]*accelerometer[1] +accelerometer[2]*accelerometer[2]))/M_PI;
  roll = 180 * atan (accelerometer[1]/sqrt(accelerometer[0]*accelerometer[0] + accelerometer[2]*accelerometer[2]))/M_PI;
  yaw = 180 * atan (accelerometer[2]/sqrt(accelerometer[0]*accelerometer[0] + accelerometer[2]*accelerometer[2]))/M_PI;

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
  SerialPort.print(";"); 
   
  SerialPort.print(roll);
  SerialPort.print(",");

  SerialPort.print(pitch);
  SerialPort.print(",");  

  SerialPort.print(yaw);
  SerialPort.print(";\n"); 

}

void digiservo(int val){
    val = map(val, 0,0,180,0);
    servo.write(val);
}


void loop2(){

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