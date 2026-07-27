/*
  Autonomous Car Parking Robot
  --------------------------------
  Hardware: Arduino Nano V3, L298N Motor Driver, 2x DC Motors,
            Servo Motor (steering), 3x HC-SR04 Ultrasonic Sensors

  How it works:
  Three ultrasonic sensors (front, left, right) continuously measure
  distance to detect a parking gap wide enough for the robot. Once a
  gap is found, the robot stops, reverses at a steering angle set by
  the servo, and straightens out once it's centered in the space.

  Sensor layout (adjust pins to match your actual wiring):
    Front sensor -> Trig: 2,  Echo: 3
    Left sensor  -> Trig: 4,  Echo: 5
    Right sensor -> Trig: 6,  Echo: 7

  Wiring (adjust pins to match your actual build):
    L298N IN1 -> Pin 8   (Left motor direction 1)
    L298N IN2 -> Pin 9   (Left motor direction 2)
    L298N IN3 -> Pin 10  (Right motor direction 1)
    L298N IN4 -> Pin 11  (Right motor direction 2)
    L298N ENA -> Pin 12  (Left motor speed - PWM... use a PWM-capable pin)
    L298N ENB -> Pin 13  (Right motor speed - PWM... use a PWM-capable pin)
    Servo signal -> Pin A0
*/

#include <Servo.h>

// Ultrasonic sensor pins
const int frontTrig = 2, frontEcho = 3;
const int leftTrig = 4, leftEcho = 5;
const int rightTrig = 6, rightEcho = 7;

// Motor pins
const int leftMotorPin1 = 8;
const int leftMotorPin2 = 9;
const int rightMotorPin1 = 10;
const int rightMotorPin2 = 11;
const int leftMotorSpeed = 12;
const int rightMotorSpeed = 13;

// Servo for steering
Servo steeringServo;
const int servoPin = A0;
const int centerAngle = 90;
const int reverseAngle = 45; // angle used while reversing into a spot

// Parking gap detection threshold (cm) — tune to your robot's size
const int requiredGapCm = 25;
const int obstacleStopCm = 15;

int baseSpeed = 150;

void setup() {
  Serial.begin(9600);

  pinMode(frontTrig, OUTPUT); pinMode(frontEcho, INPUT);
  pinMode(leftTrig, OUTPUT);  pinMode(leftEcho, INPUT);
  pinMode(rightTrig, OUTPUT); pinMode(rightEcho, INPUT);

  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorSpeed, OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);

  steeringServo.attach(servoPin);
  steeringServo.write(centerAngle);
}

void loop() {
  long frontDist = readDistanceCm(frontTrig, frontEcho);
  long rightDist = readDistanceCm(rightTrig, rightEcho);

  if (frontDist < obstacleStopCm) {
    stopCar();
    return;
  }

  if (rightDist > requiredGapCm) {
    // Found a gap on the right wide enough to park in
    parkIntoSpot();
  } else {
    moveForward();
  }
}

void parkIntoSpot() {
  stopCar();
  delay(300);

  // Reverse while steering into the spot
  steeringServo.write(reverseAngle);
  moveBackward();
  delay(1500); // tune this duration to your robot's speed/spot size

  // Straighten out
  steeringServo.write(centerAngle);
  stopCar();
}

void moveForward() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  setSpeed(baseSpeed, baseSpeed);
}

void moveBackward() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  setSpeed(baseSpeed, baseSpeed);
}

void stopCar() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
  setSpeed(0, 0);
}

void setSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(leftMotorSpeed, leftSpeed);
  analogWrite(rightMotorSpeed, rightSpeed);
}

long readDistanceCm(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  long distanceCm = duration * 0.034 / 2;
  return distanceCm;
}
