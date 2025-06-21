#include <Servo.h>

const int TRIG_PIN = 5;     // Trigger pin of ultrasonic sensor
const int ECHO_PIN = 4;     // Echo pin of ultrasonic sensor
const int servoPin1 = 9;    // Pin for the first servo motor
const int servoPin2 = 10;   // Pin for the second servo motor
const int servoPin3 = 11;   // Pin for the third servo motor

const int ini_angle = 0;
const int final_angle = 140;
const int speed = 5;

Servo myServo1, myServo2, myServo3;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo1.attach(servoPin1); // Attach first servo to pin 9
  myServo2.attach(servoPin2); // Attach second servo to pin 10
  myServo3.attach(servoPin3); // Attach third servo to pin 11

  myServo1.write(ini_angle);          // Start all motors at initial positions
  myServo2.write(180 - ini_angle);
  myServo3.write(ini_angle);

  Serial.begin(9600);         // Start serial communication for debugging
}

void loop() {

  // Display the distance in Serial Monitor
  Serial.print("Distance: ");
  // Serial.print(distance);
  Serial.println(" cm");

  // If the distance is less than 5 cm, move all servos
  while (distanceChecker() < 5) {
    moveServoSmoothly(myServo1, ini_angle, final_angle, speed); // Move first motor to 140°
    delay(500); // Wait 500ms
    moveServoSmoothly(myServo1, final_angle, ini_angle, speed); // Move back to 0° for the first motor
    delay(2000); // Wait 2 seconds

    moveServoSmoothly(myServo2, 180-ini_angle, 180-final_angle, speed); // Move second motor to 30°
    delay(500); // Wait 500ms
    moveServoSmoothly(myServo2, 180-final_angle, 180-ini_angle, speed); // Move back to 180° for the second motor
    delay(2000); // Wait 2 seconds

    moveServoSmoothly(myServo3, ini_angle, final_angle*1.25, speed); // Move third motor to 150°
    delay(1000); // Wait 500ms
    moveServoSmoothly(myServo3, final_angle*1.25, ini_angle, speed); // Move back to 0° for the third motor

    // Print "WORK DONE" after motors complete their tasks
    Serial.println("WORK DONE");

    // Wait for 5 seconds before resuming the distance check
    delay(5000);
  }

  delay(250); // Delay for distance check
}

// Function to check distance and return it
float distanceChecker() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

// Function to move servo smoothly from start position to end position
void moveServoSmoothly(Servo &servo, int startPos, int endPos, int speed) {
  if (startPos < endPos) {
    for (int pos = startPos; pos <= endPos; pos++) {
      servo.write(pos);
      delay(speed); // Smaller delay = faster movement
    }
  } else {
    for (int pos = startPos; pos >= endPos; pos--) {
      servo.write(pos);
      delay(speed); // Smaller delay = faster movement
    }
  }
}
