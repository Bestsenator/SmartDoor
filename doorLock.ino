#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 8

MFRC522 mfrc522(SS_PIN, RST_PIN);


const int greenLED = 2; 
const int redLED = 3;
const int relay = 4;
const int buzzer = 5; 
const int sizeIdTags = 23;
int counter = 0;
bool isReadCard = false;

String authorizedUIDs[sizeIdTags] = 
{
   " 6a 46 75 cc",
   " 5a a8 89 cc",
   " ba 04 7a cc",
   " 65 03 62 0a",
   " 2a 16 9b cc",
   " 2a a6 ac ca",
   " 3a 21 b0 ca",
   " fa 1a 9c cc",
   " ba 7e 7e ca",
   " da b6 9f cc",
   " 1a a0 b2 ca",
   " aa 80 72 ca",
   " 0a 4f 7b ca",
   " 2a 69 a2 ca",
   " 8a 2f b2 ca",
   " 7a 51 c0 ca",
   " ca ce bb ca",
   " aa 84 bf ca",
   " 5a 0c 79 ca",
   " da e8 b1 ca",
   " bc e1 a7 48",
   " 9c a6 71 66",
   " 7c 6e 7b 48" 
};


void setup()
{
  // Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(relay, HIGH);
  digitalWrite(buzzer, LOW);


  // Serial.println("Ready to read RFID tags");
}

void loop()
{
  if (counter > 45){
    if(counter > 1000 || isReadCard == true){
      // Serial.println("Arduino Reseting");
      isReadCard = false;
      counter = 0 ;
      resetArduino();
    }
  }
  delay(250);
  // Serial.print("Get It...");
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    // Serial.print("If one\n");
    // Serial.println(counter);
    counter++;
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    // Serial.print("If Two\n");
    // Serial.println(counter);
    counter++;
    return;
  }

  String uid = getUID();
  // Serial.print("UID tag: ");
  // Serial.println(uid);

  if (isAuthorized(uid))
  {
    // Serial.println("Authorized access");
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, LOW);
    delay(100);
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, HIGH);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(greenLED, LOW);
  }
  else
  {
    // Serial.println("Access denied");
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
  }
  delay(500);
}

String getUID()
{
  isReadCard = true;
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uid += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  return uid;
}

bool isAuthorized(String uid)
{
  for (int i = 0; i < sizeIdTags; i++)
  {
    if (uid == authorizedUIDs[i])
    {
      return true;
    }
  }
  return false;
}

void resetArduino() {
  SPI.begin();
  mfrc522.PCD_Init();
}