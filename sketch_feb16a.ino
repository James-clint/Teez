#define BLYNK_TEMPLATE_ID "TMPL2iiT3tCmP"
#define BLYNK_TEMPLATE_NAME "Fertilizer dispenser"
#define BLYNK_AUTH_TOKEN "Dfg_25UBwa9dJ7VI77mwoXVpPg-aBjkN"

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 2          // Digital pin 2 for DHT sensor
#define DHTTYPE DHT11     // DHT 11 sensor type

#define SOLENOID_VALVE_1 14   // Change to the actual pin number
#define SOLENOID_VALVE_2 12   // Change to the actual pin number
#define SOLENOID_VALVE_3 13   // Change to the actual pin number
#define PUMP_PIN 5            // Change to the actual pin number

#define MOISTURE_SENSOR A0

DHT dht(DHTPIN, DHTTYPE);

char auth[] = "Dfg_25UBwa9dJ7VI77mwoXVpPg-aBjkN"; // Enter your Blynk authentication token
char ssid[] = "EL-LAZHA"; // Enter your WiFi network name
char pass[] = "BILLIONZ"; // Enter your WiFi password

int moistureValue = 0;
int humidityValue = 0;
int temperatureValue = 0;

BlynkTimer timer;

void readSensorData() {
  humidityValue = dht.readHumidity();
  temperatureValue = dht.readTemperature();

  moistureValue = analogRead(MOISTURE_SENSOR);
  moistureValue = map(moistureValue, 0, 1023, 0, 100);

  
 Blynk.virtualWrite(V6, temperatureValue);  //V5 is for Humidity
 Blynk.virtualWrite(V5, humidityValue);  //V6 is for Temperature
 Blynk.virtualWrite(V7, moistureValue);  //V7 is for moistureValue
}

BLYNK_WRITE(V1) {  // Virtual pin V1 for controlling solenoid valve 1
  int valve1Value = param.asInt();
  digitalWrite(SOLENOID_VALVE_1, valve1Value);
  Serial.println(valve1Value); 
}

BLYNK_WRITE(V2) {  // Virtual pin V2 for controlling solenoid valve 2
  int valve2Value = param.asInt();
  digitalWrite(SOLENOID_VALVE_2, valve2Value);
  Serial.println(valve2Value); 
}

BLYNK_WRITE(V3) {  // Virtual pin V3 for controlling solenoid valve 3
  int valve3Value = param.asInt();
  digitalWrite(SOLENOID_VALVE_3, valve3Value);
  Serial.println(valve3Value); 
}

BLYNK_WRITE(V4) {  // Virtual pin V4 for controlling pump
  int pumpValue = param.asInt();
  digitalWrite(PUMP_PIN, pumpValue);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  pinMode(SOLENOID_VALVE_1, OUTPUT);
  pinMode(SOLENOID_VALVE_2, OUTPUT);
  pinMode(SOLENOID_VALVE_3, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);

  timer.setInterval(5000L, readSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}


