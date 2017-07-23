
int count;

volatile int rpmcount =0;
int rpm =0;
int v;
unsigned long lastmillis =1;

void setup()
{
 
  Serial.begin(9600);
  Serial.println ("acd");
   attachInterrupt(2, rpm_fan, FALLING);
  }
  void loop()
  {
    Serial.println("  ");
  Serial.print("cm= ");
       Serial.print("RPM =\t"); //print the word "RPM" and tab.
      Serial.println(rpm); // print the rpm value.
      Serial.print("\t Hz="); //print the word "Hz".
     Serial.println(rpmcount);
     Serial.print("\t");
    Serial.print("velocity=\t");
    Serial.println(v);
    
     delay(1000);
    {  //Uptade every one second, this will be equal to reading frecuency (Hz).
 
       detachInterrupt(2);    //Disable interrupt when calculating
       rpm = rpmcount * 60;  // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use rpmcount * 30.
       v = rpmcount * 0.065;
     //print revolutions per second or Hz. And print new line or enter.
    
     rpmcount = 0; // Restart the RPM counter
     // Uptade lasmillis
    attachInterrupt(2, rpm_fan, FALLING); //enable interrupt
       }   
   }
    void rpm_fan()
     { 
      rpmcount++;
      }
    
   
