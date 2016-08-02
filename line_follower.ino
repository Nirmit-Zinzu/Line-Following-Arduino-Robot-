// importing libraries to use special functions in the code 
#include <Servo.h>
#include <SoftwareSerial.h>


int rightQTI;             // stores the value of the right QTI sensor
int leftQTI;              // stores the value of the left QTI sensor 
int middleQTI;            // stores the value of the middle QTI sensor 

Servo servoLeft;          // Define left servo
Servo servoRight;         // Define right servo

// seting up servos
void setup() {
  Serial.begin(9600);    // used this to allow printing statements on serial monitor
  servoLeft.attach(10);  // Set left servo to digital pin 10
  servoRight.attach(9);  // Set right servo to digital pin 9
}

void loop() {
   
    leftQTI = RCTime(7);         // getting input from the left QTI sensor    
    middleQTI = RCTime(6);       // getting input from the right QTI sensor    
    rightQTI = RCTime(5);        // getting input from the right QTI sensor  
    
    // checking each conditions to run appropriate function
    if ((middleQTI > 35) && (leftQTI < 35) && (rightQTI < 35)) {
       forward();     
    } else if ((leftQTI > 35) && (middleQTI < 35) && (rightQTI < 35)) {
      turnRight();   
    } else if ((leftQTI > 35) && (middleQTI > 35) && (rightQTI < 35)) {
      turnRight();
    } else if ((rightQTI > 35) && (middleQTI < 35) && (leftQTI < 35)) {
       turnLeft();
    } else if ((rightQTI > 35) && (middleQTI > 35) && (leftQTI < 35)) {
      turnLeft();
    } else {
      stopRobot();    
    }    
}

// method which gets the value for each sensor
long RCTime(int sensorIn){
   long duration = 0;
   pinMode(sensorIn, OUTPUT);     
   digitalWrite(sensorIn, HIGH);  
   delay(1);                      
   pinMode(sensorIn, INPUT);      
   digitalWrite(sensorIn, LOW);   
   while(digitalRead(sensorIn)){  
      duration++;
   }
   return duration;
} 

void forward() {  
  servoLeft.write(0);     // 0 = counter clock-wise 
  servoRight.write(180);  // 180 = clock-wise 
} 

void turnLeft() {
  // both servos move clock-wise 
  servoLeft.write(180);
  servoRight.write(180);  
}

void turnRight() {
  // both servos move counter clock-wise 
  servoLeft.write(0);
  servoRight.write(0);  
}

void stopRobot() {
  // both servos stop moving 
  servoLeft.write(90);
  servoRight.write(90);
}
