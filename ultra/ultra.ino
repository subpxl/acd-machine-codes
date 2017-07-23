int triggerPin=2;
int echoPin =3;
long duration, cm;
int ir1=4;
int count;

void setup()
{
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  pinMode(13,OUTPUT);

  pinMode(ir1,INPUT);
  digitalWrite(ir1,LOW);
  
   pinMode(triggerPin,OUTPUT);
    pinMode(echoPin,INPUT);
    Serial.begin(9600);
    Serial.println("ultrasonic sensor");
    delay(2000);
}    
  

void loop()
{
Serial.println("  ");
  if(digitalRead(ir1)==HIGH )
{
 count++;
 delay(50);
     Serial.print("count= ");
     Serial.print(count);
     delay(50);  
}
       
     digitalWrite(triggerPin,LOW);
     delayMicroseconds(2);
     digitalWrite(triggerPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(triggerPin, LOW);
     delayMicroseconds(2);
     duration =  pulseIn(echoPin,HIGH);
     
     cm= distance(duration);
     Serial.print("cm= ");
     Serial.print(cm);
     delay(50);
 
    
  if(cm<15)
   {
     digitalWrite(13,HIGH);
     
   }
   else
   digitalWrite(13,LOW);
}

     long distance(long microseconds)
{
  return microseconds /29/2; 
}
