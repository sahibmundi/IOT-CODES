const int LDR_PIN = 34;   // LDR sensor connected to GPIO 34
const int RELAY_PIN = 25; // Relay control pin connected to GPIO 25

void setup() {
  Serial.begin(115200);   // Initialize serial communication at 115200 baud rate
  pinMode(LDR_PIN, INPUT);// Set GPIO 34 as an input
  pinMode(RELAY_PIN, OUTPUT); // Set GPIO 25 as an output
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  int mappedValue = map(ldrValue, 1600, 4095, 0, 100); // Map the LDR value to a 0-100 range

  Serial.print("LDR Value: ");
  Serial.println(mappedValue); // Print the mapped LDR value to the serial monitor

  // Determine when to activate the relay based on LDR value
  if (mappedValue < 50) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the relay
    Serial.println("Relay turned ON");
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay
    Serial.println("Relay turned OFF");
  }

  delay(1000); // Wait for 1 second before taking the next reading
}
