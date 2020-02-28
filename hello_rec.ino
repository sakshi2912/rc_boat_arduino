#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>
Servo motor1;
RF24 radio(7, 8); // CE, CSN
 int x_pos[2] ;
const byte address[6] = "23456";
int angle=0;
int motor_speed=0;
const int EN1 = 3;
const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 9;
const int IN4 = 10;
const int EN2 = 2;

void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  motor1.attach(6);
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void loop() {
  
  if (radio.available()) 
  {
  // char text[32]="";
    radio.read(&x_pos , sizeof(x_pos));
    //Serial.println(x_pos[0]);
    Serial.println(x_pos[1]);
     angle=map(x_pos[0],0,1023,0,180);
    Serial.println();
 //   radio.read(&text , sizeof(text));
//    { Serial.println(text);}

  Serial.println(angle);
 
 if (angle==86 && x_pos[1] < 400)
 {     //Rotating the left motor in clockwise direction
   

    //motor_speed = map(x_pos[1], 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
   // motor_speed=0;
    motor1.write(86);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, motor_speed);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(EN2, motor_speed);
   // angle=map(x_pos[0],0,1023,0,180);
  //   motor1.write(angle);
  
    /*
    motor_speed=0;
     digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(EN2 ,motor_speed);
      digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(EN1 ,motor_speed);*/
  }
else if (angle>80 && angle<90 && x_pos[1]>400 && x_pos[1]<600 ){  //Motors will not move when the joystick will be at center
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    angle=86;
    motor1.write(angle);
  }
  
else if (angle>80 && angle <90 && x_pos[1] > 600){    //Rotating the left motor in anticlockwise direction
    motor_speed = map(x_pos[1], 600, 1023, 0, 255);
    motor1.write(86);
    digitalWrite(IN1, HIGH);
  
  digitalWrite(IN2, LOW);
    analogWrite(EN1, motor_speed);

    digitalWrite(IN3, HIGH);
  
  digitalWrite(IN4, LOW);
    analogWrite(EN2, motor_speed);
   //   angle=map(x_pos[0],0,1023,0,180);
    // motor1.write(angle);
  }

  else if(angle!=86 && x_pos[1] > 600){    //Rotating the left motor in anticlockwise direction
    motor_speed = map(x_pos[1], 600, 1023, 0, 255);
    
    digitalWrite(IN1, HIGH);
  
  digitalWrite(IN2, LOW);
    analogWrite(EN1, motor_speed);

    digitalWrite(IN3, HIGH);
  
  digitalWrite(IN4, LOW);
   analogWrite(EN2, motor_speed);
   //   angle=map(x_pos[0],0,1023,0,180);
    motor1.write(angle);
  }
  else if(x_pos[1]>400 && x_pos[1]<600 && angle!=86)
  {
    motor1.write(angle);
  }

  else if(angle!=86 && x_pos[1] < 400)
  {
   //motor_speed = map(x_pos[1], 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
   // motor_speed=0;
   
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, motor_speed);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(EN2, motor_speed);
    motor1.write(angle);
  }
  }
}
