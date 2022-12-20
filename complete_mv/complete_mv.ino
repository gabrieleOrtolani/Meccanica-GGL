
#include <Wire.h>
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
  digitalWrite(fwD, HIGH);
  digitalWrite(bwD, LOW);
  digitalWrite(fwS, HIGH);
  digitalWrite(bwS, LOW);
  delay(2000);   //--------> da ricontrollare

}

void loop() {

  Wire.beginTransmission(mpu_addr);
  Wire.write(0x3B);  // inizia la trasmissione dei dati del sensore
  Wire.endTransmission(false);
  Wire.requestFrom(mpu_addr, 14, true); // richiedi 14 byte di dati
  val1 = Wire.read() << 8 | Wire.read(); // acclerometro asse X
  val2 = Wire.read() << 8 | Wire.read(); // acclerometro asse Y
  val3 = Wire.read() << 8 | Wire.read(); // acclerometro asse Z
  Tmp = Wire.read() << 8 | Wire.read(); // temperatura
  val4 = Wire.read() << 8 | Wire.read(); // giroscopio asse X
  val5 = Wire.read() << 8 | Wire.read(); // giroscopio asse Y
  val6 = Wire.read() << 8 | Wire.read(); // giroscopio asse Z

  discard = false;
  curDist = hcsr04();
  t = millis();
//invio pacchetti dati con 6 valori
  Serial.print(val1, DEC);// acclerometro asse X
  Serial.print(val2, DEC);// acclerometro asse Y
  Serial.print(val3, DEC);// acclerometro asse Z
  Serial.print(val4, DEC);// giroscopio asse X
  Serial.print(val5, DEC);// giroscopio asse Y
  Serial.print(val6, DEC);// giroscopio asse Z
  Serial.print(curDist,DEC)// distanza  
  Serial.println("Valori inviati sulla seriale!");
  //forse il valore che ho misurato non è coerente con la media delle misure
  if((curDist - prevDist)>50){
    discard = true;
  }else{
    prevDist = curDist ;
  }
  if (!discard){
    if (curDist>initDist) {   
      digitalWrite(buzz, LOW);
      if (val2Set<180) val2Set +=10; 
    }else if (curDist<20){
      val2Set = (long) 0;
      if (beep%6 == 0){
        digitalWrite(buzz, LOW);
      }else if (beep%3 == 0){
        digitalWrite(buzz, HIGH);
      }
      beep++;

    }else if(curDist<=initDist){
      digitalWrite(buzz, LOW);
      val2Set = map(curDist,(long)20,(long)initDist, (long)0,(long)120);
    }
    
    analogWrite(enD,val2Set);
    analogWrite(enS,val2Set);

    printPwm(val2Set);
    printDistance(curDist);
    
    if (t%100 == 0){
        clearVariable(6,0);
        clearVariable(6,1);
    }
  }
}
//funzione che ritorna la distanza misurata dal sensore HCSR04
long hcsr04(){
    digitalWrite(out,LOW);
    delayMicroseconds(2);
    digitalWrite(out,HIGH);
    delayMicroseconds(10);
    digitalWrite(out,LOW);
    dur=pulseIn(in,HIGH);
    tocm=microsecondsToCentimeters(dur);
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

