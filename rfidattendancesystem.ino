#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#include <SPI.h>
#include <MFRC522.h>


#define SS_PIN 10
#define RST_PIN 9
#define Buzzer A0

MFRC522 mfrc522(SS_PIN, RST_PIN);

byte att1 = 0;
byte att2 = 0;

unsigned long startTime = 0;
bool timerRunning = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  SPI.begin();
  mfrc522.PCD_Init();
  
  Serial.println("RFID Attendance System");
  Serial.println("Scan your RFID card to start the timer.");
  lcd.print("RFID Attendance System"); 
  delay(5000);
  lcd.clear();
  lcd.print("Scan your card.");
  delay(2000);
  lcd.clear();
  
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;
  
  String ID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    ID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(mfrc522.uid.uidByte[i], HEX));
    delay(100);
  }
  Serial.println();
  ID.toUpperCase();
  if (ID.substring(1) == "C3 CC 4A FB" && att1 == 0 ) {
        startTimer();
        tone(Buzzer, 12000);
        delay(200);
        noTone(Buzzer);
        
        att1 = 1;
  } else if (ID.substring(1) == "C3 CC 4A FB" && att1 == 1 ) {
        stopTimer();
        tone(Buzzer, 12000);
        delay(400);
        noTone(Buzzer);
        
        att1 = 0;
  } if (ID.substring(1) == "E3 6F 8A F4" && att2 == 0 ) {
        startTimer();
        tone(Buzzer, 12000);
        delay(200);
        noTone(Buzzer);
       
        att2 = 1;
  } else if (ID.substring(1) == "E3 6F 8A F4" && att2 == 1 ) {
        stopTimer();
        tone(Buzzer, 12000);
        delay(400);
        noTone(Buzzer);
        
        att2 = 0;
  }
}

void startTimer() {
  lcd.begin(16,2);
  startTime = millis();
  timerRunning = true;
  Serial.println("Timer started.");
  lcd.print("Timer started");
  delay(1000);
  lcd.clear();
}

void stopTimer() {
  lcd.begin(16,2);
  unsigned long endTime = millis();
  unsigned long elapsedTime = endTime - startTime;
  timerRunning = false;
  Serial.print("Timer stopped.\nElapsed time: ");
  Serial.print(elapsedTime/1000);
  Serial.print(" Seconds\n");
  if (elapsedTime >= 10000) { 
    markPresent();
  } else {
    markAbsent();
  }
}

void markPresent() {
  lcd.begin(16,2);
  Serial.println("Marked present.");
  lcd.print("Marked present.");
  delay(2000);
  lcd.clear();
}

void markAbsent() {
  lcd.begin(16,2);
  Serial.println("Marked absent.");
  lcd.print("Marked absent.");
  delay(2000);
  lcd.clear();
}
