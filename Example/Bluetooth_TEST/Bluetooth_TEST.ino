#include <SparkFun_HM1X_Bluetooth_Arduino_Library.h>

HM1X_BT bt;

#define SerialPort SerialUSB // Abstract serial monitor debug port

// BLE and EDR device names
String edrName = "MyEDR";
String bleName = "MyBLE";

void setup() {
  delay(2000);
  SerialPort.begin(9600); // Serial debug port @ 9600 bps
  //while (!SerialPort.available()) ; // Press a key to begin
  //while (SerialPort.available()) SerialPort.read(); // Clear RX buffer

  // bt.begin --
  // in this case takes a HardwareSerial connection and
  // a desired serial baud rate.
  // Returns true on success
  if (bt.begin(Serial1, 9600) == false) {
    SerialPort.println(F("Failed to connect to the HM-13."));
    while (1) ;
  }
  SerialPort.println("Ready to Bluetooth!");

  boolean resetRequired = false; // Reset is required on name change

  String setEdrName = bt.getEdrName();
  // getEdrName returns a string containing EDR device name
  if (setEdrName != edrName) {
    // If set name is different, configure new EDR name
    SerialPort.println("Setting new EDR name");
    // Set EDR device name
    if (bt.setEdrName(edrName) == HM1X_SUCCESS) {
      Serial.println("Set EDR name to " + edrName);
      resetRequired = true;
    }
  } else {
    Serial.println("EDR name is: " + edrName);
  }
  
  // getBleName returns a string containing BLE device name
  String setBleName = bt.getBleName();
  if (setBleName != bleName) {
    // If set name is different, configure new BLE name
    SerialPort.println("Setting new BLE name");
    // Set BLE device name
    if (bt.setBleName(bleName) == HM1X_SUCCESS) {
      SerialPort.println("Set BLE name");
      resetRequired = true;
    }
  } else {
    SerialPort.println("BLE name is: " + setBleName);
  }
  
  SerialPort.println("EDR address: " + bt.edrAddress());
  SerialPort.println("BLE address: " + bt.bleAddress());

  if (resetRequired) {
    SerialPort.println("Resetting BT module. Wait a few seconds.");
    bt.reset();
  }
}

void loop() {
  if (bt.available()) {
    SerialPort.write((char) bt.read());
  }
  if (SerialPort.available()) {
    bt.write((char) SerialPort.read());
  } 
}
