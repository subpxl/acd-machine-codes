
#include <Wire.h>
#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8f  

int count;

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;

volatile int rpmcount =0;
int rpm =0;
int v;// Register to get both High and Low bytes in 1 call.

int reading = 0;

void setup()
{
  myservo.attach(3);
  Wire.begin(); // join i2c bus
  Serial.begin(9600); // start serial communication at 9600bps
   Serial.println ("acd");
   attachInterrupt(2, rpm_fan, FALLING);
  
   pinMode(4,OUTPUT);
   pinMode(5,OUTPUT);
   pinMode(6,OUTPUT);
}

void loop()
{
  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterMeasure); // sets register pointer to  (0x00)  
  Wire.write((int)MeasureValue); // sets register pointer to  (0x00)  
  Wire.endTransmission(); // stop transmitting

  delay(20); // Wait 20ms for transmit

  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterHighLowB); // sets register pointer to (0x8f)
  Wire.endTransmission(); // stop transmitting

  delay(20); // Wait 20ms for transmit

  Wire.requestFrom((int)LIDARLite_ADDRESS, 2); 
    Serial.println("  ");
  Serial.print("cm= ");
       Serial.print("RPM =\t"); //print the word "RPM" and tab.
      Serial.println(rpm); // print the rpm value.
      Serial.print("\t Hz="); //print the word "Hz".
     Serial.println(rpmcount);
     Serial.print("\t");
    Serial.print("velocity=\t");
 int e = v;
    Serial.println(e);// request 2 bytes from LIDAR-Lite
  v = rpmcount*45;
 rpmcount = 0; // Restart the RPM counter
     // Uptade lasmillis
    attachInterrupt(2, rpm_fan, FALLING);
  if(2 <= Wire.available()) // if two bytes were received
  {
    reading = Wire.read(); // receive high byte (overwrites previous reading)
    reading = reading << 8; // shift high byte to be high 8 bits
    reading |= Wire.read(); // receive low byte as lower 8 bits
    Serial.println(reading); // print the reading
 
}
  if(reading < e){
    
  myservo.write(100); 
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  delay(500);
 myservo.write(108);
 digitalWrite(4,HIGH);
 
  digitalWrite(5,HIGH);
    delay(500);
  }
  else{
    
myservo.write(60);
digitalWrite(5,LOW);

  digitalWrite(3,HIGH);
  }
   delay(200);
}
 void rpm_fan()
     { 
      rpmcount++;
      }
    

