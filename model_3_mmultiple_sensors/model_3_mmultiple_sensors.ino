
#include <I2C.h>
#define    LIDARLite_ADDRESS     0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure       0x00          // Register to write to initiate ranging.
#define    MeasureValue          0x04          // Value to initiate ranging.
#define    RegisterHighLowB      0x8f          // Register to get both High and Low bytes in 1 call.
#define    I2CMultiplexer        0x70          // PCA9544A Multiplexer Address
#include <Servo.h>
Servo myservo;
int pos = 0;
void setup(){
  Serial.begin(115200); //Opens serial connection at 115200bps.     
  I2c.begin(); // Opens & joins the irc bus as master
  delay(100); // Waits to make sure everything is powered up before sending or receiving data  
  I2c.timeOut(50); // Sets a timeout to ensure no locking up of sketch if I2C communication fails
}

void loop(){
  selectMultiplexerChannel(0); //Select Multiplexer Channel 0
  Serial.print(readDistance()); // Read Distance from Sensor at Channel 0
  Serial.print(".");          // Print "." to separate readings
  selectMultiplexerChannel(1); //Select Multiplexer Channel 1
  Serial.print(readDistance()); // Read Distance from Sensor at Channel 1
  Serial.print(".");          // Print "." to separate readings
 
}


void selectMultiplexerChannel(byte channel){
  byte controlRegister = 0x04; // The Control register of the Multiplexer
  controlRegister |= channel; // Bitwise OR controlRegister & channel
  uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses     
  while (nackack != 0){ // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
    nackack = I2c.write((uint8_t)I2CMultiplexer, (uint8_t)controlRegister); // Write 0x04 to 0x00
    delay(1); // Wait 1 ms to prevent overpolling
  }
}

int readDistance(){
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
  int distance = (distanceArray[0] << 8) + distanceArray[1];  // Shift high byte [0] 8 to the left and add low byte [1] to create 16-bit int
  
  Serial.print(distance);   // Print Sensor Name & Distance
   
}
