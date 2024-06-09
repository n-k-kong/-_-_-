#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// RFID 모듈 핀 설정
#define SS_PIN 7
#define RST_PIN 6
#define BUZZER_PIN 5

// RGB LED 핀 설정
int redPin = 2;
int greenPin = 3;
int bluePin = 4;

// 압력센서 정의
int sensor = A3;

// LCD 설정
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C 주소 0x3F 또는 0x27

// RFID 라이브러리 생성
MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

// 특정 UID 정의 (부저가 1초 동안 울리고 LED가 핑크색으로 켜지며 메시지를 표시할 UID)
byte specificUid1[4] = {0x90, 0x3C, 0x94, 0x26}; // 기존 UID
byte specificUid2[4] = {0x80, 0x80, 0xA9, 0x26}; // 새로운 UID

// 진동모듈 정의
int vibrationPin = 8;

// 카드 감지 횟수
int specificCard1DetectionCount = 0;
int specificCard2DetectionCount = 0;

// 마지막으로 감지된 카드 UID
byte lastDetectedUid[4] = {0, 0, 0, 0};

byte im1[8] =
{
0b00000,
0b00110,
0b01001,
0b01001,
0b00110,
0b00000,
0b00000,
0b00000
};

byte im2[8] =
{
0b00000,
0b00100,
0b00100,
0b00100,
0b00000,
0b11100,
0b10100,
0b11100
};

byte san1[8] =
{
0b00000,
0B00100,
0B01010,
0B10001,
0B10000,
0B00000,
0B00000,
0B00000
};

byte san2[8] =
{
0b00000,
0B00100,
0B00110,
0B00100,
0B00000,
0B10000,
0B10000,
0B11100
};

byte bu1[8] =
{
0B00000,
0B00100,
0B00111,
0B00111,
0B00000,
0B01111,
0B00001,
0B00001
};


byte bu2[8] =
{
0B00000,
0B01000,
0B11000,
0B11000,
0B00000,
0B11100,
0B00000,
0B00000
};

byte ga1[8] =
{
0b00000,
0b00111,
0b00001,
0b00001,
0B00000,
0B00000,
0b00000,
0b00000
};

byte ga2[8] =
{
0b00000,
0b00100,
0b00110,
0b00100,
0B00000,
0B00000,
0b00000,
0b00000
};


byte top1[8] =
{
  0B00000,
  0B00111,
  0B00000,
  0B00111,
  0B00100,
  0B00111,
  0B00000,
  0B00000
};

byte top2[8] =
{
  0b00000,
  0b00100,
  0b00110,
  0b00100,
  0B00000,
  0B10100,
  0b11100,
  0b11100
};

byte tmd1[8] =
{
  0B00000,
  0B00001,
  0B00010,
  0B00000,
  0B00011,
  0B00000,
  0B00001,
  0B00000
};

byte tmd2[8] =
{
  0B00000,
  0B10000,
  0B01000,
  0B00000,
  0B11000,
  0B00000,
  0B10000,
  0B00000
};

byte hat1[8] =
{
  0B00110,
  0B01111,
  0B00000,
  0B00100,
  0B01010,
  0B00100,
  0B00001,
  0B00010
};

byte hat2[8] =
{
  0B00000,
  0B10100,
  0B11100,
  0B10100,
  0B00000,
  0B00000,
  0B01000,
  0B10100
};

byte tmq1[8] =
{
  0B00001,
  0B00010,
  0B00100,
  0B00000,
  0B00111,
  0B00000,
  0B00010,
  0B00011
};

byte tmq2[8] =
{
  0B00000,
  0B10000,
  0B01000,
  0B00000,
  0B11000,
  0B00000,
  0B10000,
  0B10000
};


byte ni1[8] =
{
  0B00000,
  0B00100,
  0B00100,
  0B00111,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

byte ni2[8] =
{
  0B00000,
  0B00100,
  0B00100,
  0B00100,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

byte da1[8] =
{
  0B00000,
  0B00111,
  0B00100,
  0B00100,
  0B00111,
  0B00000,
  0B00000,
  0B00000
};

byte da2[8] =
{
  0B00000,
  0B00100,
  0B00110,
  0B00100,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

byte bea1[8] =
{
0b00000,
0b00101,
0b00111,
0b00101,
0b00111,
0b00000,
0b00000,
0b00000
};

byte bea2[8] =
{
0b00000,
0b01010,
0b01010,
0b01110,
0b01010,
0b00000,
0b00000,
0b00000
};

byte ryeo1[8] =
{
0b00000,
0b00111,
0b00001,
0b00111,
0b00100,
0b00111,
0b00000,
0b00000
};

byte ryeo2[8] =
{
0b00000,
0b00100,
0b11100,
0b00100,
0b11100,
0b00100,
0b00000,
0b00000
};

byte tak1[8] =
{
0b00000,
0b00111,
0b00100,
0b00111,
0b00100,
0b00111,
0b00000,
0b00000
};

byte tak2[8] =
{
0b00000,
0b00100,
0b00110,
0b00100,
0b00000,
0b01100,
0b00100,
0b00100
};

byte de1[8] =
{
0b00000,
0b00111,
0b00100,
0b00111,
0b00000,
0b01111,
0b00000,
0b00000
};

byte de2[8] =
{
0b00000,
0b10000,
0b00000,
0b10000,
0b00000,
0b11000,
0b00000,
0b00000
};

byte rip1[8] =
{
0b00000,
0b00111,
0b00001,
0b00111,
0b00100,
0b00111,
0b00000,
0b00000
};

byte rip2[8] =
{
0b00000,
0b00100,
0b00100,
0b00100,
0b00000,
0b10100,
0b11100,
0b11100
};

byte non[8] =
{
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};

byte* customChars[][8] = {
  {im1, im2, san1, san2, bu1, bu2, ga1, ga2},
  {non,non,non,non,non,non,non,non},
  {top1, top2, tmd1, tmd2, hat1, hat2, tmq1, tmq2},
  {ni1, ni2, da1, da2,non,non,non,non},
  
  {bea1, bea2, ryeo1, ryeo2,non,non,non,non},
  {non,non,non,non,non,non,non,non},
  {bu1,bu2,tak1, tak2, de1, de2, rip1, rip2},
  {ni1,ni2,da1,da2,non,non,non,non}
};

void setup() {
  Serial.begin(9600);
  SPI.begin(); // SPI 시작
  rfid.PCD_Init(); // RFID 시작

  // 초기 키 ID 초기화
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  lcd.init();
  lcd.backlight();
  Serial.println(F("시스템 초기화 완료"));
  lcd.setCursor(0, 0);
  
  delay(2000);
  lcd.clear();

  // 진동모듈 셋업
  pinMode(vibrationPin, OUTPUT);

  // 압력센서 셋업
  pinMode(sensor, INPUT);
}

void loop() {
  // 카드가 인식되었다면 다음으로 넘어가고 아니면 리턴
  if (!rfid.PICC_IsNewCardPresent())
    return;

  // ID가 읽혀졌다면 다음으로 넘어가고 아니면 리턴
  if (!rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC 유형: "));
  // 카드의 타입을 읽어온다
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // 모니터에 출력
  Serial.println(rfid.PICC_GetTypeName(piccType));

  Serial.println(F("새로운 카드가 감지되었습니다."));
  Serial.println(F("NUID 태그는 다음과 같습니다:"));
  Serial.print(F("16진수: "));
  // 16진수로 변환해서 출력
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  Serial.print(F("10진수: "));
  // 10진수로 출력
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  // 압력센서 값 출력 (테스트용)
  Serial.println(analogRead(sensor));
  delay(50);

  // 특정 카드가 감지되면 부저 울리고 LED와 메시지 설정
  if (isSpecificCard(rfid.uid.uidByte, rfid.uid.size, specificUid1)) {
    specificCard1DetectionCount++; // 카드 감지 횟수 증가
    if (specificCard1DetectionCount % 2 != 0) { // 홀수 번째 감지 시
      if (isSameCard(rfid.uid.uidByte, rfid.uid.size)) {
        triggerActions();
      } else {
        triggerActionsWithoutVibration();
        updateLastDetectedUid(rfid.uid.uidByte, rfid.uid.size);
      }
      //하차
    }else{buzz(100);} // 부저 0.1초 울림
    
  } else if (isSpecificCard(rfid.uid.uidByte, rfid.uid.size, specificUid2)) {
    specificCard2DetectionCount++; // 카드 감지 횟수 증가
    if (specificCard2DetectionCount % 2 != 0) { // 홀수 번째 감지 시
      if (isSameCard(rfid.uid.uidByte, rfid.uid.size)) {
        triggerActions();
      } else {
        triggerActionsWithoutVibration();
        updateLastDetectedUid(rfid.uid.uidByte, rfid.uid.size);
      }
      //하차
    }else{buzz(100);} // 부저 0.1초 울림
    
  } else {
    buzz(100); // 부저 0.1초 울림
  }

  // PICC 종료
  rfid.PICC_HaltA();

  // 암호화 종료(?)
  rfid.PCD_StopCrypto1();
}

// 16진수로 변환하는 함수
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

// 10진수로 변환하는 함수
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

// 특정 카드 확인 함수
bool isSpecificCard(byte *uid, byte size, byte *specificUid) {
  for (byte i = 0; i < size; i++) {
    if (uid[i] != specificUid[i]) {
      return false;
    }
  }
  return true;
}

// 마지막으로 감지된 UID 업데이트 함수
void updateLastDetectedUid(byte *uid, byte size) {
  for (byte i = 0; i < size; i++) {
    lastDetectedUid[i] = uid[i];
  }
}

// 동일한 카드인지 확인하는 함수
bool isSameCard(byte *uid, byte size) {
  for (byte i = 0; i < size; i++) {
    if (uid[i] != lastDetectedUid[i]) {
      return false;
    }
  }
  return true;
}

// 부저 울리고 LED 및 진동 모듈을 작동시키는 함수
void triggerActions() {
  setColor(255, 0, 255); // LED 핑크색
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000); // 1초 동안 유지
  digitalWrite(BUZZER_PIN, LOW);
  lcd1();
  setColor(0, 0, 0); // LED 끔

if(800>analogRead(sensor)){
  digitalWrite(vibrationPin, HIGH); // 진동 모듈 켜기
  delay(1000); // 1초 동안 진동
  digitalWrite(vibrationPin, LOW); // 진동 모듈 끄기
  delay(1000); // 1초 동안 정지
}
}
// 부저 울리고 LED만 작동시키는 함수 (진동 제외)
void triggerActionsWithoutVibration() {
  setColor(255, 0, 255); // LED 핑크색
  digitalWrite(BUZZER_PIN, HIGH);

  delay(1000); // 1초 동안 유지
  digitalWrite(BUZZER_PIN, LOW);
  lcd1();
  setColor(0, 0, 0); // LED 끔
}

// 부저 울리는 함수
void buzz(int duration) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}

// RGB LED 색 설정 함수
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void lcd1(){
int numSets = sizeof(customChars) / sizeof(customChars[0]);

  for (int set = 0; set < numSets; set++) {
//   lcd.clear();

    for (int i = 0; i < 8; i++) {
      lcd.createChar(i, customChars[set][i]);
    }
    if(set%4==1) {   
      for (int i = 0; i < 8; i++) {
        lcd.setCursor(i+8, 0);
        lcd.write((uint8_t)i);
      delay(40);
      }
    }
    else if(set%4==2) {
      for (int i = 0; i < 8; i++) {
        lcd.setCursor(i, 1);
        lcd.write((uint8_t)i);
 //lcd.scrollDisplayLeft();   // 왼쪽으로 한칸씩 이동
        delay(40);   // 0.3초마다
      }

    }
        else if(set%4==3) {
      for (int i = 0; i < 8; i++) {
        lcd.setCursor(i+8, 1);
        lcd.write((uint8_t)i);
 //lcd.scrollDisplayLeft();   // 왼쪽으로 한칸씩 이동
        delay(40);   // 0.3초마다
      }

    }
    else{
      for (int i = 0; i < 8; i++) {
        lcd.setCursor(i, 0);
        lcd.write((uint8_t)i);
 //lcd.scrollDisplayLeft();   // 왼쪽으로 한칸씩 이동
        delay(40);   // 0.3초마다
      }    
    }
  delay(500);
  
  lcd.clear();
  }
}