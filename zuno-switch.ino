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
byte pinVirt01;
byte pinVirt02;
unsigned int setterLoopCountVirt01;
unsigned int setterLoopCountVirt02;
// Switch controls
ZUNO_SETUP_CHANNELS(
  ZUNO_SWITCH_BINARY(pin03, NULL),
  ZUNO_SWITCH_BINARY(pin04, NULL),
  ZUNO_SWITCH_BINARY(pin05, NULL),
  ZUNO_SWITCH_BINARY(pin06, NULL),
  ZUNO_SWITCH_BINARY(pin19, NULL),
  ZUNO_SWITCH_BINARY(pin20, NULL),
  ZUNO_SWITCH_BINARY(pin21, NULL),
  ZUNO_SWITCH_BINARY(pin22, NULL),
  ZUNO_SWITCH_BINARY(pinVirt01, NULL),
  ZUNO_SWITCH_BINARY(pinVirt02, NULL)
);

// SleepMode disabled
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE); // Always ON, no battery meter
//ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE); // FLIRS MAKES ZUNO NOT TO RECEIVE MULTIPLE REQUESTS

// Setup is run on
// - Power ON
// - Wake after sleep
void setup() {  
  Serial.begin(9600);
  //Serial.begin();
  Serial.println("Starting zuno-switch4 b20241221.1 ...");

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
  pin03 = LOW;
  pin04 = LOW;
  pin05 = LOW;
  pin06 = LOW;  
  pin19 = LOW;
  pin20 = LOW;
  pin21 = LOW;
  pin22 = LOW;
  pinVirt01 = LOW;
  pinVirt02 = LOW;
  
  setPinValue(1, 3, pin03);
  setPinValue(2, 4, pin04);
  setPinValue(3, 5, pin05);
  setPinValue(4, 6, pin06);
  setPinValue(5, 19, pin19);
  setPinValue(6, 20, pin20);
  setPinValue(7, 21, pin21);
  setPinValue(8, 22, pin22);
  
  zunoSendReport(1);
  zunoSendReport(2);
  zunoSendReport(3);
  zunoSendReport(4);
  zunoSendReport(5);
  zunoSendReport(6);
  zunoSendReport(7);
  zunoSendReport(8);

  zunoSendReport(9);  // pinvirt01  
  zunoSendReport(10); // pinvirt02

  blinkLedLoopCount = 10; // Startup
}

// Loop
void loop() {      
  blinkLed();

  if (zunoIsChannelUpdated(1)) {
    setPinValue(1, 3, pin03);
  }
  if (zunoIsChannelUpdated(2)) {
    setPinValue(2, 4, pin04);
  }
  if (zunoIsChannelUpdated(3)) {
    setPinValue(3, 5, pin05);
  }
  if (zunoIsChannelUpdated(4)) {
    setPinValue(4, 6, pin06);
  }
  if (zunoIsChannelUpdated(5)) {
    setPinValue(5, 19, pin19);
  }
  if (zunoIsChannelUpdated(6)) {
    setPinValue(6, 20, pin20);
  }
  if (zunoIsChannelUpdated(7)) {
    setPinValue(7, 21, pin21);
  }
  if (zunoIsChannelUpdated(8)) {
    setPinValue(8, 22, pin22);
  }
  if (zunoIsChannelUpdated(9)) {
    setPinVirtValue(9, 1, pinVirt01);
  }
  if (zunoIsChannelUpdated(10)) {
    setPinVirtValue(10, 2, pinVirt02);
  }
  
  
  //delay(_LOOP_DELAY_MS);
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

// Returns a LOW / HIGH value
byte getLowHigh(byte value) {
  byte r = HIGH;
  if (value > 0) {
    r = LOW;
  }
  return r;
}

// channel = ZWave channel, pin = associated pin
byte getPinValue(byte channel, byte pin) {
  blinkLedLoopCount = 10;
  byte value = digitalRead(pin);  
  Serial.print("Reading C");
  Serial.print(channel);
  Serial.print(".PIN");
  Serial.print(pin);
  Serial.print(" = ");  
  Serial.println(value);
  return value;
}

// vIndex = Virtual pin index
// 1 = 1 to 4
// 2 = 5 to 8
byte getPinVirtValue(byte vIndex) {
  byte r = vIndex == 1 ? 
    getLowHigh(pin03 + pin04 + pin05 + pin06) :
    getLowHigh(pin19 + pin20 + pin21 + pin22);
  Serial.print("Reading PinVirt");
  Serial.print(vIndex);
  Serial.print(" = ");
  Serial.println(r);  
  return r;
}

// channel = zwave channel index
void setPinValue(byte channel, byte pin, byte value) {
  blinkLedLoopCount = 10;
  value = getLowHigh(value);
  Serial.print("Setting C"); 
  Serial.print(channel);
  Serial.print(".PIN");
  Serial.print(pin);
  Serial.print(" to value ");
  Serial.println(value);
  digitalWrite(pin, value);
  
  byte r = digitalRead(pin);
  if (r != value) {
    Serial.print("Warning : digitalWrite failure on PIN");
    Serial.print(pin);
    Serial.print(". Expected : ");
    Serial.print(value);
    Serial.print(" / Read : ");
    Serial.println(r);
  }
  zunoSendReport(channel);
}

void setPinVirtValue(byte channel, byte vIndex, byte value) {
  // value = getLowHigh(value);
  Serial.print("Setting C");
  Serial.print(channel); 
  Serial.print(".PinVirt");
  Serial.print(vIndex);
  Serial.print(" to value ");
  Serial.println(value);

  if (vIndex == 1) {
    pin03 = value;
    pin04 = value;
    pin05 = value;
    pin06 = value;
    setPinValue(1, 3, value);
    setPinValue(2, 4, value);
    setPinValue(3, 5, value);
    setPinValue(4, 6, value);
  }
  else if (vIndex == 2) {
    pin19 = value;
    pin20 = value;
    pin21 = value;
    pin22 = value;
    setPinValue(5, 19, value);
    setPinValue(6, 20, value);
    setPinValue(7, 21, value);
    setPinValue(8, 22, value);
  }
  else {
    Serial.print("setPinVirtValue error, unmanaged vIndex value");
    Serial.println(vIndex);
  }
  zunoSendReport(channel);
}
