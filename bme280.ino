/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define TCAADDR 0x70

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme1; // I2C CPU with TCA9548A 
Adafruit_BME280 bme2; // I2C GPU with TCA9548A 
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

void tcaselect(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();  
}

unsigned long delayTime;

void setup() {
    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("double BME280 with TCA9548A"));
  
  // NOTE!!! VERY IMPORTANT!!!
  // Must call this once manually before first call to tcaselect()
  Wire.begin();

  // Init sensor on bus number 2
  tcaselect(6);
  if (!bme1.begin(0x76)) {
    Serial.println("not work 6");
    while (1);
  }
  Serial.println();

  tcaselect(7);
  if (!bme2.begin(0x76)) {
    Serial.println("not work 7");
    while (1);
  }
  Serial.println();

    unsigned status;
}

  void loop() {
  float temperature1, temperature2;
  float pressure1, pressure2;
  float altitude1, altitude2;
  float humidity1, humidity2;
  float DewPoint1, DewPoint2;

  // Read each device separately
  tcaselect(6);
  temperature1 = bme1.readTemperature();
  pressure1 = bme1.readPressure() /1000;
  altitude1 = bme1.readAltitude(1026);
  humidity1 = bme1.readHumidity();
  DewPoint1 = calcDewpoint(humidity1, temperature1);
  
  tcaselect(7);
  temperature2 = bme2.readTemperature();
  pressure2 = bme2.readPressure() /1000;
  altitude2 = bme2.readAltitude(1026);
  humidity2 = bme2.readHumidity();
  DewPoint2 = calcDewpoint(humidity2, temperature2);
  
  String message = (String) temperature1 + ";" + pressure1 + ";" + altitude1 + ";"  + humidity1 + ";" + DewPoint1 + ";" + temperature2 + ";" + pressure2 + ";" + altitude2 + ";"  + humidity2 + ";" + DewPoint2;
  Serial.println(message);
  delay(750);
}

float calcDewpoint(float humi, float temp) {
  float k;
  k = log(humi/100) + (17.62 * temp) / (243.12 + temp);
  return 243.12 * k / (17.62 - k);
}
