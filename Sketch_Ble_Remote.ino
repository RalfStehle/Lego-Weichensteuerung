/*
  ESP32 BLE Receiving data from your phone over Bluetooth low energy

  https://github.com/arduino-libraries/ArduinoBLE/blob/master/examples/Peripheral/CallbackLED/CallbackLED.ino
  https://github.com/espressif/arduino-esp32/blob/master/libraries/BLE/examples/BLE_uart/BLE_uart.ino
  https://www.electronicshub.org/esp32-ble-tutorial/
*/


#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <Servo.h>  // ServoESP32 von RoboticsBrno

// uuid mit https://www.uuidgenerator.net/ erstellt
#define SERVICE_UUID "196988b3-b878-4b5b-a4cc-2e3eb64c1e00"
#define CHARACTERISTIC_UUID "196988b4-b878-4b5b-a4cc-2e3eb64c1e00"


BLECharacteristic *pCharacteristic;
BLEAdvertising *pAdvertising;
BLEServer *pServer;

bool deviceConnected = false;
int switchStatus1 = 0;
int switchStatus2 = 0;

// die beiden Servopositionen können justiert werden durch Senden
// der 2 Werte für pos1 und pos2, getrennt durch # ( z.B. 0#120 )
int servopos1 = 0;    // Servo Ausgangsstellung eingefahren
int servopos2 = 120;  // Servo ausgefahren

static const int servoPin1 = 12;
static const int servoPin2 = 14;

Servo servo1;
Servo servo2;


#define Gelb 4    // Weiche 1
#define Rot 16    // Weiche 2
#define Blau 17   // Bluetooth Connect On/Off

void weichensteuerung(String);
void servoJustieren(String);

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0) {
      Serial.println("Received value");
      String s = "";

      for (int i = 0; i < value.length(); i++) {
        Serial.print(value[i]);
        s = s + value[i];
      }

      // Do stuff based on th command received from th app
      if (value.find("1") != -1) {
        weichensteuerung("1");
      } else if (value.find("2") != -1) {
        weichensteuerung("2");
      }

      if (value.find("#") != -1) {
        servoJustieren(s);
      }
    }
  }
};


void setup() {

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  servo1.write(servopos1);
  servo2.write(servopos1);

  pinMode(Blau, OUTPUT);
  pinMode(Gelb, OUTPUT);
  pinMode(Rot, OUTPUT);

  Serial.begin(115200);
  Serial.println("Starte Bluetooth...");


  BLEDevice::init("ESP32: Control1");
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  //BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_INDICATE  | BLECharacteristic::PROPERTY_NOTIFY)

  pServer->setCallbacks(new MyServerCallbacks());
  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Seeed Xiao ESP32 C3 is online");
  pService->start();

  //pAdvertising = pServer->getAdvertising();
  pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->start();
}

void loop() {

  if (deviceConnected) {
    digitalWrite(Blau, HIGH);
    delay(1000);
  }

  delay(1000);

  if (!deviceConnected) {
    digitalWrite(Blau, LOW);
    // Verbindung ging verloren, daher advertising starten
    pAdvertising->start();
    Serial.println("");
    Serial.println("advertising....");
    delay(1000);
  }
}

void weichensteuerung(String s) {
  if (s == "1") {
    if (switchStatus1 == 0) {
      switchStatus1 = 1;
      Serial.println("Switch ->");
      servo1.write(servopos1);
      digitalWrite(Gelb, HIGH);
    } else if (switchStatus1 == 1) {
      switchStatus1 = 0;
      Serial.println("Switch <-");
      servo1.write(servopos2);
      for (int i = 1; i <= 5; i++) {
        digitalWrite(Gelb, HIGH);
        delay(150);
        digitalWrite(Gelb, LOW);
        delay(150);
      }
    }
  }

  if (s == "2") {
    if (switchStatus2 == 0) {
      switchStatus2 = 1;
      Serial.println("Switch ->");
      servo2.write(servopos1);
      digitalWrite(Rot, HIGH);
    } else if (switchStatus2 == 1) {
      switchStatus2 = 0;
      Serial.println("Switch <-");
      servo2.write(servopos2);
      for (int i = 1; i <= 5; i++) {
        digitalWrite(Rot, HIGH);
        delay(150);
        digitalWrite(Rot, LOW);
        delay(150);
      }
    }
  }
}

void servoJustieren(String s) {
  String sp1 = "0";
  String sp2 = "120";
  // die zwei Werte werden als String gesendet. # =Delimiter z.B. 0#120
  sp1 = s.substring(0, s.indexOf("#"));
  sp2 = s.substring(s.indexOf("#") + 1, s.length());

  servopos1 = sp1.toInt();
  servopos2 = sp2.toInt();
  Serial.println("Servo justieren - Neue Werte:");
  Serial.println(sp1);
  Serial.println(sp2);
}
