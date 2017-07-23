
#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

volatile int rpmcount = 0;
int rpm = 0;
int v; // x on the graph
int d; // observed
int e;
int i;

int triggerPin=6;
int echoPin =7;
long duration, cm;
int count;
#include <Servo.h>
Servo myservo;
int pos = 0;


void setup(){
   Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(triggerPin,OUTPUT);
    pinMode(echoPin,INPUT);
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(11,INPUT); //PIN FOR REVERSE SWITCH
     myservo.attach(9);
 Serial.begin(9600); 
 int pos = 0;

 attachInterrupt(1, rpm_fan, FALLING);
}

void loop()
{
 
  
 
       detachInterrupt(1);    
       rpm = rpmcount * 60;  
       v = rpmcount * 0.681 ; // km/hour
      // Serial.print("RPM =\t"); 
      //Serial.print(rpm/8); 
      //Serial.print("\t Hz="); 
     //Serial.println(rpmcount/8);
    // Serial.print("\t");
     //Serial.print("\t");
     //Serial.print("\t");
    Serial.print("velocity= \t");
    Serial.println(v);
    //Serial.print("cm= ");
   //  Serial.print(cm);
       Serial.print("acy= ");
     Serial.print(AcY);
     
      digitalWrite(triggerPin,LOW);
     delayMicroseconds(6);
     digitalWrite(triggerPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(triggerPin, LOW);
     delayMicroseconds(6);
     duration =  pulseIn(echoPin,HIGH);
     
     cm= distance(duration);
 
     rpmcount = 0;
     
    attachInterrupt(1, rpm_fan, FALLING);
    e= 0.5*v;
    d = cm ;
    Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();
    if(d > e)
    {digitalWrite(13,HIGH);
    digitalWrite(12,LOW);
    }
    
    if(d < e)
    {digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
    }
     if (AcY > 3000)
    {
         digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    delay(100);
       digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    delay(100);
       digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
      delay(100);
    }
    i = digitalRead(11);
    if(i==HIGH)
    {  digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    delay(100);
       digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    delay(100);
       digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);      //condition for reverse gear
      delay(100);
    }
   
  delay(1000);
  
  
     

  
 }
    void rpm_fan()
     { 
      rpmcount++;
      }  
    
    
    
       long distance(long microseconds)
   {
      return microseconds /29/2; 
    }
    



