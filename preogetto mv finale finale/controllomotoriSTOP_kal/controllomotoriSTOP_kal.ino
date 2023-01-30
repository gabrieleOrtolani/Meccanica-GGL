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

int START = 2;


//distance variables
long initDist;
long curDist;
long prevDist;
long val2Set;
bool discard;
long rawDist;
float filterValue;
int maxSpeed;
int minSpeed;
int breakDist;
double kalDist;

char a[2];
int t;



void setup() {

  Serial.begin(9600);

  maxSpeed=255;
  minSpeed=0;
  breakDist = 16;

  // put your setup code here, to run once:ù
  pinMode(enD, OUTPUT);
  pinMode(fwD, OUTPUT);
  pinMode(bwD, OUTPUT);

  pinMode(enS, OUTPUT);
  pinMode(fwS, OUTPUT);
  pinMode(bwS, OUTPUT);
  pinMode(in,  INPUT);
  pinMode(out, OUTPUT);

  pinMode(START, INPUT);

  pinMode(buzz, OUTPUT);



  lcd.begin(16,2);


  while(digitalRead(START)==HIGH){
    lcd.print("wait...");
    delay(100);
    lcd.clear();
  }
  rawDist = hcsr04();

  while(digitalRead(START)==LOW){
    lcd.print("wait...");
    delay(100);
    curDist = hcsr04();
    Serial.write(curDist);
    Serial.write(val2Set);
    lcd.clear();
  }

  lcd.print("start");
  delay(1000);
  lcd.clear();

  //Scriviamo velocità:
  lcd.setCursor(0,0);
  lcd.print("PWM: ");
  lcd.print(" ");

  lcd.setCursor(0,1);
  lcd.print("Dist: ");


 // Serial.println(initDist);
  rawDist = hcsr04();
  prevDist = rawDist;

}

void loop() {

  discard = false;
  rawDist = hcsr04();
  t = millis();

  curDist = rawDist;
  Serial.write(curDist);
  Serial.write(val2Set);

  //chosing value for PWM
    if (curDist>initDist) {   
      digitalWrite(buzz, LOW);
      initDist = curDist;
    }else if (curDist<breakDist){      
      val2Set = (long) minSpeed;
      if (digitalRead(START)==HIGH){ beep_f();}
      else{ digitalWrite(buzz, LOW);}

    }else if(curDist>=breakDist){
      digitalWrite(buzz, LOW);
      if (val2Set<maxSpeed) val2Set+=5;  
    }
    constrain(val2Set,minSpeed,maxSpeed);

    //actuate PWM
    if (val2Set>=0){
      digitalWrite(fwD, HIGH);
      digitalWrite(bwD, LOW);
      digitalWrite(fwS, HIGH);
      digitalWrite(bwS, LOW);

    }else{
      val2Set = abs(val2Set);
      digitalWrite(bwD, HIGH);
      digitalWrite(bwS, HIGH);
      digitalWrite(fwD, LOW);
      digitalWrite(fwS, LOW);    
    }


    if(digitalRead(START)== HIGH){
      analogWrite(enD,val2Set);
      analogWrite(enS,val2Set);      
    }

    printPwm(val2Set);
    printDistance(curDist);
    
    if (t%100 == 0){
        clearVariable(6,0);
        clearVariable(7,0);
        clearVariable(6,1);
        clearVariable(7,1);
    }

  

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
    kalDist = kalman((double)tocm);
    

    return (long)kalDist;
}

double kalman(double U){
  static const double R = 40;
  static const double H = 1.00;
  static double Q = 10;
  static double P = 0;
  static double U_hat = 0;
  static double K = 0;
  K = P*H/(H*P*H+R);
  U_hat += + K*(U-H*U_hat);
  P = (1-K*H)*P+Q;
  return U_hat;
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

void beep_f(){
    if (beep%6 == 0){
        digitalWrite(buzz, LOW);
    }else if (beep%3 == 0){
        digitalWrite(buzz, HIGH);
    }
    beep++;
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





