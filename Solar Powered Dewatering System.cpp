#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define USE_MQTT false

const char* WIFI_SSID = "YOUR_SSID";
const char* WIFI_PASSWORD = "YOUR_PASSWORD";

const uint8_t PIN_FLOAT_LOW  = D5;
const uint8_t PIN_FLOAT_MID  = D6;
const uint8_t PIN_FLOAT_HIGH = D7;
const uint8_t PIN_PUMP_RELAY = D1;
const uint8_t PIN_BATTERY_ADC = A0;

const float VDIVIDER_RATIO = 4.0f;
const float ADC_MAX_VOLT = 1.0f;
const float ADC_RESOLUTION = 1023.0f;
const float ACS712_SENSITIVITY = 0.185f;
const float VCC = 3.3f;

const float BATTERY_VOLTAGE_MIN = 11.5f;
const float CURRENT_LIMIT_A = 6.0f;

bool pumpState = false;

bool readFloat(uint8_t pin) {
  return digitalRead(pin) == LOW;
}

float readBatteryVoltage() {
  int raw = analogRead(PIN_BATTERY_ADC);
  float adcVoltage = (raw / ADC_RESOLUTION) * ADC_MAX_VOLT;
  return adcVoltage * VDIVIDER_RATIO;
}

float readPumpCurrent() {
  int raw = analogRead(PIN_BATTERY_ADC);
  float adcVoltage = (raw / ADC_RESOLUTION) * ADC_MAX_VOLT;
  float sensorZero = ADC_MAX_VOLT / 2.0;
  float amps = (adcVoltage - sensorZero) / ACS712_SENSITIVITY;
  return fabs(amps);
}

void setPump(bool on) {
  pumpState = on;
  digitalWrite(PIN_PUMP_RELAY, on ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_FLOAT_LOW, INPUT_PULLUP);
  pinMode(PIN_FLOAT_MID, INPUT_PULLUP);
  pinMode(PIN_FLOAT_HIGH, INPUT_PULLUP);
  pinMode(PIN_PUMP_RELAY, OUTPUT);
  setPump(false);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void loop() {
  bool floatLow  = readFloat(PIN_FLOAT_LOW);
  bool floatMid  = readFloat(PIN_FLOAT_MID);
  bool floatHigh = readFloat(PIN_FLOAT_HIGH);

  float batteryVoltage = readBatteryVoltage();
  float pumpCurrent = readPumpCurrent();

  bool wantPump = false;
  if (floatHigh) wantPump = false;
  else if (floatMid) wantPump = true;
  else wantPump = false;

  if (batteryVoltage < BATTERY_VOLTAGE_MIN) wantPump = false;
  if (pumpCurrent > CURRENT_LIMIT_A) wantPump = false;

  if (wantPump != pumpState) setPump(wantPump);

  Serial.printf("LOW:%d MID:%d HIGH:%d  Vbat:%.2fV  I:%.2fA  Pump:%s\n",
                floatLow, floatMid, floatHigh,
                batteryVoltage, pumpCurrent,
                pumpState ? "ON" : "OFF");

  delay(500);
}