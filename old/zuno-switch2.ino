const byte _LOOP_DELAY_MS = 100; // Loop delay
byte blinkLedLoopCount = 0; // Blink led loop count
byte pin03;
byte pin04;
byte pin05;
byte pin06;
byte pin19;
byte pin20;
byte pin21;
byte pin22;

// Custom battery handler and battery levels
ZUNO_SETUP_BATTERY_HANDLER(getBatteryLeft);
ZUNO_SETUP_BATTERY_LEVELS(0, 3300);

// Switch controls
ZUNO_SETUP_CHANNELS(
  ZUNO_SWITCH_BINARY(getterPin03, setterPin03),
  ZUNO_SWITCH_BINARY(getterPin04, setterPin04),
  ZUNO_SWITCH_BINARY(getterPin05, setterPin05),
  ZUNO_SWITCH_BINARY(getterPin06, setterPin06),
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
  //Serial.begin();
  Serial.println("Starting...");

  // OUTPUT is a low voltage pin mode that works with relay switches
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);  
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);

  // Switch OFF Relays
  pin03 = HIGH;
  pin04 = HIGH;
  pin05 = HIGH;
  pin06 = HIGH;  
  pin19 = HIGH;
  pin20 = HIGH;
  pin21 = HIGH;
  pin22 = HIGH;

  // Sending report to ZWave controller that should then send a read request
  zunoSendReport(1); // pin03
  zunoSendReport(2); // pin04
  zunoSendReport(3); // pin05
  zunoSendReport(4); // pin06
  zunoSendReport(5); // pin19
  zunoSendReport(6); // pin20
  zunoSendReport(7); // pin21
  zunoSendReport(8); // pin22  

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
  if (digitalRead(3) != pin03) {
    setterPin03(pin03);
  }
  if (digitalRead(4) != pin04) {
    setterPin04(pin04);
  }
  if (digitalRead(5) != pin05) {
    setterPin05(pin05);
  }
  if (digitalRead(6) != pin06) {
    setterPin06(pin06);
  }        
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

byte getterPin03() {
  Serial.print("Reading PIN03 = ");
  Serial.println(pin03);
  return pin03;
}

byte getterPin04() {
  Serial.print("Reading PIN04 = ");
  Serial.println(pin04);
  return pin04;
}

byte getterPin05() {
  Serial.print("Reading PIN05 = ");
  Serial.println(pin05);
  return pin05;
}

byte getterPin06() {
  Serial.print("Reading PIN06 = ");
  Serial.println(pin06);
  return pin06;
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

void setterPin03(byte value) {
  pin03 = getLowHigh(value);
  setPinValue(3, pin03);
}

void setterPin04(byte value) {
  pin04 = getLowHigh(value);
  setPinValue(4, pin04);
}

void setterPin05(byte value) {
  pin05 = getLowHigh(value);
  setPinValue(5, pin05);
}

void setterPin06(byte value) {
  pin06 = getLowHigh(value);
  setPinValue(6, pin06);
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
