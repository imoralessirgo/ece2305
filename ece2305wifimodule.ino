while(1){
if(wifiSerial.available()>0){ 
   String message = readWifiSerialMessage(); 
   if(find(message,"esp8266:")){ 
      String result = sendToWifi(message.substring(8,message.length()),responseTime,DEBUG); 
     if(find(result,"OK")) 
       sendData("\n"+result); 
     else 
       sendData("\nErrRead");               //At command ERROR CODE for Failed Executing statement 
   }else 
   if(find(message,"HELLO")){  //receives HELLO from wifi 
       sendData("\\nHI!");    //arduino says HI 
   }else if(find(message,"LEDON")){ 
     digitalWrite(13,HIGH); 
   }else if(find(message,"LEDOFF")){ 
     digitalWrite(13,LOW); 
   } 
   else{ 
     sendData("\nErrRead");                 //Command ERROR CODE for UNABLE TO READ 
   } 
 }
}



/*
* Name: sendData
* Description: Function used to send string to tcp client using cipsend
* Params: 
* Returns: void
*/
void sendData(String str){
 String len="";
 len+=str.length();
 sendToWifi("AT+CIPSEND=0,"+len,responseTime,DEBUG);
 delay(100);
 sendToWifi(str,responseTime,DEBUG);
 delay(100);
 sendToWifi("AT+CIPCLOSE=5",responseTime,DEBUG);
}
/*
* Name: find
* Description: Function used to match two string
* Params: 
* Returns: true if match else false
*/
boolean find(String string, String value){
 if(string.indexOf(value)>=0)
   return true;
 return false;
}
/*
* Name: readSerialMessage
* Description: Function used to read data from Arduino Serial.
* Params: 
* Returns: The response from the Arduino (if there is a reponse)
*/
String  readSerialMessage(){
 char value[100]; 
 int index_count =0;
 while(Serial.available()>0){
   value[index_count]=Serial.read();
   index_count++;
   value[index_count] = '\0'; // Null terminate the string
 }
 String str(value);
 str.trim();
 return str;
}
/*
* Name: readWifiSerialMessage
* Description: Function used to read data from ESP8266 Serial.
* Params: 
* Returns: The response from the esp8266 (if there is a reponse)
*/
String  readWifiSerialMessage(){
 char value[100]; 
 int index_count =0;
 while(wifiSerial.available()>0){
   value[index_count]=wifiSerial.read();
   index_count++;
   value[index_count] = '\0'; // Null terminate the string
 }
 String str(value);
 str.trim();
 return str;
}
/*
* Name: sendToWifi
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendToWifi(String command, const int timeout, boolean debug){
 String response = "";
 wifiSerial.println(command); // send the read character to the esp8266
 long int time = millis();
 while( (time+timeout) > millis())
 {
   while(wifiSerial.available())
   {
   // The esp has data so display its output to the serial window 
   char c = wifiSerial.read(); // read the next character.
   response+=c;
   }  
 }
 if(debug)
 {
   Serial.println(response);
 }
 return response;
}
/*
* Name: sendToUno
* Description: Function used to send data to Arduino.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendToUno(String command, const int timeout, boolean debug){
 String response = "";
 Serial.println(command); // send the read character to the esp8266
 long int time = millis();
 while( (time+timeout) > millis())
 {
   while(Serial.available())
   {
     // The esp has data so display its output to the serial window 
     char c = Serial.read(); // read the next character.
     response+=c;
   }  
 }
 if(debug)
 {
   Serial.println(response);
 }
 return response;
}
