#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <HX711.h>
#include <Ultrasonic.h>

// RFID reader
const int RST_PIN = 5;
const int SS_PIN = 4;
MFRC522 rfid(SS_PIN, RST_PIN);

// Load cell sensor
const int LOAD_CELL_DOUT_PIN = 34;
const int LOAD_CELL_CLK_PIN = 32;
HX711 load_cell(LOAD_CELL_DOUT_PIN, LOAD_CELL_CLK_PIN);

// Ultrasonic sensor
const int TRIG_PIN = 27;
const int ECHO_PIN = 26;
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize RFID reader
  rfid.begin();

  // Initialize load cell sensor
  load_cell.tare();

  // Initialize ultrasonic sensor
  ultrasonic.init();
}

void loop() {
  // Read RFID tag
  String tag_id = rfid.readTag();

  // Read weight
  float weight = load_cell.get_units();

  // Read distance
  float distance = ultrasonic.distance();

  // Print RFID tag, weight, and distance to Serial
  Serial.print("Tag ID: ");
  Serial.println(tag_id);
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" grams");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait for 1 second
  delay(1000);
}
