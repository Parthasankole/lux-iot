#define LDR_PIN 34
#define R_FIXED 10000.0   // 10k ohm resistor
#define VCC 3.3

// Empirical LDR constants (adjust by calibration)
#define A 50000.0
#define GAMMA 0.8

void setup() {
  Serial.begin(115200);

  // ESP32 ADC settings
  analogReadResolution(12);                 // 0–4095
  analogSetPinAttenuation(LDR_PIN, ADC_11db); // Allows full 0–3.3V range
}

void loop() {
  int adcValue = analogRead(LDR_PIN);

  // Convert ADC to voltage
  float voltage = adcValue * (VCC / 4095.0);

  // Avoid division errors
  if (voltage >= (VCC - 0.01)) {
    Serial.println("Too bright / invalid reading");
    delay(1000);
    return;
  }

  // Calculate LDR resistance
  float rLDR = R_FIXED * (voltage / (VCC - voltage));

  // Estimate light intensity in lux
  float lux = pow((A / rLDR), (1.0 / GAMMA));

  // Print results
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | LDR Resistance: ");
  Serial.print(rLDR);
  Serial.print(" ohm | Light Intensity: ");
  Serial.print(lux);
  Serial.println(" lux");

  delay(3000);
}
