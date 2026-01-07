#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>

//Pin setup
const int SERVO_PIN = 3;
const int BT_TX  =10;
const int BT_RX  = 11;
const int RED_LED  = 8  ;   
const int GREEN_LED =  13;
const int BUZZER_PIN  = 9;

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 2, 4, 5, 6, 7);
SoftwareSerial bluetooth(BT_TX, BT_RX);
Servo myservo1;

//  Variables 
int unlockValue = 65;   // Threshold to unlock
bool isLocked = true;
int failedAttempts = 0;
int maxAttempts = 3;

void setup() {
  myservo1.attach(SERVO_PIN);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  bluetooth.begin(9600);
  lcd.begin(16, 2);

  lcd.clear();
  lcd.print("Smart Lock Ready");
  Serial.println("System ready — send value = 65 to unlock.");

  lockDoor();
}

void loop() {
  if (bluetooth.available()) {
    String input = bluetooth.readStringUntil('\n');
    int val = input.toInt();

    Serial.print("Received value: ");
    Serial.println(val);

    if (val >= unlockValue && isLocked) {
      failedAttempts = 0;  // Reset on success
      unlockDoor();
    }
    else if (val < unlockValue && isLocked) {
      failedAttempts++;
      lcd.clear();
      lcd.println("Access Denied");
      lcd.clear();
      lcd.print("Wrong attempt #");
      lcd.println(failedAttempts);

      // Normal beep
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);
      digitalWrite(BUZZER_PIN, LOW);

      // Alarm after 3 failed attempts
      if (failedAttempts >= maxAttempts) {
        lcd.clear();
        lcd.print("ALARM TRIGGERED!");
        lcd.clear();
        lcd.println("Too many failed attempts!");

        for (int i = 0; i < 5; i++) {
          digitalWrite(BUZZER_PIN, HIGH);
          delay(500);
          digitalWrite(BUZZER_PIN, LOW);
          delay(300);
        }

        failedAttempts = 0;  // Reset after alarm
      }
    }
  }
}

//  Lock Door 
void lockDoor() {
  myservo1.write(0);  // Closed position
  delay(500);         // Allow servo to move
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  isLocked = true;
  lcd.clear();
  lcd.print("Door Locked");
  Serial.println("Door Locked");
}

//  Unlock Door with Countdown 
void unlockDoor() {
  myservo1.write(90);  // Open position
  delay(500);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  isLocked = false;

  lcd.clear();
  lcd.print("Door Unlocked");
  Serial.println("Door Unlocked");

  // Countdown to auto-lock
  for (int i = 10; i > 0; i--) {
    lcd.setCursor(0, 1);
    lcd.print("Locking in: ");
    lcd.print(i);
    lcd.print("  ");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(900);
  }

  lockDoor();
}