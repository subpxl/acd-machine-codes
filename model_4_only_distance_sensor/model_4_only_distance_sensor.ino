

#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8f          // Register to get both High and Low bytes in 1 call.
#include <Servo.h>
Servo myservo;
int pos = 0 ;


void setup(){
  Serial.begin(9600); //Opens serial connection at 9600bps.     
 
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
pinMode(11,INPUT);
 // Opens & joins the irc bus as master
  delay(100); // Waits to make sure everything is powered up before sending or receiving data  
   // Sets a timeout to ensure no locking up of sketch if I2C communication fails
}

void loop(){
  // Write 0x04 to register 0x00
  uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses     
  while (nackack != 0){ // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
    nackack = I2c.write(LIDARLite_ADDRESS,RegisterMeasure, MeasureValue); // Write 0x04 to 0x00
    delay(1); // Wait 1 ms to prevent overpolling
  }

  byte distanceArray[2]; // array to store distance bytes from read function
  
  // Read 2byte distance from register 0x8f
  nackack = 100; // Setup variable to hold ACK/NACK resopnses     
  while (nackack != 0){ // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
    nackack = I2c.read(LIDARLite_ADDRESS,RegisterHighLowB, 2, distanceArray); // Read 2 Bytes from LIDAR-Lite Address and store in array
    delay(1); // Wait 1 ms to prevent overpolling
  }
  int distance;
 distance = (distanceArray[0] << 8) + distanceArray[1];  // Shift high byte [0] 8 to the left and add low byte [1] to create 16-bit int
  int e;
  e = distance;
  int i;
  i = digitalRead(11);
  if(i == HIGH)
  {e*0;
  } 
 if (200>e && e<250)
 {myservo.write(10);
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

if (170>e && e<190)
 {myservo.write(20);
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
 
 if (140>e && e<165)
 {myservo.write(30);
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
 if (100>e && e<130)
 {myservo.write(40);
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
 if (50>e && e<90)
 {myservo.write(55);
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
 if (20>e && e<45)
 {myservo.write(65);
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
 if (e<19)
 {myservo.write(90);
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
 
 if (e < 5)
 {myservo.write(10);
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
  // Print Distance
  Serial.println(distance);
}

