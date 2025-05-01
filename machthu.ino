#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
//Khai báo chân ngõ vào nút nhấn điều khiển
#define forward 7
#define back    6
#define left    5
#define right   4

unsigned long time =0;
int msg[2];
int msg2[2];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
    radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  pinMode(forward,INPUT_PULLUP);
  pinMode(back,INPUT_PULLUP);
  pinMode(left,INPUT_PULLUP);
  pinMode(right,INPUT_PULLUP);
  time = millis();
}
void loop(){
  Serial.println(msg[0]);
  if(millis()-time > 50)
  {
 if (digitalRead(forward) == LOW)//đọc giá trị nút nhấn
 {
      radio.stopListening();
      radio.openWritingPipe(pipe);
  msg[0] = 1;
  radio.write(msg, sizeof(msg));
//  delay(10);    radio.openReadingPipe(1,pipe); radio.startListening();
 }
 if(digitalRead(back) == LOW)//Đọc giá trị nút nhấn
 {
      radio.stopListening();
      radio.openWritingPipe(pipe); 
  msg[0] = 2;
  radio.write(msg, sizeof(msg));
 // delay(10);    radio.openReadingPipe(1,pipe); radio.startListening(); 
 }
 if(digitalRead(left) == LOW)//Đọc giá trị nút nhấn
 {
      radio.stopListening();
      radio.openWritingPipe(pipe);
  msg[0] = 3;
  radio.write(msg, sizeof(msg));
//  delay(10);    radio.openReadingPipe(1,pipe); radio.startListening();
 }
 if(digitalRead(right) == LOW)//Đọc giá trị nút nhấn
 {
      radio.stopListening();
      radio.openWritingPipe(pipe);
  msg[0] = 4;
  radio.write(msg, sizeof(msg));
//  delay(10);    radio.openReadingPipe(1,pipe); radio.startListening(); 
 }
 if(digitalRead(forward)==HIGH && digitalRead(back)==HIGH && digitalRead(left)==HIGH && digitalRead(right)==HIGH )  ////STOP
 {
      radio.stopListening();
      radio.openWritingPipe(pipe);
  msg[0] = 5;
  radio.write(msg, sizeof(msg));
 // delay(10);    radio.openReadingPipe(1,pipe); radio.startListening();  
 }
 time = millis();
  }
  
}

