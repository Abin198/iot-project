#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int distanceThreshold = 50; // Distance in cm to trigger door open

Servo doorServo;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  doorServo.attach(3); // Connect servo to pin 3
  doorServo.write(0); // Initial door closed position
  Serial.begin(9600);
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= distanceThreshold) {
    openDoor();
    delay(3000); // Keep door open for 3 seconds
    closeDoor();
  }

  delay(500);
}

void openDoor() {
  doorServo.write(90); // Rotate servo to open position
  Serial.println("Door Opened");
}

void closeDoor() {
  doorServo.write(0); // Rotate servo to closed position
  Serial.println("Door Closed");
}

