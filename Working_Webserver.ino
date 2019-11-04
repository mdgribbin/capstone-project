#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <DHT_U.h>
#include <PubSubClient.h>
#include <MqttClient.h>
#include <UnoWiFiDevEd.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>


#define BAUD 9600

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float piezoV;

const int PIEZO_PIN = A1; // Piezo output
int GroundPin = A0;
const int ledPin = 5;

void setup() 
{
    
  dht.begin();
  pinMode(GroundPin, OUTPUT);
  digitalWrite(GroundPin, LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Wifi.begin();
    Wifi.println("WebServer Server is up"); 
}


void loop() {

   ambienthumidity();
    ambienttemp();
    vibration();
    

 
    while(Wifi.available()){
      process(Wifi);
    }


      
 
  delay(50);
}

void process(WifiData client) {
  // read the command
  String command = client.readStringUntil('/');
  // is "digital" command?
  if (command == "webserver") {
    WebServer(client);
  }
}

float ambienthumidity()
{
hum = dht.readHumidity();
}

float ambienttemp()
{ 
 temp=dht.readTemperature();
}

float vibration()
{
   int piezoADC = analogRead(PIEZO_PIN);
   piezoV = piezoADC;

  if (Serial.read() == '1') {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
}
}

void WebServer(WifiData client){


client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          client.println("<title>");
          client.println("IME4 Webserver");
          client.println("</title>");
          client.println("<h1> FAME Lab Lathe Machine");
          client.println("<meta http-equiv= 'refresh' content= '5'> ");
          client.println("</h1>"); 
          
          client.println("<br/>");
          
          client.print("<body>");

          client.print("<b>");
          client.print("Humidity: ");
          client.print("</b>");
          client.println(hum);
          client.println("<br/>");

          client.print("<b>");
          client.print("Temperature: ");
          client.print("</b>");
          client.println((temp*(9/5))+32);
          client.println("<br/>");

          client.print("<b>");
          client.println("Vibration: ");
          client.print("</b>");
          client.println(piezoV);
          
          client.println("<br/>");
          client.println("<br/>");

          
          
          client.print("</body>");
          client.println("</html>");
          client.print(DELIMITER); // very important to end the communication !!! 
}
  

