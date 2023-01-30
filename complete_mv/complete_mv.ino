
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <MPU6050.h>

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;
const int mpu_addr = 0x68;
MPU6050 mpu;

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
int thisChar;

bool first_cicle = true;



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

//valori invio seriale
int16_t val9,val1,val2,val3,val4,val5,val6;
long t;

bool discard;

long initDist; 
long curDist;
long prevDist;
long stopDist = 20;

int val2Set;
int refVel;
int maxVel = 200;
int minVel = 0; 

char a[2];
//pin enable campionamento
int PIN_ENABLE_WEMOS = 2;
String ip_a;

int len_ip;
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

  pinMode(PIN_ENABLE_WEMOS, INPUT);


  pinMode(buzz, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(mpu_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  lcd.begin(16,2);
}

void loop() {
  if(first_cicle){
    //effettuo il primo ciclo
    first_cicle = false;
    t = millis();
    //Scriviamo velocità:
    //ip_a = "wait ip..";
    //lcd.setCursor(0,0);
    //lcd.print("start.."); 

    /*
    while(1){
      if(Serial.available() >=15){
        ip_a = Serial.readString();
      }
      break;
    }

    while(digitalRead(PIN_ENABLE_WEMOS)==LOW){
      lcd.setCursor(0,0);
      lcd.print(ip_a);
      
    }
    */


    lcd.clear();
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
   
  }
  else{
  //CAMPIONAMENTO E INVIO SERIALE DATI MPU-----------------------------------------------
    Wire.beginTransmission(mpu_addr);
    Wire.write(0x3B);  // inizia la trasmissione dei dati del sensore
    Wire.endTransmission(false);
    Wire.requestFrom(mpu_addr, 14, true); // richiedi 14 byte di dati
    val1 = Wire.read() << 8 | Wire.read(); // acclerometro asse X
    val2 = Wire.read() << 8 | Wire.read(); // acclerometro asse Y
    val3 = Wire.read() << 8 | Wire.read(); // acclerometro asse Z
    val9 = Wire.read() << 8 | Wire.read(); // temperatura
    val4 = Wire.read() << 8 | Wire.read(); // giroscopio asse X
    val5 = Wire.read() << 8 | Wire.read(); // giroscopio asse Y
    val6 = Wire.read() << 8 | Wire.read(); // giroscopio asse Z

    curDist = hcsr04();
    
    unsigned long currentTime = millis();
    float elapsedTime = (currentTime - t) / 1000.0;
  //invio pacchetti dati con 8 valori
    
    Serial.print(val1, DEC);// acclerometro asse X
    Serial.print(val2, DEC);// acclerometro asse Y
    Serial.print(val3, DEC);// acclerometro asse Z
    Serial.print(val4, DEC);// giroscopio asse X
    Serial.print(val5, DEC);// giroscopio asse Y
    Serial.print(val6, DEC);// giroscopio asse Z
    if(discard == true ){
      Serial.print(prevDist,DEC);// distanza
    }else{
      Serial.print(curDist,DEC);// distanza
    }
    Serial.print(elapsedTime,DEC); // mando la misura del tempo
    //Serial.println("");
    //Serial.println("Valori inviati sulla seriale!");
    

  //CAMPIONAMENTO DATI HCSR---------------------------------------------------------
    
    //forse il valore misurato non è coerente con la misura precedente quindi lo scarto
    discard = false;
    
    if((curDist - prevDist)>60) discard = true;


    if (!discard){
      prevDist = curDist ;

      if (curDist<=stopDist){

        refVel = minVel;
        if (beep%6 == 0){
          digitalWrite(buzz, LOW);
        }else if (beep%3 == 0){
          digitalWrite(buzz, HIGH);
        }
        beep++;
      }
      
      else if (curDist>initDist) {
        digitalWrite(buzz, LOW);
        refVel = maxVel;
      }
      
      else if(curDist<=initDist){
        digitalWrite(buzz, LOW);
        refVel = map(curDist,(long)stopDist,(long)initDist, (long)minVel,(long)maxVel);
      }

  //INSEGUIMENTO VELOCITA' DI RIFERIMENTO E ATTUAZIONE----------------------------------------

      if(refVel < val2Set){
        val2Set -= 4;
      }
      else if(refVel > val2Set){
        val2Set += 2;
      }

      constrain(val2Set,minVel,maxVel);
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

