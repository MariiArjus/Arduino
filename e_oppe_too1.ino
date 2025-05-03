const int ledPins[] = {2, 3, 4, 5};
const int buttonPin = 6;

bool isRunning = true;
bool lastButton = HIGH;
unsigned long lastTime = 0;
int currentLED = 0;
int cycleCount = 0; // loeb tsükkleid

void setup() {
  Serial.begin(9600); // alustab serial monitori
  for (int i = 0; i < 4; i++) pinMode(ledPins[i], OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // vahetab nupu olekut (on ja off)
  bool btn = digitalRead(buttonPin);
  if (btn == LOW && lastButton == HIGH) {
    isRunning = !isRunning;
    if (!isRunning) allOff();
    delay(200);
  }
  lastButton = btn;

  if (isRunning && millis() - lastTime > 100) {
    lastTime = millis();
    allOff();
    digitalWrite(ledPins[currentLED], HIGH);
    currentLED = (currentLED + 1) % 4;

    // kui üks tsükkel on läbi, hakkab teist lugema
    if (currentLED == 0) {
      cycleCount++;
      Serial.print("Tsükkel: ");
      Serial.println(cycleCount);
    }
  }
}

// lülitab LED-id välja
void allOff() {
  for (int i = 0; i < 4; i++) digitalWrite(ledPins[i], LOW);
}
//töö asub siin: https://www.tinkercad.com/things/iK1Wd9Ycwww-e-oppe-too/editel
