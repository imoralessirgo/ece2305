#include <Servo.h>


Servo servo;
int val;

void setup() {
  Serial.begin(9600);
    pinMode(7, INPUT);
    servo.attach(8);
    servo.write(0);
    delay(2000);
}

void loop() {
  val = digitalRead(7);
  if(val > 0){
        Serial.print("low");
        servo.write(90);
  }else{
    Serial.print("high");
        servo.write(0);  
  }

  delay(2000);
//  // put your main code here, to run repeatedly:
//    servo.write(90);
//    delay(2000);
//    servo.write(0);
//    delay(2000);
}
