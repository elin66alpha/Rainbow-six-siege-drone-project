#include <Servo.h>  
#define enA 3
#define in1 4
#define in2 9
#define enB 5
#define in3 6
#define in4 7
#define STBY 8
#define servopin 11
#define lbb 2
Servo myservo;
int xAxis, yAxis, zAxis;
int buttonState = 0;
int  x = 0;
int  y = 0;
int  z = 0;
int button = 0;
int motorSpeedA = 0;
int motorSpeedB = 0;
void setup() {
  pinMode(STBY,OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(lbb, OUTPUT);
  myservo.attach(servopin);
  Serial.begin(9600); 

}
void loop(){
  xAxis = 510;
  yAxis = 510;
  zAxis = 510;
  buttonState=510;
  // Read the incoming data from the 
  while (Serial.available() == 0) {}
  x = Serial.read();
  delay(10);
  y = Serial.read();
  delay(10);
  z = Serial.read();
  delay(10);
  button = Serial.read();
  delay(10);

  digitalWrite(STBY,HIGH);
 
  xAxis = x * 4;
  yAxis = y * 4;
  zAxis = z *4;
  buttonState= button *4;
  
  if (yAxis < 500) {
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 500, 0, 0, 255);
    motorSpeedB = map(yAxis, 500, 0, 0, 255);
  }
  else if (yAxis > 610) {
    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 610, 1023, 0, 255);
    motorSpeedB = map(yAxis, 610, 1023, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }
  // X-axis used for left and right control
  if (xAxis < 500) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 500, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
  if (xAxis > 620) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 620, 1023, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  if (zAxis>0)
  { int zmapw;
    zmapw = map(zAxis,0,1023,0,180);
    myservo.write(zmapw);
 
      }
  
  else
  {
    myservo.write(0);
    }
  if(buttonState>0)
  { digitalWrite(lbb, LOW);
    
    }
    else
   {
    digitalWrite(lbb, HIGH);
    
      }


      }
  
