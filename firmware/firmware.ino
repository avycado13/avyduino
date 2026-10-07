// Avyduino bring-up sketch for the ATmega328P (Arduino Uno pin mapping).
// The CH340G provides the USB serial port; this chip does not run this sketch.
// Connect an external LED + resistor to D13 if you want to see the heartbeat.

constexpr unsigned long kBaudRate = 115200;
constexpr unsigned long kHeartbeatIntervalMs = 500;

unsigned long lastHeartbeatMs = 0;
bool heartbeatHigh = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // D13 / PB5 / SCK
  Serial.begin(kBaudRate);
  Serial.println(F("Avyduino ready. Type to echo; D13 toggles every 500 ms."));
}

void loop() {
  const unsigned long now = millis();
  if (now - lastHeartbeatMs >= kHeartbeatIntervalMs) {
    lastHeartbeatMs = now;
    heartbeatHigh = !heartbeatHigh;
    digitalWrite(LED_BUILTIN, heartbeatHigh ? HIGH : LOW);
  }

  // Echo bytes verbatim so a serial terminal can test RX and TX together.
  while (Serial.available() > 0) {
    Serial.write(Serial.read());
  }
}
