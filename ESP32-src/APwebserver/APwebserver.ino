/*
Written By Jackson McDowell for the Biedermann Lab
07/2024

Follow https://randomnerdtutorials.com/esp32-access-point-ap-web-server/ for more information
*/

#include <WiFi.h>

// Network AP credentials
const char *ssid = "ESP32-Access-Point";
const char *password = "strontium";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliary variables to store the current output state

// Pump Relay
String output6State = "off";

// Coil Relay
String output22State = "off";
String output23State = "off";
String coilTempShutOff = "on";
String coilPumpMoistureShutOff = "off";

// RGB LED
String outputLEDState = "off";

// Assign output variables to GPIO pins
const int output6Pump = 6;
const int output22Coil = 22;
const int output23Coil = 23;

// Assign input variables to GPIO pins

// Thermistors
const int input2Thermistor = 2;
const int input3Thermistor = 3;
const int input4Thermistor = 4;
const int input5Thermistor = 5;

// Moisture Sensors
const int input20Moisture = 20;
const int input21Moisture = 21;

// Values
float temp1;
float temp2;
float temp3;
float temp4;
float tempAvg;
int moisture1;
int moisture2;
int moistureTotal;
int coilShutoffTemp = 60;

void setup()
{
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output6Pump, OUTPUT);
  pinMode(output22Coil, OUTPUT);
  pinMode(output23Coil, OUTPUT);

  // Initialize the input variables as inputs
  pinMode(input2Thermistor, INPUT);
  pinMode(input3Thermistor, INPUT);
  pinMode(input4Thermistor, INPUT);
  pinMode(input5Thermistor, INPUT);
  pinMode(input20Moisture, INPUT);
  pinMode(input21Moisture, INPUT);

  // Set outputs to LOW
  digitalWrite(output6Pump, LOW);
  digitalWrite(output22Coil, LOW);
  digitalWrite(output23Coil, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop()
{
  // Sensors

  // Wifi
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /6/on") >= 0)
            {
              Serial.println("GPIO 6 on");
              output6State = "on";
              digitalWrite(output6Pump, HIGH);
            }
            else if (header.indexOf("GET /6/off") >= 0)
            {
              Serial.println("GPIO 6 off");
              output6State = "off";
              digitalWrite(output6Pump, LOW);
            }
            else if (header.indexOf("GET /22/on") >= 0)
            {
              Serial.println("GPIO 22 on");
              output22State = "on";
              digitalWrite(output22Coil, HIGH);
            }
            else if (header.indexOf("GET /22/off") >= 0)
            {
              Serial.println("GPIO 22 off");
              output22State = "off";
              digitalWrite(output22Coil, LOW);
            }
            else if (header.indexOf("GET /23/on") >= 0)
            {
              Serial.println("GPIO 23 on");
              output23State = "on";
              digitalWrite(output23Coil, HIGH);
            }
            else if (header.indexOf("GET /23/off") >= 0)
            {
              Serial.println("GPIO 23 off");
              output23State = "off";
              digitalWrite(output23Coil, LOW);
            }

            client.println("<!DOCTYPE html>");
            client.println("<style> .tooltip { position: relative; display: inline-block; } .tooltip .tooltiptext { visibility: hidden; background-color: #E0E3F4; color: #000; text-align: center; border-radius: 5px; padding: 5px 0; /* Position the tooltip */ position: absolute; z-index: 1; top: -35px; } .tooltip:hover .tooltiptext { visibility: visible; } .tooltip:active .tooltiptext { visibility: visible; } a:hover { scale: 1.1; transition: 0.5s; } </style>");
            client.println("<html lang=\" en \"> <head> <meta charset=\" UTF - 8 \"> <meta name=\" viewport \" content=\" width = device - width, initial - scale = 1.0 \"> <title>Coil Control Panel</title> </head>");
            client.println("<body> <div style=\" text - align : center; display : flex; flex - wrap : wrap; justify - content : center; flex-direction : column; align-items : center; \"> <h1>Coil Control Panel</h1> <div style=\" display : flex; justify - content : center; background-color: #EEECF4; width : 90 % ; padding : 20px; border-radius : 5px; margin - top : 20px; margin - bottom : 20px; \">");

            // Display current state, and ON/OFF buttons for GPIO 22
            client.println("<p>Coil 1 - " + output22State + "</p>");
            // If the output22State is off, it displays the ON button
            if (output22State == "off")
            {
              client.println("<a href=\"/22/on\" style=\"text-decoration: none; color: black; \"><div style=\" margin : 20px; background-color: #FD8A8A; padding : 25px; border-radius : 5px; padding-left : 30px; padding-right : 30px; \"> <h2> Coil 1 </h2> </div> </a>");
            }
            else
            {
              client.println("<a href=\"/22/off\" style=\"text-decoration: none; color: black; \"><div style=\" margin : 20px; background-color: #A8D1D1; padding : 25px; border-radius : 5px; padding-left : 30px; padding-right : 30px; \"> <h2> Coil 1 </h2> </div> </a>");
            }

            // Display current state, and ON/OFF buttons for GPIO 23
            client.println("<p>Coil 2 - " + output23State + "</p>");
            // If the output23State is off, it displays the ON button
            if (output23State == "off")
            {
              client.println("<a href=\"/23/on\" style=\"text-decoration: none; color: black; \"><div style=\" margin : 20px; background-color: #FD8A8A; padding : 25px; border-radius : 5px; padding-left : 30px; padding-right : 30px; \"> <h2> Coil 2 </h2> </div> </a>");
            }
            else
            {
              client.println("<a href=\"/23/off\" style=\"text-decoration: none; color: black; \"><div style=\" margin : 20px; background-color: #A8D1D1; padding : 25px; border-radius : 5px; padding-left : 30px; padding-right : 30px; \"> <h2> Coil 2 </h2> </div> </a>");
            }

            // Display current state, and ON/OFF buttons for GPIO 6
            client.println("<p>Pump - " + output6State + "</p>");
            // If the output6State is off, it displays the ON button
            if (output6State == "off")
            {
              client.println("<a href=\"/6/on\" style=\"text-decoration: none; color: black; \"><div style=\" margin : 20px; background-color: #FD8A8A; padding : 25px; border-radius : 5px; padding-left : 30px; padding-right : 30px; \"> <h2> Pump </h2> </div> </a>");
            }
            else
            {
              client.println("<a href=\"/6/off\" style=\"text-decoration: none; color: black; \"><div style=\" margin : 20px; background-color: #A8D1D1; padding : 25px; border-radius : 5px; padding-left : 30px; padding-right : 30px; \"> <h2> Pump </h2> </div> </a>");
            }

            client.println("</div>");

            client.println("<div style=\" display : flex; justify-content : center; flex - wrap : wrap; background-color: #EEECF4; width : 90 % ; padding : 20px; border-radius : 5px; margin - top : 25px; margin - bottom : 25px; \"> <div class=\" tooltip \" style=\" display : flex; flex-direction : column; align-items : center; margin : 20px; background-color: #F7F5FF; padding : 20px; border-radius : 5px; \"> <h1>Coils</h1> <h2>Temp Avg: " + tempAvg + "°C</h2> <h2>Moisture: " + moistureTotal + "</h2> <span class=\" tooltiptext \"> <div style=\" display : flex; align-items : center; \"> <div style=\" margin : 30px; \"> <h2>Coil 1</h2> <h3>Temp 1: " + temp1 + "°C</h3> <h3>Temp 2: " + temp2 + "°C</h3> <h3>Moisture: " + moisture1 + "</h3> </div> <div style=\" margin : 30px; \"> <h2>Coil 2</h2> <h3>Temp 1: " + temp3 + "°C</h3> <h3>Temp 2: " + temp4 + "°C</h3> <h3>Moisture: " + moisture2 + "</h3> </div> </div> </span> </div> </div>");

            client.println("<div style=\"display: flex; justify-content: center; flex-wrap: wrap; background-color: #EEECF4; width: 90%; padding: 20px; border-radius: 5px; margin-top: 25px; margin-bottom: 25px;\">");

            if (coilTempShutOff == "off")
            {
              client.println("<a href=\"/Temp/on\" style=\" text-decoration : none; color: black; \"> <div style=\" margin : 30px; background-color: #FD8A8A; padding : 20px; border-radius : 5px; padding-left : 35px; padding-right : 35px; display : flex; flex-direction : column; align-items : center; \"> <div> <h2>Temp Coil Shut Off</h2> <h3> " + coilShutoffTemp + "°C</h3> </div> <div> <a href=\"/Temp/-\" style=\"text-decoration: none; color: black; \"> <button style=\" height : 40px; width : 45px; font - size : 30px; margin : 15px; border-radius : 5px; \">-</button> </a> <a href=\"/Temp/+\" style=\"text-decoration: none; color: black; \"> <button style=\" height : 40px; width : 45px; font - size : 30px; margin : 15px; border-radius : 5px; \">+</button> </a> </div> </div> </a>");
            }
            else
            {
              client.println("<a href=\"/Temp/off\" style=\" text-decoration : none; color: black; \"> <div style=\" margin : 30px; background-color: #A8D1D1; padding : 20px; border-radius : 5px; padding-left : 35px; padding-right : 35px; display : flex; flex-direction : column; align-items : center; \"> <div> <h2>Temp Coil Shut Off</h2> <h3> " + coilShutoffTemp + "°C</h3> </div> <div> <a href=\"/Temp/-\" style=\"text-decoration: none; color: black; \"> <button style=\" height : 40px; width : 45px; font - size : 30px; margin : 15px; border-radius : 5px; \">-</button> </a> <a href=\"/Temp/+\" style=\"text-decoration: none; color: black; \"> <button style=\" height : 40px; width : 45px; font - size : 30px; margin : 15px; border-radius : 5px; \">+</button> </a> </div> </div> </a>");
            }

            if (coilPumpMoistureShutOff == "off")
            {
              client.println("<a href=\"/PumpMoisture/on\" style=\"text-decoration: none; color: black; \"> <div style=\" margin : 30px; background-color: #FD8A8A; padding : 75px; border-radius : 5px; padding-left : 25px; padding-right : 25px; display : flex; flex-direction : column; align-items : center; \"> <div> <h2>Moisture Pump/Coil Shut Off</h2> </div> </div> </a>");
            }
            else
            {
              client.println("<a href=\"/PumpMoisture/off\" style=\"text-decoration: none; color: black; \"> <div style=\" margin : 30px; background-color: #A8D1D1; padding : 75px; border-radius : 5px; padding-left : 25px; padding-right : 25px; display : flex; flex-direction : column; align-items : center; \"> <div> <h2>Moisture Pump/Coil Shut Off</h2> </div> </div> </a>");
            }

            client.println("</div></div></body></html>");
            client.println();

            // Break out of the while loop
            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
