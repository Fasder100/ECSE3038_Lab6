#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdio.h>



SoftwareSerial esp(10, 11); // Rx=10, TX=11
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
} 
int increment(){
int i ;

i = i+1;
return i;
}


int getWaterLevel()// random generate Water level
{
long output;
output = random(10,200);

return output;
}

void setup() {
  Serial.begin(9600);
  esp.begin(9600);

  sendData("AT+RST\r\n", 5000, true);
  // //sendData("AT+CWLAP\r\n",10000, true);
  sendData("AT+CWJAP=\"138SL-Residents\",\"resident2020@138sl\"\r\n",5000,true);
   sendData("AT+CIFSR\r\n", 3000,true);
   //sendData("AT+CIPSTART=\"TCP\",\"10.10.76.143\",\"5000\"", 5000, true);

   
  delay(10000); 
}

void loop() {

int w_level;
w_level= getWaterLevel();
int id;
id = increment();


  sendData("AT+CIPSTART=\"TCP\",\"10.10.76.143\",\"5000\"\r\n", 1000, true);
  
  String post = "POST /tank HTTP/1.1\r\nHost: 10.10.76.143:5000\r\nContent-Type: application/json\r\nContent-Length: 30 \r\n\r\n{\"tank_id\":"+ String(id) + ",\"water_level\":" + String(w_level) +"}\r\n";
  Serial.println(w_level);
  Serial.println(id);
  Serial.println(post);
  sendData("AT+CIPSEND=166\r\n", 5000, true);
  sendData(post, 5000, true);


  
  
  
  
  // if (Serial.available()) {      // If anything comes in Serial (USB),
  //   esp.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
  // }

  // if (esp.available()) {     // If anything comes in Serial1 (pins 0 & 1)
  //   Serial.write(esp.read());   // read it and send it out Serial (USB)
  // }
}
 

// ESP TX to Arduino pin 10, through 1k Resistor.
// ESP RX to Arduino pin 11, thorugh 1k Resistor. 
// ESP VCC to Arduino 3V3 
// ESP CH_PD to arduino 3v3
// ESP GND to Arduino GND