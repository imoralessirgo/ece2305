#include <Servo.h>


Servo servo;
int soilPin = A0;//Declare a variable for the soil moisture sensor 
int soilPower = 7;//Variable for Soil moisture Power

void setup() {
  
  Serial.begin(115200);
  WiFi.begin(ESP, "password");
  
  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
  
  pinMode(7, INPUT);
    servo.attach(8);
    servo.write(0);
    
  
  // Start TCP server.
  server.begin();

}

void loop() {
 if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    // Print the new IP to Serial. 
    printWiFiStatus();
  }

  WiFiClient client = server.available();
  
  if (client) {
    
    Serial.println("Client connected.");
    
    while (client.connected()) {  
      if (client.available()) {
        
        char command = client.read(); 
        
        if (command == 'W') { // Water Plant
          waterPlant();
        }
        else if (command == 'R') { // Read moisture
          Serial.print(readSoil());
        }        
      }
    }
    
    Serial.println("Client disconnected.");
    client.stop();
  }

}

void waterPlant(){
  servo.write(90);
  delay(2000);
   servo.write(90);
}

int readSoil(){

    digitalWrite(soilPower, HIGH);//turn D7 "On"
    delay(10);//wait 10 milliseconds 
    val = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn D7 "Off"
    return val;//send current moisture value
    
}
