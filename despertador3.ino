#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include "WiFiUdp.h"
 
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<p style="font-size:100px">Despertador con luz<p>
<p style="font-size:70px">Pancho Iaconis</p>
 
<form action="/action_page">
  <p style="font-size:50px">Alarma: </p> 
  <br>
  <input type="time" style="font-size:50px" name="alarma_usuario" >
  <br>

  
  <p style="font-size:90px">Interruptor</p>
  <input type="radio" id="ON" name="Led" value=1023  size="80">
  <label for="ON"  style="font-size:50px">ON</label><br>
  <input type="radio" id="OFF" checked="checked" name="Led" value=0  size="80">
  <label for="OFF"  style="font-size:50px">OFF</label><br>
  <input type="submit" value="OK"  style="font-size:50px" size="80">
  
</form> 
</center> 
</body>
</html>
)=====";
 
//SSID and Password of your WiFi router
const char* ssid = "Fibertel WiFi060 2.4GHz";//dto
const char* password = "0043225384";

int hora_int = 0;
int minutos_int = 0;
int led = 1;
const int ledPin = 2;
int i = 0;
const long utcOffsetInSeconds = -10800;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

ESP8266WebServer server(80); //Server on port 80
 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//===============================================================
// This routine is executed when you press submit
//===============================================================
void handleForm() {
 String alarma_usuario = server.arg("alarma_usuario");
 String led_state = server.arg("Led");
 //int led_state = server.arg("alarma_usuario");
 Serial.print("Alarma seteada a las:");
 Serial.println(alarma_usuario);

 Serial.print("Led State:");
 Serial.println(led_state);
 led = led_state.toInt();
 
 String hora = alarma_usuario.substring(0,2);
 String minutos = alarma_usuario.substring(3,5);
 
 hora_int = hora.toInt();
 minutos_int = minutos.toInt();
 
 String s = "<a href='/'> Go Back </a>";
 server.send(200, "text/html", s); //Send web page

 
}
/*
void handleLEDon() { 
 Serial.println("LED on page");
 digitalWrite(ledPin,HIGH); //LED is connected in reverse
 led = 1;
 server.send(200, "text/html", "LED is ON"); //Send ADC value only to client ajax request
}
 
void handleLEDoff() { 
 Serial.println("LED off page");
 //digitalWrite(ledPin,LOW); //LED off
 led = 0;
 server.send(200, "text/html", "LED is OFF"); //Send ADC value only to client ajax request
}
*/
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(9600);
  analogWriteFreq(50);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/action_page", handleForm); //form action is handled here
  //server.on("/ledOn", handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  //server.on("/ledOff", handleLEDoff);
  
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
  //Serial.println(hora_int);
  if ((timeClient.getHours() == hora_int) and (timeClient.getMinutes()>=minutos_int) and (timeClient.getMinutes()<minutos_int+15)){
    for(int dutyCycle = 0; dutyCycle < 1024; dutyCycle++){   
    // changing the LED brightness with PWM
      analogWrite(ledPin, dutyCycle);
      delay(900);
      server.handleClient();
      if ((timeClient.getHours() == 0) and (timeClient.getMinutes()==0)){
        break;}
    if (dutyCycle ==1023){
      led=1023;}
    }
    
   //if (led==1){
    //analogWrite(ledPin, 1023);}
   //if (led==0){
    //Serial.println(led);
  analogWrite(ledPin, led);}
  //Serial.println(led); 
  //delay(1000);
  
      
     
  timeClient.update();
  delay(1000);
}

