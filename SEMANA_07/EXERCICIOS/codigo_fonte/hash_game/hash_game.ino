#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output38State = "off";
String output16State = "off";

// Assign output variables to GPIO pins
const int output38 = 38;
const int output16 = 16;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output38, OUTPUT);
  pinMode(output16, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output38, LOW);
  digitalWrite(output16, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {  // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");                                             // print a message out in the serial port
    String currentLine = "";                                                   // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {  // if there's bytes to read from the client,
        char c = client.read();  // read a byte, then
        Serial.write(c);         // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /38/on") >= 0) {
              Serial.println("GPIO 38 on");
              output38State = "on";
              digitalWrite(output38, HIGH);
            } else if (header.indexOf("GET /38/off") >= 0) {
              Serial.println("GPIO 38 off");
              output38State = "off";
              digitalWrite(output38, LOW);
            } else if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("GPIO 16 on");
              output16State = "on";
              digitalWrite(output16, HIGH);
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("GPIO 16 off");
              output16State = "off";
              digitalWrite(output16, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body { font-family: font-size: 14px; font-family: Tahoma; margin: 0px auto; text-align: center;}");
            client.println(".h1 { text-align: center;}");
            client.println(".game { margin: 0 auto; width: 500px; display: flex; flex-wrap: wrap; flex-direction: row; justify-content: center;}");
            client.println(".wins {background-color: green !important; color: #fff;}");      
            client.println(".gamer {margin-top: 10px; display: flex; justify-content: center;}");                
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".lines {display: flex !important; justify-content: center;}");
            client.println(".restart {background-color: slateblue ; border: 1pt solid purple; border-radius: 10px; padding:10px; color:White; font-weight: 700; font-size: 30pt;}");            
            client.println(".opt {background-color: white; border:none; color:black; font-weight: 700; font-size: 30pt;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            

            // Web Page Heading
            client.println("<body><h1>Jogo da Velha</h1>");
            client.println("<form class=\"game\" name=\"game\">");
            client.println("<div><div class=\"gamer\"> Jogador 1:<input type=\"text\" name=\"X\" value=\"X\" /></div><br>");
            client.println("<div><div class=\"gamer\"> Jogador 2:<input type=\"text\" name=\"O\" value=\"O\" /></div><br /><br/></div>");
            client.println("<div class= \"lines\">");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(0)\"/>");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(1)\"/>");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(2)\"/></div><hr>");
            client.println("<div class= \"lines\">");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(3)\"/>");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(4)\"/>");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(5)\"/></div><hr>");
            client.println("<div class= \"lines\">");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(6)\"/>");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(7)\"/>");
            client.println("<input type=\"button\" class = \"opt\" name=\"opt\" value=\"click\" onclick=\"process(8)\"/></div><hr>");
            client.println("<div><br /><div class=\"lines\" ><input class=\"restart\" type=\"button\" value=\"Reiniciar\" onclick=\"reboot()\" /></div></div></form>");
            // Display current state, and ON/OFF buttons for GPIO 26
            client.println("<p>Reiniciar Led Vermelho</p>");
            // If the output26State is off, it displays the ON button
            if (output38State == "off") {
              client.println("<p><a href=\"/38/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/38/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 27
            client.println("<p>Reiniciar Led Vermelho</p>");
            // If the output27State is off, it displays the ON button
            if (output16State == "off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<script type=\"text/javascript\"> var clicks = 0; var matrix = [[0, 1, 2],[3, 4, 5],[6, 7, 8],[0, 3, 6],[1, 4, 7],[2, 5, 8],[0, 4, 8],[2, 4, 6],];");            
            client.println("function process(pos) { clicks++; var type = clicks % 2 === 0 ? \"X\" : \"O\"; document.game.opt[pos].value = type; check(type);}");
            client.println("function check(type) { matrix.forEach(function (x) {var count = 0; x.forEach(function (y) { if (document.game.opt[y] && document.game.opt[y].value === type) count++;});if (count == 3) {wins(x); var person = document.game[type].value || type; if(person == \"X\"){alert(\"Parabens X !!! voce ganhou!!!\");  window.location.href=\"/16/on\" }else{alert(\"Parabens O !!! voce ganhou!!!\"); window.location.href=\"/38/on\"};}});}");
            client.println("function wins(x){x.forEach(function (i) {document.game.opt[i].className = \"wins\"})}");
            client.println("function reboot(){document.location.reload(true);}");
            client.println("</script>");
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
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