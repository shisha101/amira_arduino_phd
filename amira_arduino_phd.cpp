#include <Arduino.h>
#include <Time.h>

const static bool DEBUG_ENABLED = true;
const static unsigned int DELAY_BETWEEN_READINGS_SEC = 5;
const static unsigned int DELAY_BETWEEN_READINGS_M_SEC =
    DELAY_BETWEEN_READINGS_SEC * 1000;

static time_t start_time;
static time_t current_time;

const static uint8_t number_of_analog_pins = 8;
const static uint8_t analog_pins[number_of_analog_pins] = {A0, A1, A2, A3,
                                                           A4, A5, A6, A7};
static int currnet_analog_readings[number_of_analog_pins];
static unsigned long current_reading_number = 0;

void printDebug(const String& debug_msg, bool debug_enabled = DEBUG_ENABLED) {
  if (debug_enabled) {
    Serial.println(String("[DEBUG]: ") + debug_msg);
  }
}

void printDebug(const char* debug_msg) { printDebug(String(debug_msg)); }

void readAnalogValues() {
  for (uint8_t i = 0; i < number_of_analog_pins; i++) {
    currnet_analog_readings[i] = analogRead(analog_pins[i]);
  }
}

String getTimeSinceStart(const time_t& difference) {
  auto duration = difference;
  uint8_t seconds = duration % 60;
  duration /= 60;  // in minutes
  uint8_t minutes = duration % 60;
  duration /= 60;  // in hours
  uint8_t hours = duration % 24;
  uint8_t days = duration / 24;
  String output = String(days) + ":" + String(hours) + ":" + String(minutes) +
                  ":" + String(seconds);
  return output;
}

void logAnalogValues() {
  current_time = now();
  String output = String(current_reading_number) + ", ";
  output += getTimeSinceStart(current_time - start_time);
  for (uint8_t i = 0; i < number_of_analog_pins; i++) {
    output += ", " + String(map(currnet_analog_readings[i], 0, 1023, 0, 100));
  }
  output += "\n";
  current_reading_number++;
  Serial.print(output);
}

void setup() {
  start_time = now();
  Serial.begin(9600);
  analogReference(EXTERNAL);
  Serial.println(
      "Reading Number, Reading Time [d:h:m:s], "
      "A0 Value, A1 Value, A2 Value, A3 Value, "
      "A4 Value, A5 Value, A6 Value, A7 Value");
}

void loop() {
  readAnalogValues();
  logAnalogValues();
  delay(DELAY_BETWEEN_READINGS_M_SEC);
}
