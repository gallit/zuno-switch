const byte _LOOP_DELAY_MS = 200; // Loop delay
byte blinkLedLoopCount = 0; // Blink led loop count
byte pin19;
byte pin20;
byte pin21;
byte pin22;

// Custom battery handler and battery levels
ZUNO_SETUP_BATTERY_HANDLER(getBatteryLeft);
ZUNO_SETUP_BATTERY_LEVELS(0, 3300);

// Switch controls
ZUNO_SETUP_CHANNELS(
  ZUNO_SWITCH_BINARY(getterPin19, setterPin19),
  ZUNO_SWITCH_BINARY(getterPin20, setterPin20),
  ZUNO_SWITCH_BINARY(getterPin21, setterPin21),
  ZUNO_SWITCH_BINARY(getterPin22, setterPin22)
);

// SleepMode disabled
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE);

// Setup is run on
// - Power ON
// - Wake after sleep
void setup() {  
  Serial.begin(9600);
  Serial.println("Starting...");

  // OUTPUT is a low voltage pin mode that works with relay switches
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);

  // Switch OFF Relays
  pin19 = HIGH;
  pin20 = HIGH;
  pin21 = HIGH;
  pin22 = HIGH;

  // Sending report to ZWave controller that should then send a read request
  zunoSendReport(1); // pin19
  zunoSendReport(2); // pin20
  zunoSendReport(3); // pin21
  zunoSendReport(4); // pin22

  blinkLedLoopCount = 10; // Startup
}

// Loop
void loop() {      
  checkPin();
  blinkLed();
  delay(_LOOP_DELAY_MS);
}

// *** User functions ***

void blinkLed() {
  // Blinking Led
  if (blinkLedLoopCount > 0) {
    byte value = digitalRead(LED_BUILTIN);
    Serial.print("Led value = ");
    Serial.print(value);
    Serial.print(" | Count = ");
    Serial.println(blinkLedLoopCount);    
    if (value == 0 && blinkLedLoopCount > 1) {
      digitalWrite(LED_BUILTIN, HIGH);  
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
    }
    blinkLedLoopCount--;
  }
}

// Check pin value and set if required
void checkPin() {
  if (digitalRead(19) != pin19) {
    setterPin19(pin19);
  }
  if (digitalRead(20) != pin20) {
    setterPin20(pin20);
  }
  if (digitalRead(21) != pin21) {
    setterPin21(pin21);
  }
  if (digitalRead(22) != pin22) {
    setterPin22(pin22);
  }      
}

// Custom battery handler, percent left
byte getBatteryLeft() {  
  byte percent = 77;
  Serial.print("getBatteryLeft = ");
  Serial.println(percent);
  return percent;
}

// Returns a LOW / HIGH value
byte getLowHigh(byte value) {
  if (value > 0) {
    value = HIGH;
  }
  else {
    value = LOW;
  }
  return value;
}

byte getPinValue(byte pin) {
  blinkLedLoopCount = 10;
  byte value = digitalRead(pin);  
  Serial.print("Reading PIN");
  Serial.print(pin);
  Serial.print(" value = ");  
  Serial.println(value);
  return value;
}

byte getterPin19() {
  Serial.print("Reading PIN19 = ");
  Serial.println(pin19);
  return pin19;
}

byte getterPin20() {
  Serial.print("Reading PIN20 = ");
  Serial.println(pin20);
  return pin20;
}

byte getterPin21() {
  Serial.print("Reading PIN21 = ");
  Serial.println(pin21);
  return pin21;
}

byte getterPin22() {
  Serial.print("Reading PIN22 = ");
  Serial.println(pin22);
  return pin22;
}

void setPinValue(byte pin, byte value) {
  blinkLedLoopCount = 10;
  Serial.print("Setting PIN");
  Serial.print(pin);
  Serial.print(" to value ");
  Serial.println(value);
  digitalWrite(pin, value);
}

void setterPin19(byte value) {
  pin19 = getLowHigh(value);
  setPinValue(19, pin19);
}

void setterPin20(byte value) {
  pin20 = getLowHigh(value);
  setPinValue(20, pin20);
}

void setterPin21(byte value) {
  pin21 = getLowHigh(value);
  setPinValue(21, pin21);
}

void setterPin22(byte value) {
  pin22 = getLowHigh(value);
  setPinValue(22, pin22);
}
