#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


int H_green = A2;
int H_red = A1;
int H_yellow = A0;

int V_green = A5;
int V_red = A4;
int V_yellow = A3;
int touchSensor = 8;
int buzzer = 6;
int buttonState = HIGH;
int lastButtonState = HIGH;
int x = 0;

void setup()
{
pinMode(H_green, OUTPUT);
pinMode(H_red, OUTPUT);
pinMode(H_yellow, OUTPUT);

  pinMode(V_green, OUTPUT);
  pinMode(V_red, OUTPUT);
  pinMode(V_yellow, OUTPUT);

  pinMode(touchSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  
Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  
}


void standard(){
  tone(buzzer, 100);
digitalWrite(H_red, HIGH);
digitalWrite(V_green, HIGH);
  
  for(int i = 15; i > 0; i--){

    Serial.println(i);
    delay(1000);
  }
  digitalWrite(V_green, LOW);
  digitalWrite(V_yellow, HIGH);
  
  for(int i = 3; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  noTone(buzzer);
  digitalWrite(V_yellow, LOW);
  digitalWrite(V_red, HIGH);
  digitalWrite(H_red, LOW);
  digitalWrite(H_green, HIGH);
  
  for(int i = 15; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(H_green, LOW);
  digitalWrite(H_yellow, HIGH);
  
  for(int i = 3; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(V_red, LOW);
  digitalWrite(H_yellow, LOW);

}

void walker(){
int y = digitalRead(touchSensor);
if (y == 1){
  Serial.println("Button Pressed"); 
  delay(2000);
  walkerLights();
}
}


void walkerLights() {
  tone(buzzer, 100);
digitalWrite(H_red, HIGH);
digitalWrite(V_green, HIGH);
  
  for(int i = 20; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(V_green, LOW);
  digitalWrite(V_yellow, HIGH);
  
  for(int i = 3; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(V_yellow, LOW);
  digitalWrite(V_red, HIGH);
  digitalWrite(H_red, LOW);
  digitalWrite(H_green, HIGH);
  noTone(buzzer);
  for(int i = 20; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(H_green, LOW);
  digitalWrite(H_yellow, HIGH);
  
  for(int i = 3; i > 0;i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(V_red, LOW);
  digitalWrite(H_yellow, LOW);
}

void disabledLights(){
  tone(buzzer, 100);
  
digitalWrite(H_red, HIGH);
digitalWrite(V_green, HIGH);
  
  for(int i = 25; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(V_green, LOW);
  digitalWrite(V_yellow, HIGH);
  noTone(buzzer);
  for(int i = 3; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(V_yellow, LOW);
  digitalWrite(V_red, HIGH);
  digitalWrite(H_red, LOW);
  digitalWrite(H_green, HIGH);
  
  for(int i = 25; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(H_green, LOW);
  digitalWrite(H_yellow, HIGH);
  
  for(int i = 3; i > 0; i--){
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(V_red, LOW);
  digitalWrite(H_yellow, LOW);
}

void rfid() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "35 33 03 15") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized pass");
    disabledLights();
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
}
}


void loop()
{
  while(true){
  rfid();
  walker();
  }

  delay(30000);
  standard();
}