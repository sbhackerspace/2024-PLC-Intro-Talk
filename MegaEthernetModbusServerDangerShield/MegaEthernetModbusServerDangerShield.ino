/*
  created 16 July 2018 by Sandeep Mistry
  Modifed for danger shield 2024 Nick Winters
  Using:
   - Arduino Mega 2560
   - Ethernet shield
   - Sparkfun Danger Shield v17 https://www.sparkfun.com/products/retired/10115

  Unfortunately this sample is written for only one modbus TCP connection at a time.
*/

#include <SPI.h>
#include <Ethernet.h>

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(172, 16, 0, 11);

EthernetServer ethServer(502);

ModbusTCPServer modbusTCPServer;

const int ledPin = LED_BUILTIN;

// Danger shield pin definitions
#define SLIDER1  2
#define SLIDER2  1
#define SLIDER3  0
// BUTTON1 conflicts with Ethernet shield CS pin
// #define BUTTON1  10
#define BUTTON2  11
#define BUTTON3  12
#define TEMP  4
#define LIGHT  3
// outputs:
#define LED1  5
#define LED2  6
#define BUZZER   3
#define LATCH 7
#define CLOCK 8
#define DATA 4

// Shift register bit values to display 0-9 on the seven-segment display
const byte ledCharSet[16] = {
  B00111111,B00000110,B01011011,B01001111,B01100110,B01101101,B01111101,B00000111,B01111111,B01101111,
// HGFEDCBA
  B01110111,
  B01111100,
  B00111001,
  B01011110,
  B01111001,
  B01110001
};

unsigned long next_anim_millis;
int anim_state;

void setup() {
  // initalize animation state for when no connection
  anim_state = 0;
  next_anim_millis = millis();

  // danger shield:
  
  // inputs:
  // pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  // analog inputs:
  // SLIDER1
  // SLIDER2
  // SLIDER3
  // TEMP
  // LIGHT
  
  pinMode(BUZZER, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA,OUTPUT);

  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  pinMode(BUZZER, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(19200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet Danger Shield Modbus TCP Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  ethServer.begin();
  
  // start the Modbus TCP server
  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }

  // configure a single coil at address 0x00
  // modbusTCPServer.configureCoils(0x00, 1);
  
  modbusTCPServer.configureHoldingRegisters(0x00, 12);
}


void loop() {
  // listen for incoming clients
  EthernetClient client = ethServer.available();
  
  if (client) {
    // a new client connected
    Serial.println("new client");

    // let the Modbus TCP accept the connection 
    modbusTCPServer.accept(client);

    while (client.connected()) {
      // poll for Modbus TCP requests, while client connected
      modbusTCPServer.poll();

      updateDangerShield();
    }

    Serial.println("client disconnected");
  }

  // play animation when not connected
  if (millis() > next_anim_millis) {
    next_anim_millis = millis() + 350;

    // light up one of the 7 segments
    uint16_t hexVal = ~(1 << anim_state);
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLOCK,MSBFIRST,hexVal);
    digitalWrite(LATCH,HIGH);

    anim_state += 1;
    if (anim_state > 5) {
      anim_state = 0;
    }    
  }
}

void updateDangerShield() {
  // outputs:
  modbusTCPServer.holdingRegisterWrite(0x00, analogRead(SLIDER1));
  modbusTCPServer.holdingRegisterWrite(0x01, analogRead(SLIDER2));
  modbusTCPServer.holdingRegisterWrite(0x02, analogRead(SLIDER3));
  modbusTCPServer.holdingRegisterWrite(0x03, analogRead(TEMP));
  modbusTCPServer.holdingRegisterWrite(0x04, analogRead(LIGHT));
  // modbusTCPServer.holdingRegisterWrite(0x05, !digitalRead(BUTTON1));
  modbusTCPServer.holdingRegisterWrite(0x06, !digitalRead(BUTTON2));
  modbusTCPServer.holdingRegisterWrite(0x07, !digitalRead(BUTTON3));

  // inputs:
  digitalWrite(LED1, 0 != modbusTCPServer.holdingRegisterRead(0x08));
  digitalWrite(LED2, 0 != modbusTCPServer.holdingRegisterRead(0x09));
  
  long freq = modbusTCPServer.holdingRegisterRead(0x0A);
  if (freq > 0 && freq < 0xFFFF) {
    tone(BUZZER, freq);
  } else {
    noTone(BUZZER);
  }
  
  // 7 segment
  uint16_t hexVal = 0xF & modbusTCPServer.holdingRegisterRead(0x0B);
  digitalWrite(LATCH,LOW);
  shiftOut(DATA,CLOCK,MSBFIRST,~(ledCharSet[hexVal]));
  digitalWrite(LATCH,HIGH);
}

