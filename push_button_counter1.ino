#include <LiquidCrystal.h>

// LCD pin connections: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int tempPin = A0;
const int buttonPin = 7;

int counter = 0;
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Start serial monitor

  lcd.setCursor(0, 0);
  lcd.print("Temp & Counter");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Temperature
  int reading = analogRead(tempPin);
  float voltage = reading * 5.0 / 1023.0;
  float temperatureC = voltage * 100.0;

  // Push Button Counter
  bool readingButton = digitalRead(buttonPin);
  if (readingButton == HIGH && lastButtonState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    counter++;
    lastDebounceTime = millis();
  }
  lastButtonState = readingButton;

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC, 1);
  lcd.print(" C   ");

  lcd.setCursor(0, 1);
  lcd.print("Count: ");
  lcd.print(counter);
  lcd.print("     ");

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" C\t");

  Serial.print("Count: ");
  Serial.println(counter);

  delay(200);
}
