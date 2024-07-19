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
            if (header.indexOf("GET /LED/on") >= 0)
            {
              Serial.println("GPIO LED on");
              outputLEDState = "on";
              digitalWrite(RGB_BUILTIN, HIGH);
            }
            else if (header.indexOf("GET /LED/off") >= 0)
            {
              Serial.println("GPIO LED off");
              outputLEDState = "off";
              digitalWrite(RGB_BUILTIN, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            // Display current state, and ON/OFF buttons for GPIO 26
            client.println("<p>GPIO 26 - State " + outputLEDState + "</p>");
            // If the output26State is off, it displays the ON button
            if (outputLEDState == "off")
            {
              client.println("<p><a href=\"/LED/on\"><button class=\"button\">ON</button></a></p>");
            }
            else
            {
              client.println("<p><a href=\"/LED/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("</body></html>");

            // The HTTP response ends with another blank line
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