//including the libraries
#include <AFMotor.h>
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 42, 40, 38, 36 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 34, 32, 30, 28};

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//defining pins and variables
#define lefts A11
#define rights A9
int trigPin = 25;
int echoPin = 31;
long duration, cm, inches;
//defining motors
AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);





void setup() {
  // setting the speed of motors
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
  pinMode(lefts, INPUT);
  pinMode(24, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(rights, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}


void loop() {
  digitalWrite(37, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(23, HIGH);

  ///Serial.println(analogRead(lefts));
  ///Serial.println("left");
  //Serial.println(analogRead(rights));
  //Serial.println("right");
  //delay(500);
  char c = kpd.getKey();
  Serial.println(c);
  //Serial.println("A2");
  //delay(500);
  if (c == '1' || c == '2' || c == '3')
  {
    int p = c - 48;
    int loop = 1000* p;
    int i = 0;
    while (i < loop)
    {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);

      cm = (duration / 2) / 29.1;
      if (cm > 10)
      {
        //Serial.println(cm);
        
        if (analogRead(lefts) <= 30 && analogRead(rights) > 400) {
          Serial.println("turn left");
          motor1.run(BACKWARD);
          motor2.run(BACKWARD);
          motor3.run(BACKWARD);
          motor4.run(RELEASE);
          
        }
        else if (analogRead(lefts) > 600 && analogRead(rights) <= 400) {
          Serial.println("turn right");
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          motor3.run(RELEASE);
          motor4.run(FORWARD);
         
        }
        else {
          //stop
          Serial.println("run forward");
          motor1.run(FORWARD);
          motor2.run(BACKWARD);
          motor3.run(BACKWARD);
          motor4.run(FORWARD);
          i++;
        }
        
        
        
        
      }
      else
      {
        Serial.println("Stopped");
        Serial.println(cm);
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        
      }
      delay(200);
    }
  }
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        motor3.run(RELEASE);
        motor4.run(RELEASE);
        //delay(1000);
 /* if (analogRead(lefts) <= 400 && analogRead(rights) <= 400) {
     //stop
     motor1.run(FORWARD);
     motor2.run(BACKWARD);
     motor3.run(BACKWARD);
     motor4.run(FORWARD);
    }
    else if (analogRead(lefts) <= 400 && !analogRead(rights) <= 400) {
     motor1.run(BACKWARD);
     motor2.run(BACKWARD);
     motor3.run(BACKWARD);
     motor4.run(RELEASE);
    }
    else if (!analogRead(lefts) <= 400 && analogRead(rights) <= 400) {
     motor1.run(FORWARD);
     motor2.run(FORWARD);
     motor3.run(RELEASE);
     motor4.run(FORWARD);
    }
    else
    {
     motor1.run(RELEASE);
     motor2.run(RELEASE);
     motor3.run(RELEASE);
     motor4.run(RELEASE);
    }
    delay(500);


    /*else if(analogRead(lefts)<=400 && !analogRead(rights)<=400){
     motor1.run(FORWARD);
     motor2.run(BACKWARD);
     motor3.run(FORWARD);
     motor4.run(BACKWARD);

     }

     else if(!analogRead(lefts)<=400 && analogRead(rights)<=400){

     motor1.run(BACKWARD);
     motor2.run(FORWARD);
     motor3.run(BACKWARD);
     motor4.run(FORWARD);

     }

     else if(!analogRead(lefts)<=400 && analogRead(rights)<=400){

     motor1.run(RELEASE);
     motor2.run(RELEASE);
     motor3.run(RELEASE);
     motor4.run(RELEASE);

     }*/
}