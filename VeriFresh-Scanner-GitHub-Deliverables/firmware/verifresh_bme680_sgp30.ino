/*
 VeriFresh Scanner: ESP32 DevKit + BME680 + SGP30
 Arduino Library Manager:
   Adafruit BME680 Library
   Adafruit SGP30 Sensor
   Dependencies requested by Library Manager

 I2C: GPIO21 SDA, GPIO22 SCL; common GND.
 Use 3.3 V only if both breakouts support it.
 Outputs sensor responses, NOT specific chemical identification.
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Adafruit_SGP30.h>
#include <math.h>

const int SDA_PIN = 21;
const int SCL_PIN = 22;
const unsigned long INTERVAL_MS = 1000;
Adafruit_BME680 bme;
Adafruit_SGP30 sgp;
bool bmeReady = false;
bool sgpReady = false;
unsigned long lastMs = 0;
unsigned long sampleNo = 0;

void printValue(float v, int decimals) {
  if (isnan(v) || isinf(v)) Serial.print("NA");
  else Serial.print(v, decimals);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(SDA_PIN, SCL_PIN);

  bmeReady = bme.begin(0x77, &Wire);
  if (!bmeReady) bmeReady = bme.begin(0x76, &Wire);
  if (bmeReady) {
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150);
    Serial.println("# BME680 initialized");
  } else {
    Serial.println("# ERROR: BME680 not detected at 0x76 or 0x77");
  }

  sgpReady = sgp.begin(&Wire);
  if (sgpReady) {
    sgp.IAQinit();
    Serial.println("# SGP30 initialized; allow stabilization");
  } else {
    Serial.println("# ERROR: SGP30 not detected (expected 0x58)");
  }
  Serial.println("sample_no,elapsed_ms,bme_temp_c,bme_humidity_pct,bme_pressure_hpa,bme_gas_ohms,sgp_tvoc_ppb,sgp_eco2_ppm");
}

void loop() {
  unsigned long now = millis();
  if (now - lastMs < INTERVAL_MS) return;
  lastMs = now;
  sampleNo++;

  float tempC = NAN, humidity = NAN, pressure = NAN, gasOhms = NAN;
  int tvoc = -1, eco2 = -1;

  if (bmeReady && bme.performReading()) {
    tempC = bme.temperature;
    humidity = bme.humidity;
    pressure = bme.pressure / 100.0F;
    gasOhms = bme.gas_resistance;
  }
  // SGP30 IAQ measurement should be called about once per second.
  if (sgpReady && sgp.IAQmeasure()) {
    tvoc = sgp.TVOC;
    eco2 = sgp.eCO2;
  }

  Serial.print(sampleNo); Serial.print(",");
  Serial.print(now); Serial.print(",");
  printValue(tempC, 2); Serial.print(",");
  printValue(humidity, 2); Serial.print(",");
  printValue(pressure, 2); Serial.print(",");
  printValue(gasOhms, 0); Serial.print(",");
  if (tvoc < 0) Serial.print("NA"); else Serial.print(tvoc);
  Serial.print(",");
  if (eco2 < 0) Serial.println("NA"); else Serial.println(eco2);
}
