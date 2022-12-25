#include <avr/io.h>
#include <util/delay.h>
#include <EEPROM.h>
#include <Servo.h>
#include <Wire.h>

#define trigPin PB3
#define echoPin PD2
#define trigPin2 PB5
#define echoPin2 PD3
#define IRPin PC0
#define fan_thrust_pin 5
#define fan_lift_pin 4

int servo_pin = PD6;
int fanSpeedLift;
int fanSpeedThrust;
unsigned int durationLeft, durationRight;
int leftorRight;
int adcInput;
int distanceArray[5];
int distanceLeft, distanceRight, distanceFront, distanceShortest;
int distanceLeftPrevious, distanceRightPrevious, distanceFrontPrevious;
int velocityLeft, velocityRight, velocityFront;

int angle;
int baseAngle = 90;
float correctionAngle;
float sideFactor = 70;
float frontFactor = 0.01;
float time, elapsedTime;


Servo sg90;

void setup() {

sg90.attach(servo_pin);
Serial.begin(9600);
delay(50);

 pinMode(fan_thrust_pin, OUTPUT);
 pinMode(fan_lift_pin, OUTPUT);

  DDRB|=(1<<trigPin); // Sets the trigPin as an Output
  DDRB|=(1<<trigPin2);

  
  fanSpeedLift = 255;
  fanSpeedThrust = 255;
 analogWrite(fan_thrust_pin, fanSpeedThrust); 
 analogWrite(fan_lift_pin, fanSpeedLift);

}

void loop()
{

  time = millis();

//------------------------------------------------------------
//
//                GET SENSOR VALUES
//
//------------------------------------------------------------

  // PORTB|=(1<<trigPin);
  // _delay_us(10);
  // PORTB&=~(1<<trigPin);
  // durationLeft = pulseIn(echoPin, HIGH);  
  // distanceLeft = (durationLeft/2)/34;
  // distanceLeft = constrain(distanceLeft, 1, 50);
  // velocityLeft = distanceLeftPrevious - distanceLeft;
  // distanceLeftPrevious = distanceLeft;

  // PORTB|=(1<<trigPin2);
  // _delay_us(10);
  // PORTB&=~(1<<trigPin2);   
  // durationRight = pulseIn(echoPin2, HIGH);
  // distanceRight = (durationRight/2)/34;
  // distanceRight = constrain(distanceRight, 1, 50);
  // velocityRight= distanceRightPrevious - distanceRight;
  // distanceRightPrevious = distanceRight;

  // adcInput = analogRead(IRPin);// Get a distance measurement and store in adcInput:
  // distanceFront = abs(4157/(-46.5 + adcInput)); //conversion formula calculated from datasheet. Abs is because it goes to negative at high values
  // distanceFront = constrain(distanceFront,1,100); //Stops the distance from ever being outside the range

  PORTB|=(1<<trigPin);
  _delay_us(10);
  PORTB&=~(1<<trigPin);
  durationLeft = pulseIn(echoPin, HIGH);  
  distanceFront = (durationLeft/2)/34;
  distanceFront = constrain(distanceLeft, 1, 50);

//------------------------------------------------------------
//
//                     ALGORITHM      
//  
//0 is left          90 is straight         180 is right
// 
//------------------------------------------------------------

//What is shorter? left or right? If left, then shortest = Left, otherwise shortest = Right

sg90.write(90);

//if(distanceFront<=40){
//   Serial.println("Initializing Loop");
//
//
//  int maxDistance = 0;
//  int maxAngle;
//  
// analogWrite(fan_thrust_pin,0); //Turns off fan
// analogWrite(fan_lift_pin, 0);
//
//    for(int i = 0; i<(sizeof(distanceArray)/sizeof(int)); i++){      
//      int checkAngle = i* 180/(sizeof(distanceArray)/sizeof(int)-1);
//      sg90.write(checkAngle);
//      delay(300);
//
//      PORTB|=(1<<trigPin);
//      _delay_us(10);
//      PORTB&=~(1<<trigPin);
//      durationLeft = pulseIn(echoPin, HIGH);  
//      distanceFront = (durationLeft/2)/34;
//      distanceFront = constrain(distanceLeft, 1, 50);
//
//
//      distanceArray[i] = distanceFront; //Stores front values in array
//
//          if (distanceArray[i]>maxDistance) { //Gets the max value
//          maxDistance = distanceArray[i];
//          maxAngle = checkAngle;
//          }
//
//             Serial.print(" Distance ");
//             Serial.print(i);
//             Serial.print(": ");
//             Serial.print(distanceArray[i]);
//    }
//
//   Serial.print("   Max: ");
//   Serial.println(maxDistance);
//
//   sg90.write(maxAngle);
//   analogWrite(fan_thrust_pin,255); //Turns on fan
//   analogWrite(fan_lift_pin, 255);
//   delay(5000);  
//}


// if (distanceLeft<distanceRight){
// distanceShortest = distanceLeft;
// leftorRight = 1;
// } else{
//   distanceShortest = distanceRight;
// leftorRight = -1;
// }


//-----------------------------------------------------------
//
//                SERIAL PRINT
//
//------------------------------------------------------------

// Serial.print("Left: ");
// Serial.print(distanceLeft);
// Serial.print(" cm");
// Serial.print("   Right: ");
// Serial.print(distanceRight);
// Serial.print(" cm");
// Serial.print("   Front: ");
// Serial.print(distanceFront);
// Serial.print(" cm");
// Serial.print("    Servo Angle: ");
// Serial.println(angle);

// Serial.print("   Velocity Left: ");
// Serial.print(velocityLeft);
// Serial.print("   Velocity Right: ");
// Serial.println(velocityRight);

Serial.print("   Front: ");
Serial.print(distanceFront);
Serial.println(" cm");

 // delay(100);
}
