const byte _LOOP_DELAY_MS = 50; // Loop delay
byte blinkLedLoopCount = 0; // Blink led loop count
unsigned int loopCount = 0; // Blink led loop count

// Switch controls
ZUNO_SETUP_CHANNELS(
  ZUNO_SWITCH_BINARY(switch1Getter, switch1Setter),
  ZUNO_SWITCH_BINARY(switch2Getter, switch2Setter),
  ZUNO_SWITCH_BINARY(switch3Getter, switch3Setter),
  ZUNO_SWITCH_BINARY(switch4Getter, switch4Setter)
);

// SleepMode disabled
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE); // Always ON, no battery meter
//ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE); // FLIRS MAKES ZUNO NOT TO RECEIVE MULTIPLE REQUESTS

// Setup is run on
// - Power ON
// - Wake after sleep
void setup() {  
  Serial.begin(9600);  

  // OUTPUT is a low voltage pin mode that works with relay switches
  pinMode(LED_BUILTIN, OUTPUT);  
  pinMode(3, OUTPUT);    // Switch 1
  pinMode(4, OUTPUT);    // Switch 2
  pinMode(5, OUTPUT);    // Switch 3
  pinMode(6, OUTPUT);    // Switch 4

  // Switch OFF Relays  
  setSwitchValue(1, LOW);
  setSwitchValue(2, LOW);
  setSwitchValue(3, LOW);
  setSwitchValue(4, LOW);  
  
  zunoSendReport(1);
  zunoSendReport(2);
  zunoSendReport(3);
  zunoSendReport(4);  

  blinkLedLoopCount = 20; // Startup
}

// Loop
void loop() {      
  blinkLed();
  loopCount++;
  
  if (loopCount > 1000) {
    blinkLedLoopCount = 5;
    Serial.println("zuno-switch v5 b20241223.2"); 
    zunoSendReport(1);
    zunoSendReport(2);
    zunoSendReport(3);
    zunoSendReport(4);
    loopCount = 0;
  }  
  
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
    //Serial.print("BlinkLed ");
    //Serial.println(blinkLedLoopCount);
    blinkLedLoopCount--;
  }
}

byte getPinForChannel(byte channel) {
  byte r = 0;
  if (channel == 1) {
    r = 3;
  }
  else if (channel == 2) {
    r = 4;
  }
  else if (channel == 3) {
    r = 5;
  }
  else if (channel == 4) {
    r = 6;
  }
  else if (channel == 5) {
    r = 19;
  }
  else if (channel == 6) {
    r = 20;
  }
  else if (channel == 7) {
    r = 21;
  }
  else if (channel == 8) {
    r = 22;
  }
  return r;
}

byte getPinValue(byte pin) {
  blinkLedLoopCount = 5;
  byte r = digitalRead(pin);  
  Serial.print("getPinValue(");
  Serial.print(pin);
  Serial.print(") = ");
  Serial.print(r);
  if (r == LOW) {
    Serial.println(" (LOW)");
  }
  else if (r == HIGH) {
    Serial.println(" (HIGH)");
  }
  else {
    Serial.println(" (UNKNOWN)");
  }
  return r;
}

byte getSwitchValue(byte channel) {  
  byte pin = getPinForChannel(channel);
  byte r = getPinValue(pin);  
  Serial.print("getSwitchValue(");
  Serial.print(channel);
  Serial.print(") = ");
  Serial.print(r);
  if (r == LOW) {
    Serial.println(" (OFF)");
    r = 0;
  }
  else if (r == HIGH) {
    Serial.println(" (ON)");
    r = 255;
  }
  else {
    Serial.println(" (UNKNOWN)");
    r = 0;
  }
  return r;
}

void setPinValue(byte pin, byte v) {  
  Serial.print("setPinValue(");
  Serial.print(pin);
  Serial.print(") = ");
  Serial.print(v);
  Serial.println("");
  blinkLedLoopCount = 10;
  digitalWrite(pin, v);  
}

void setSwitchValue(byte channel, byte v) {
  Serial.print("setSwitchValue(");
  Serial.print(channel);
  Serial.print(") = ");
  Serial.print(v);
  Serial.println("");

  byte pin = getPinForChannel(channel);
  if (v == 255) {
    v = HIGH;
  }
  else {
    v = LOW;
  }
  setPinValue(pin, v);
}

byte switch1Getter() {
  return getSwitchValue(1);
}

void switch1Setter(byte value) {
  setSwitchValue(1, value);
}

byte switch2Getter() {
  return getSwitchValue(2);
}

void switch2Setter(byte value) {
  setSwitchValue(2, value);
}

byte switch3Getter() {
  return getSwitchValue(3);
}

void switch3Setter(byte value) {
  setSwitchValue(3, value);
}

byte switch4Getter() {
  return getSwitchValue(4);
}

void switch4Setter(byte value) {
  setSwitchValue(4, value);
}
