#define led 12
const int buttonPin = A3;
int xAxis, yAxis, zAxis;
int buttonState;
void setup() {
  pinMode(led, OUTPUT);
 
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}
void loop() 
  {
  xAxis = analogRead(A0); // Read Joysticks X-axis, for motor direction
  yAxis = analogRead(A1); // Read Joysticks Y-axis,for motor forward backward
  zAxis = analogRead(A2); // Read Joysticks z-axis, for servo
  buttonState = analogRead(buttonPin);//read button state, for jumping
  // Send the values via the serial port to the slave HC-12 
  Serial.write(xAxis/4);
 // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  Serial.write(yAxis/4);
 
  Serial.write(zAxis/4);
 
  Serial.write(buttonState/4);
  delay(40);
  } 
  //if(buttonState>0)
  //{
   // digitalWrite(led, LOW);
    }
    //else
    //{digitalWrite(led, HIGH);
//  this is for the button testing    }
  
  
     





 
