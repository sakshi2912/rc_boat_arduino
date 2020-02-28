#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN


const byte address[6] = "23456";
const int x_key =A0;
const int y_key =A1;
int x_pos[2];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(x_key , INPUT);
  
}

void loop() {
   Serial.println(analogRead(A0));
   Serial.println(analogRead(A1));
 char text[] = "abcdef";
 // radio.write(&text, sizeof(text));
  x_pos[0]=analogRead(x_key);
  x_pos[1]=analogRead(y_key);
 // x_pos[0] = map(x_pos ,0 , 1023 , 0 , 255);
 radio.write(&x_pos,sizeof(x_pos));
 
 
}
