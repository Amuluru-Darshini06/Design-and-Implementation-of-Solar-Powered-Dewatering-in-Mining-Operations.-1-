# Design-and-Implementation-of-Solar-Powered-Dewatering-in-Mining-Operations.

# Solar-Powered Dewatering System (ESP8266/NodeMCU)

An *IoT-enabled solar-powered dewatering system* designed for mining and agricultural applications.
This project uses an ESP8266 (NodeMCU) to monitor *water levels, battery voltage, and pump current* while automatically controlling a water pump. It ensures *safe operation, prevents battery over-discharge, and supports **MQTT telemetry* for remote monitoring.

---

## ✨ Features

* 🌞 Powered by *solar energy* with battery backup
* 💧 *Three float switches* (LOW, MID, HIGH) for water level sensing
* 🔋 *Battery voltage monitoring* with safety cutoffs
* ⚡ *Pump current sensing* with overcurrent protection
* 🔄 Automatic pump control logic
* 📡 *Optional MQTT integration* for IoT dashboards
* 🖥 Serial debugging output for testing

## 🛠 Hardware Requirements

* ESP8266 (NodeMCU)
* Solar panel + charge controller + 12V battery
* Relay module (for pump control)
* Water level float switches (3x)
* ACS712 current sensor
* Voltage divider for battery monitoring

---

## 📂 Project Files

* solar_dewatering_nodeMCU.ino → Main Arduino sketch
* (Optional) README.md → This documentation
## 🚀 Getting Started

1. Clone this repository

   bash
   git clone https://github.com/your-username/solar-dewatering.git
   cd solar-dewatering
   
2. Open solar_dewatering_nodeMCU.ino in Arduino IDE.
3. Install required libraries:

   * *ESP8266WiFi* (built-in)
   * *PubSubClient* (for MQTT, optional)
4. Update WiFi and MQTT credentials in the code.
5. Upload to NodeMCU and open Serial Monitor.
## 📊 Control Logic

* ✅ Pump *ON* when water level ≥ MID and battery voltage is safe.
* ⛔ Pump *OFF* when water level ≤ LOW, tank is FULL (HIGH float), battery too low, or current exceeds limit.

---

## 📡 MQTT Topics (optional)

* dewatering/status → Pump ON/OFF status
* dewatering/telemetry → JSON telemetry (levels, voltage, current, pump state)

---

## 📜 License

This project is released under the *MIT License*.
Feel free to use, modify, and share.

---

## 💡 Future Improvements

* ESP32 support with dual ADC inputs
* Integration with *Blynk / Node-RED / ThingsBoard* dashboards
* Data logging to SD card or cloud
* Automatic pump scheduling
## Prototype Image
![Image](https://github.com/user-attachments/assets/1aada7f6-d746-4d1b-b033-aa9205dbd7a9)

----

## Demo video 
https://youtu.be/ixLTgRtjCVU
