#include <UnoWiFiDevEd.h>

#include <Adafruit_Sensor.h>

//#include <DHT_U.h>

// data collection for FAME lab machines
// uses ambient temperature and humidity sensor and vibration sensor

#include <DHT.h>
#include <Wire.h>


#define BAUD 9600
WifiData ESPSerial;

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

const int PIEZO_PIN = A1; // Piezo output
int GroundPin = A0;
const int ledPin = 5;

void setup() 
{
  ESPSerial.begin(9600);
  dht.begin();
  pinMode(GroundPin, OUTPUT);
  digitalWrite(GroundPin, LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

float ambienthumidity()
{
hum = dht.readHumidity();
ESPSerial.print("Humidity: ");
ESPSerial.println(hum);
}

float ambienttemp()
{ 
 temp=dht.readTemperature();
 ESPSerial.print("Temperature ");
 ESPSerial.println(temp*(9/5)+32);
 //Serial.print(", ");
}

void loop() 
{
  // Read ambient humidity and temp
 ambienthumidity();
 ambienttemp();

  // Read Piezo ADC value in, and convert it to a voltage
  int piezoADC = analogRead(PIEZO_PIN);
  float piezoV = piezoADC;
  ESPSerial.println(piezoV); // Print the voltage.
  delay(200);
  if (Serial.read() == '1') {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(5000);
 
}
