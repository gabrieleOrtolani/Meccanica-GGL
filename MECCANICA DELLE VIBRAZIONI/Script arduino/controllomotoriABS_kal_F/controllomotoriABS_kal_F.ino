//Vibration Mechanics - Arduino Project by
//G. Ortolani, L. Grande, G. Iacovacci

// Include Wire Library for I2C
#include <Wire.h>

// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <MPU6050.h>

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
int16_t Acx, Acy,Acz, temp, Gyx, Gyy, Gyz;

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

//right motor
int enD = 9;
int fwD = 8; //avanti DX
int bwD = 7; //indietro DX

//left motor
int enS = 3;
int fwS = 4; //avanti SX
int bwS = 5; //indietro SX


//Wemos pin
int START = 2;

//distance variables
long initDist;
long curDist;
long val2Set;
long rawDist;
double kalDist;

//speed variables
int maxSpeed;
int minSpeed;
int breakDist;

int t;

void setup() {
  Serial.begin(9600);

  //change these parameters to create a new experiment
  maxSpeed=255;
  minSpeed=0;
  breakDist=40;

  //motor pins
  pinMode(enD, OUTPUT);
  pinMode(fwD, OUTPUT);
  pinMode(bwD, OUTPUT);
  pinMode(enS, OUTPUT);
  pinMode(fwS, OUTPUT);
  pinMode(bwS, OUTPUT);

  //hcsr04's pins
  pinMode(in,  INPUT);
  pinMode(out, OUTPUT);

  //Wemos pin 
  pinMode(START, INPUT);

  //buzzer pin
  pinMode(buzz, OUTPUT);

  //first wait Wemos D1 is on 
  lcd.begin(16,2);
  while(digitalRead(START)==HIGH){
    lcd.print("wait...");
    delay(100);
    lcd.clear();
  }
  
  //wait client is connected to Wemos D1
  while(digitalRead(START)==LOW){
    lcd.print("wait...");
    delay(100);
    rawDist = hcsr04();   //take some mesuraments while wainting so the kalman filter works the best
    Serial.write(rawDist);
    Serial.write(val2Set);
    lcd.clear();
  }

  //client connected
  lcd.print("start!!!");
  delay(1000);
  lcd.clear();
  
  //print PWM and distance on LCD
  lcd.setCursor(0,0);
  lcd.print("PWM: ");
  lcd.print(" ");
  lcd.setCursor(0,1);
  lcd.print("Dist: ");
}

void loop() {
  t = millis();

  //sending the PWM and the distance through the serial TX RX to the Wemos D1
  curDist = hcsr04();
  Serial.write(curDist);
  Serial.write(val2Set);

  //chosing PWM value
  if (curDist>breakDist){   
    //ramp reference to accelerate
    digitalWrite(buzz, LOW);
    if (val2Set<maxSpeed) val2Set+=5;

  }else if (curDist<15){
    //if a safe distance is exceeded make the buzzer beep 
    beep_f();
    //PWM set to zero
    val2Set = 0;

  }else if(curDist<=breakDist){
    //adjust PWM depending on the distance
    digitalWrite(buzz, LOW);
    val2Set = map(curDist, (long)15, (long)breakDist,(long)35,(long)maxSpeed);
  }

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

  //enable both motors
  if(digitalRead(START)== HIGH){
    analogWrite(enD,val2Set);
    analogWrite(enS,val2Set);      
  }    

  //display on LCD screen
  printPwm(val2Set);
  printDistance(curDist);
  
  //clearing the screen
  if (t%100 == 0){
      clearVariable(6,0);
      clearVariable(7,0);
      clearVariable(6,1);
      clearVariable(7,1);
  }
}

//hcsr04 funciont with an 
long hcsr04(){
  digitalWrite(out,LOW);
  delayMicroseconds(2);
  digitalWrite(out,HIGH);
  delayMicroseconds(10);
  digitalWrite(out,LOW);
  dur=pulseIn(in,HIGH);

  //convert ms to cm
  tocm=microsecondsToCentimeters(dur);

  //using kalman filter to adjust distance
  kalDist = kalman((double)tocm);

  return (long)kalDist;
}

double kalman(double U){
  //using static variables to allocate permanently in this function
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

//conversion from seconds to centimeters for an ultrasonic pulse
long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

//clearing LCD buffer
void clearVariable(int i, int j){
  lcd.setCursor(i, j);
  lcd.print("          ");
}

//print the PWM on LCD screen
void printPwm(int pwm_value){
  lcd.setCursor(6, 0);
  lcd.print(pwm_value);
}

//print the distance on LCD screen
void printDistance(int distance_value){
  lcd.setCursor(6, 1);
  lcd.print(distance_value);
}

//repetitive calls to this f. will make the buzzer beep
void beep_f(){
  int span = 10;
    if (beep%span == 0){
        digitalWrite(buzz, LOW);
    }else if (beep%(span/2) == 0){
        digitalWrite(buzz, HIGH);
    }
    beep++;
}
