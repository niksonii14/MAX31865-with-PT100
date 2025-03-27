#include <Adafruit_MAX31865.h>
#include <SPI.h>

// Define SPI pins for ESP32
#define MAX_CS   5   // Chip Select
#define MAX_MISO 19  // MISO
#define MAX_MOSI 23  // MOSI
#define MAX_SCK  18  // SCK

// Use hardware SPI with custom CS pin
Adafruit_MAX31865 thermo = Adafruit_MAX31865(MAX_CS);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
#define RNOMINAL  100.0

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit MAX31865 PT100 Sensor Test on ESP32!");

  SPI.begin(MAX_SCK, MAX_MISO, MAX_MOSI, MAX_CS); // Initialize SPI
  thermo.begin(MAX31865_3WIRE);  // Adjust to 2WIRE or 4WIRE if needed
}

void loop() {
  uint16_t rtd = thermo.readRTD();

//  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = (float)rtd / 32768.0;
//  Serial.print("Ratio = "); Serial.println(ratio, 8);
  Serial.print("Resistance = "); Serial.println(RREF * ratio, 8);
  Serial.print("Temperature = "); Serial.println(thermo.temperature(RNOMINAL, RREF));

  // Check and print any faults
  uint8_t fault = thermo.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold");
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold");
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias");
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage");
    }
    thermo.clearFault();
  }
  Serial.println();
  delay(1000);
}
