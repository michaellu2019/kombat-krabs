#include <VarSpeedServo.h>

int strikeButtonPin = A0;
int leftTurnButtonPin = A1;
int leftStraightButtonPin = A2;
int rightTurnButtonPin = A3;
int rightStraightButtonPin = A4;

int motor1SpeedPin = 11;
int motor1Dir1Pin = 12;
int motor1Dir2Pin = 13;

int motor2SpeedPin = 10;
int motor2Dir1Pin = 9;
int motor2Dir2Pin = 8;

VarSpeedServo armServo;
int armServoPin = 7;

const int motorSpeed = 255;
const float lrCalibration = 1.667;

void setup() {
  // put your setup cod   e here, to run once:
  pinMode(strikeButtonPin, INPUT_PULLUP);
  pinMode(leftTurnButtonPin, INPUT_PULLUP);
  pinMode(leftStraightButtonPin, INPUT_PULLUP);
  pinMode(rightTurnButtonPin, INPUT_PULLUP);
  pinMode(rightStraightButtonPin, INPUT_PULLUP);
  
  pinMode(motor1SpeedPin, OUTPUT);
  pinMode(motor1Dir1Pin, OUTPUT);
  pinMode(motor1Dir2Pin, OUTPUT);

  armServo.write(7, 100);
  armServo.attach(armServoPin);
  
  Serial.begin(9600);
  Serial.println("INIT...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(strikeButtonPin) == LOW) {
    Serial.println("Strike");
    armServo.write(70, 240);
    delay(400);
    armServo.write(7, 100);
  } else if (digitalRead(leftTurnButtonPin) == LOW) {
    Serial.println("Left Turn");
    turn(-1);
  } else if (digitalRead(leftStraightButtonPin) == LOW) {
    Serial.println("Left Straight");
    runStraight(-1);
  } else if (digitalRead(rightTurnButtonPin) == LOW) {
    Serial.println("Right Turn");
    turn(1);
  } else if (digitalRead(rightStraightButtonPin) == LOW) {
    Serial.println("Right Straight");
    runStraight(1);
  } else {
    Serial.println("Stop");
    stop();
  }
}

void stop() {
    runMotor1(0);
    runMotor2(0);
}

void runStraight(int direction) {
  runMotor1(direction * motorSpeed);
  runMotor2(direction * motorSpeed);
}

void turn(int direction) {
  if (direction > 0) {
    runMotor1(direction * motorSpeed);
    runMotor2(0 * motorSpeed);
  } else {
    runMotor1(0 * motorSpeed);
    runMotor2(-direction * motorSpeed);
  }
}

void runMotor1(int speed) {
  speed = max(-255, min(speed, 255));
  
  if (speed < 0) {
    digitalWrite(motor1Dir1Pin, HIGH);
    digitalWrite(motor1Dir2Pin, LOW);
    analogWrite(motor1SpeedPin, abs(speed));
  } else if (speed > 0) {
    digitalWrite(motor1Dir1Pin, LOW);
    digitalWrite(motor1Dir2Pin, HIGH);
    analogWrite(motor1SpeedPin, abs(speed));
  } else {
    digitalWrite(motor1Dir1Pin, LOW);
    digitalWrite(motor1Dir2Pin, LOW);
    analogWrite(motor1SpeedPin, 0);
  }
}

void runMotor2(int speed) {
  speed = max(-255, min(speed, 255));
  
  if (speed < 0) {
    digitalWrite(motor2Dir1Pin, HIGH);
    digitalWrite(motor2Dir2Pin, LOW);
    analogWrite(motor2SpeedPin, abs(speed));
  } else if (speed > 0) {
    digitalWrite(motor2Dir1Pin, LOW);
    digitalWrite(motor2Dir2Pin, HIGH);
    analogWrite(motor2SpeedPin, abs(speed));
  } else {
    digitalWrite(motor2Dir1Pin, LOW);
    digitalWrite(motor2Dir2Pin, LOW);
    analogWrite(motor2SpeedPin, 0);
  }
}
