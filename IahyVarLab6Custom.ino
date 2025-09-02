#include "arduino_secrets.h"

/********************************
  PEO Scarborough Chapter
  Mechatronics 2024
  Ontario, Canada
  Lab 6 - WiFi Servo Control

  Ishyvar Builders
  Varsan Jeyakkumar
  Arushan Jeyakkumar
  Ishraq Alam
********************************/

#include "WiFi.h"
#include <ESP32Servo.h>

Servo servoX;
Servo servoY;
Servo servoG;

int minUs = 520;      
int maxUs = 2480;

int servoXPin = 18;
int servoYPin = 19;
int servoGPin = 21;

int servoXPos = 0;                   
int servoYPos = 0;                   
int servoGPos = 0;                   

int servoXPos_temp = 0;         
int servoYPos_temp = 0; 

int servoXPos_min = 0;
int servoXPos_max = 180;
int servoXPos_increment = 20;

int servoYPos_min = 0;        
int servoYPos_max = 180;
int servoYPos_increment = 20; 

int servoGPos_min = 0;        
int servoGPos_max = 180;

String servoXStatus = "0 Degrees";   // Variable to store the current X-Axis direction
String servoYStatus = "0 Degrees";   // Variable to store the current Y-Axis direction
String servoGStatus = "Open";        // Variable to store the current gripper state

const char* ssid = "PEOSC_ESP32";    // <<< Change the SSID
const char* password = "123456789";  // <<< !!! Password needs to be greater than 8 characters !!!
String header = "";                  // Variable to store the HTTP request
WiFiServer server(80);               // Set web server port number to 80
IPAddress IP = {0,0,0,0};            // Clear Access Point IP Address
String IPString = "";                // String to store Access Point IP Address

void setup() {
  
  servoX.attach(servoXPin, minUs, maxUs);
  servoY.attach(servoYPin, minUs, maxUs);
  servoG.attach(servoGPin, minUs, maxUs);
    
  Serial.begin(9600);
  while(!Serial);

  Serial.println("Setting APâ¦");
  
  // Initialize the Access Point SSID and password
  WiFi.softAP(ssid, password);

  // Get the assigned IP address to the Access Point (ESP32)
  IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  IPString = IP.toString().c_str();
  
  server.begin();

  servoX.write(servoXPos_min);
  servoY.write(servoYPos_min);
  servoG.write(servoGPos_min);

  servoXPos_temp = servoXPos_min;
  servoYPos_temp = servoYPos_min;
  
}

void loop(){
  
  // Listen for incoming clients
  WiFiClient client_request = server.available();   
  
  // If a new client connects,
  if (client_request) {                             
    
    // Call to web server function
    web_server(client_request);
    
  }

}

void web_server(WiFiClient client) {
  
  Serial.println("New Client.");  
  
  // Store incoming data from the client into a variable
  String currentLine = "";    
  
  while (client.connected()) {            // Loop while the client is connected
    
    if (client.available()) {             // If there is incoming characters from the client
      
      char incoming_char = client.read(); // Read a byte
      Serial.write(incoming_char);        // Print it to the serial monitor
      header += incoming_char;            // Append bytes to string called header
      
      if (incoming_char == '\n') {        // If the incoming character is a newline
        
        // If the current line is blank, you got two newline characters in a row.
        // That's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
        
          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<link rel=\"icon\" href=\"data:,\">");
          
          // CSS to style the buttons 
          client.println("<style>html { background-color: #072339; ; font-family: Calibri; color: white; display: inline-block; margin: 0px auto; text-align: center;}");
          client.println(".button { background-color: #477D94; border: none; color: white; padding: 12px 10px;");
          client.println("text-align: center; font-size: 20px; margin: 2px; cursor: pointer; width: 150px}");
          client.println("</style></head>");
          
          //Call Servo Control
          servo_control();
          
          // Web Page Heading
          client.println("<body>");
          client.println("<h2>PEO Scarborough</h2>");
          client.println("<h2>Mechatronics 2024</h2>");
          //client.println("<br>");
          client.println("<h3>Robotic Arm Project</h3>");
          client.println("<h3>ESP32 Web Server</h3>");
          client.println("<h4>IP Address: " + IPString + "</h4>");
          client.println("<br>");

          // Display Gripper state 
          client.println("<p>Gripper: " + servoGStatus + "</p>");
          
          // If motorState is OFF, display the ON button instead       
          client.println("<p>");
          client.println("<a href=\"/g/open\"><button class=\"button\">Open</button></a>");
          client.println("<a href=\"/g/close\"><button class=\"button\">Close</button></a>");
          client.println("</p>");
          
          // Display X Axis direction
          client.println("<p>X-Axis: " + servoXStatus + "</p>");
          
          // If motorDirect is forward, displays the Reverse button instead       
          client.println("<p>");
          client.println("<a href=\"/x/left\"><button class=\"button\">Left</button></a>");
          client.println("<a href=\"/x/right\"><button class=\"button\">Right</button></a>");
          client.println("</p>");

          // Display Y Axis direction
          client.println("<p>Y-Axis: " + servoYStatus + "</p>");
          
          client.println("<p>");
          client.println("<a href=\"/y/up\"><button class=\"button\">Up</button></a>");
          client.println("<a href=\"/y/down\"><button class=\"button\">Down</button></a>");
          client.println("</p>");
          
          client.println("</body></html>");
          
          // The HTTP response ends with another blank line
          client.println();
          
          // Break out of the while loop
          break;
        
        } 
        else {                            // If you got a newline, then clear currentLine
          
          currentLine = "";
          
        }
      
      } 
      else if (incoming_char != '\r') {   // if you got anything else but a carriage return character,
        
        currentLine += incoming_char;     // add it to the end of the currentLine
        
      }
    }
  }
  
  // Clear the header variable
  header = "";
  
  // Close the connection
  client.stop();
  
  Serial.println("Client disconnected successfully, proceed.");
  Serial.println("");

}

void servo_control() {

  if (header.indexOf("GET /g/close") >= 0 && servoGStatus == "Open") {
    
    for (servoGPos = servoGPos_min; servoGPos < servoGPos_max; servoGPos += 1) {
	servoG.write(servoGPos);
	delay(1);
    } 

    Serial.println("Gripper: Close");
    servoGStatus = "Close";
    
  }
  
  if (header.indexOf("GET /g/open") >= 0 && servoGStatus == "Close") {
  
    for (servoGPos = servoGPos_max; servoGPos > servoGPos_min; servoGPos -= 1) { 
      servoG.write(servoGPos);
      delay(1);          
    }

    Serial.println("Gripper: Open");
    servoGStatus = "Open";
    
  }

  if (header.indexOf("GET /x/left") >= 0 && servoXPos_temp < servoXPos_max) {
  
    for (servoXPos = servoXPos_temp; servoXPos < (servoXPos_temp + servoXPos_increment); servoXPos += 1) {
      servoX.write(servoXPos);
      delay(10);   

      if(servoXPos == (servoXPos_temp-1)){break;}
    }

    servoXPos_temp = servoXPos + 1;
    
    servoXStatus = "-" + String(servoXPos_increment) + " Degrees";
    Serial.println("X Axis: Left");
  } 

  if (header.indexOf("GET /x/right") >= 0 && servoXPos_temp > 0) {

    for (servoXPos = servoXPos_temp; servoXPos > (servoXPos_temp - servoXPos_increment); servoXPos -= 1) { 
	  servoX.write(servoXPos);
	  delay(10);

      if(servoXPos == 1){break;}
    } 

    servoXPos_temp = servoXPos - 1;

    servoXStatus = "+" + String(servoXPos_increment) + " Degrees";
    Serial.println("X Axis: Right");
    
  } 
  
  if (header.indexOf("GET /y/down") >= 0 && servoYPos_temp < servoYPos_max) {
  
    for (servoYPos = servoYPos_temp; servoYPos < (servoYPos_temp + servoYPos_increment); servoYPos += 1) {
      servoY.write(servoYPos);
      delay(10);   

      if(servoYPos == (servoYPos_max-1)){break;}
    }

    servoYPos_temp = servoYPos + 1;
    
    servoYStatus = "-" + String(servoYPos_increment) + " Degrees";
    Serial.println("Y Axis: Down");
  } 

  if (header.indexOf("GET /y/up") >= 0 && servoYPos_temp > 0) {

    for (servoYPos = servoYPos_temp; servoYPos > (servoYPos_temp - servoYPos_increment); servoYPos -= 1) { 
	  servoY.write(servoYPos);
	  delay(10);

      if(servoYPos == 1){break;}
    } 

    servoYPos_temp = servoYPos - 1;

    servoYStatus = "+" + String(servoYPos_increment) + " Degrees";
    Serial.println("Y Axis: Up");
    
  } 

  
} // Void