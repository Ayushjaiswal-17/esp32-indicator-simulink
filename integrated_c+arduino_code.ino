// Include generated header
extern "C" {
  #include "IndicatorControlModel.h"
}

// Pins (use any GPIOs)
#define LEFT_LED_PIN     18
#define RIGHT_LED_PIN    19
#define LEFT_BTN_PIN     32
#define RIGHT_BTN_PIN    33

// Inputs to Simulink
extern boolean_T left_button;
extern boolean_T right_button;
extern boolean_T tick_1s;

// Outputs from Simulink
extern boolean_T left_led;
extern boolean_T right_led;
extern uint8_T status;

unsigned long lastTickTime = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
  pinMode(LEFT_BTN_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BTN_PIN, INPUT_PULLUP);

  // Initialize the Simulink model
  IndicatorControlModel_initialize();
}

void loop() {
  // Read buttons (active LOW logic)
  left_button = digitalRead(LEFT_BTN_PIN) == LOW;
  right_button = digitalRead(RIGHT_BTN_PIN) == LOW;

  // Generate tick_1s signal every 1000 ms
  if (millis() - lastTickTime >= 1000) {
    tick_1s = 1;
    lastTickTime = millis();
  } else {
    tick_1s = 0;
  }

  // Run Simulink model step
  IndicatorControlModel_step();

  // Drive LEDs
  digitalWrite(LEFT_LED_PIN, left_led ? HIGH : LOW);
  digitalWrite(RIGHT_LED_PIN, right_led ? HIGH : LOW);

  // Print status to UART
  Serial.print("Status: "); Serial.print(status);
  Serial.print(" | Left_LED: "); Serial.print(left_led);
  Serial.print(" | Right_LED: "); Serial.println(right_led);

  delay(100); // 100 ms scheduler
}
