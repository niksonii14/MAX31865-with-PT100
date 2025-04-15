#include <Adafruit_MAX31865.h>
#include <SPI.h>

// Define SPI pins for ESP32
#define MAX_MISO 19  // MISO
#define MAX_MOSI 23  // MOSI
#define MAX_SCK  18  // SCK
#define MAX_CS1  5   // CS for first MAX31865
#define MAX_CS2  17  // CS for second MAX31865

// Create two sensor objects with different CS pins
Adafruit_MAX31865 thermo1 = Adafruit_MAX31865(MAX_CS1);
Adafruit_MAX31865 thermo2 = Adafruit_MAX31865(MAX_CS2);

// The value of the Rref resistor. Use 430.0 for PT100
#define RREF      430.0
#define RNOMINAL  100.0

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit MAX31865 Dual PT100 Sensor Test on ESP32");

  SPI.begin(MAX_SCK, MAX_MISO, MAX_MOSI);  // Shared SPI bus

  thermo1.begin(MAX31865_3WIRE);  // Configure first sensor (3-wire, adjust if needed)
  thermo2.begin(MAX31865_3WIRE);  // Configure second sensor
}

void readSensor(Adafruit_MAX31865 &sensor, const char* label) {
  uint16_t rtd = sensor.readRTD();
  float ratio = (float)rtd / 32768.0;
  float resistance = RREF * ratio;
  float temperature = sensor.temperature(RNOMINAL, RREF);

  Serial.print(label); Serial.print(" - Resistance = ");
  Serial.println(resistance, 8);
  Serial.print(label); Serial.print(" - Temperature = ");
  Serial.println(temperature);

  // Check and print faults
  uint8_t fault = sensor.readFault();
  if (fault) {
    Serial.print(label); Serial.print(" - Fault 0x"); Serial.println(fault, HEX);
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
    sensor.clearFault();
  }
  Serial.println();
}

void loop() {
  readSensor(thermo1, "Sensor 1");
  readSensor(thermo2, "Sensor 2");
  delay(1000);
}
