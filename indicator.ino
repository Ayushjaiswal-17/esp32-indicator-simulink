// Pin configuration
const int leftLED = 18;   // You can choose any GPIO pin
const int rightLED = 19;  // You can change pins as needed

bool leftOn = false;
bool rightOn = false;
bool ledState = false;

unsigned long lastBlinkTime = 0;

void setup() {
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  Serial.begin(115200);
  Serial.println("ESP32 Indicator System Ready");
  Serial.println("Type 'L' = Left, 'R' = Right, 'H' = Hazard, 'O' = OFF");
}

void loop() {
  // Read serial input
  if (Serial.available()) {
    char input = Serial.read();

    if (input == 'L' || input == 'l') {
      leftOn = !leftOn;
      rightOn = false;
      Serial.println("Left Indicator Toggled");
    } 
    else if (input == 'R' || input == 'r') {
      rightOn = !rightOn;
      leftOn = false;
      Serial.println("Right Indicator Toggled");
    } 
    else if (input == 'H' || input == 'h') {
      leftOn = true;
      rightOn = true;
      Serial.println("Hazard Mode ON");
    } 
    else if (input == 'O' || input == 'o') {
      leftOn = false;
      rightOn = false;
      Serial.println("All Indicators OFF");
    }
  }

  // LED blinking logic every 300 ms
  unsigned long currentTime = millis();
  if (currentTime - lastBlinkTime > 300) {
    ledState = !ledState;
    lastBlinkTime = currentTime;
  }

  digitalWrite(leftLED, leftOn && ledState);
  digitalWrite(rightLED, rightOn && ledState);
}

