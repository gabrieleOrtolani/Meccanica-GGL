// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <MPU6050.h>
// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
int16_t AcGyx, AcGyy,AcGyz;

MPU6050 mpu;
// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;
const int mpu_addr = 0x68;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
int thisChar;
int pwm, distance;

//hcsr04 variables
long dur;
long dis;
long tocm;
int in= 12;
int out= 13;

//buzzer 
int buzz = 11;
long beep;


//motore destro
int enD = 9;
int fwD = 8; //avanti DX
int bwD = 7; //indietro DX

//motore sinistro
int enS = 3;
int fwS = 4; //avanti SX
int bwS = 5; //indietro SX


long initDist;
long curDist;
long prevDist;
long val2Set;
bool discard;

char a[2];
int t;

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:ù
  pinMode(enD, OUTPUT);
  pinMode(fwD, OUTPUT);
  pinMode(bwD, OUTPUT);

  pinMode(enS, OUTPUT);
  pinMode(fwS, OUTPUT);
  pinMode(bwS, OUTPUT);
  pinMode(in,  INPUT);
  pinMode(out, OUTPUT);


  pinMode(buzz, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(mpu_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  lcd.begin(16,2);
  // Print on first row


  lcd.print("start");
  delay(1000);
  lcd.clear();
  //Scriviamo velocità:
  lcd.setCursor(0,0);
  lcd.print("PWM: ");
  lcd.print(" ");

  lcd.setCursor(0,1);
  lcd.print("Dist: ");


  initDist = 35;//hcsr04();
  Serial.println(initDist);
  curDist = initDist;
  prevDist = curDist;
  val2Set = 0;
  digitalWrite(fwD, HIGH);
  digitalWrite(bwD, LOW);
  digitalWrite(fwS, HIGH);
  digitalWrite(bwS, LOW);
  delay(2000);

}

void loop() {

  Wire.beginTransmission(mpu_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(mpu_addr, 14, true); // request a total of 14 registers

  AcGyx = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcGyy = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcGyz = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  //AcGy[1][0] = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  //AcGy[1][1] = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  //AcGy[1][2] = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  
  //for(int i = 0; i<1; i++){
  //  for(int j = 0; j<3; j++){

  Serial.print(AcGyx, DEC);
  Serial.write(",",1);
  Serial.print(AcGyy, DEC);
  Serial.write(",",1);
  Serial.print(AcGyz, DEC);
  Serial.write(";\n",2);
/*
  while(1){
    a[0] = Serial.read();
    if(strcmp(a,"a")){
      //Serial.println(a);
      break;}
  }
*/

  discard = false;
  curDist = hcsr04();
  t = millis();

  if((curDist - prevDist)>50){
    discard = true;
  }else{
    prevDist = curDist ;
  }

  if (!discard){
    if (curDist>initDist) {   
      digitalWrite(buzz, LOW);
      if (val2Set<220) val2Set +=2; 

      analogWrite(enD,val2Set);
      analogWrite(enS,val2Set);
      
    }else if (curDist<=initDist){
      val2Set = (long) 0;
      if (beep%6 == 0){
        digitalWrite(buzz, LOW);
      }else if (beep%3 == 0){
        digitalWrite(buzz, HIGH);
      }
      beep++;
    }


  




    //Serial.println(curDist);  
    //Serial.println(val2Set);
    printPwm(val2Set);
    printDistance(curDist);
    
    if (t%100 == 0){
        clearVariable(6,0);
        clearVariable(6,1);
    }

  }
  //delay(1000);
}


long hcsr04(){
    digitalWrite(out,LOW);
    delayMicroseconds(2);
    digitalWrite(out,HIGH);
    delayMicroseconds(10);
    digitalWrite(out,LOW);
    dur=pulseIn(in,HIGH);
    tocm=microsecondsToCentimeters(dur);
    //Serial.println(String(tocm));

    return tocm;
}


long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

//Function that clear the variable at row i and column j --> assume that variable is in range[0, 254];
void clearVariable(int i, int j){
  lcd.setCursor(i, j);
  lcd.print("          ");
}

void printPwm(int pwm_value){
  lcd.setCursor(6, 0);
  lcd.print(pwm_value);
}


void printDistance(int distance_value){
  lcd.setCursor(6, 1);
  lcd.print(distance_value);
}



















void prova1(){
  // accendo motore destra
  digitalWrite(fwD, HIGH);
  digitalWrite(bwD, LOW);

  //setto la velocità su scala 255
  int speedD  = 150; //velocità motore destro
  analogWrite(enD,speedD);

  // accendo motore sinistro
  digitalWrite(fwS, HIGH);
  digitalWrite(bwS, LOW);

  //setto la velocità su scala 255
  int speedS  = speedD; //velocità motore sinistro
  analogWrite(enD,speedS);
  
  delay(3000);
  

  //inverto senso
  digitalWrite(fwD, LOW);
  digitalWrite(bwD, HIGH);
  digitalWrite(fwS, LOW);
  digitalWrite(bwS, HIGH);

  delay(3000);

  
  //spengo i motori
  digitalWrite(fwD, LOW);
  digitalWrite(bwD, LOW);
  digitalWrite(fwS, LOW);
  digitalWrite(bwS, LOW);

}

void prova2(){

  //accendo i motori
  digitalWrite(fwD, LOW);
  digitalWrite(bwD, HIGH);
  //digitalWrite(fwS, LOW);
  //digitalWrite(bwS, HIGH);

  //accelero da 0 al massimo
  for(int i = 0; i< 256; i++){
    analogWrite(enD,i);
    //analogWrite(enS,i);
    Serial.println(i);
    delay(20);
  }

  Serial.println("top speed");
  delay(200);

  //decelero dal massimo fino a zero
  for(int i = 255; i >= 0; --i){
    analogWrite(enD,i);
    //analogWrite(enS,i);
    Serial.println(i);
    delay(20);
  }

  //spengo i motori
  digitalWrite(fwD, LOW);
  digitalWrite(bwD, LOW);
  digitalWrite(fwS, LOW);
  digitalWrite(bwS, LOW);

}




