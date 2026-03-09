#include <SPI.h>
#include <LoRa.h>

// --- PIN DEFINITIONS ---

// LoRa Pins
const int LORA_CS = 10;
const int LORA_RST = 9;
const int LORA_DIO0 = 2;

// IR Sensor Pins (Digital Input)
const int S1_PIN = A0; // Far Left
const int S2_PIN = A1; // Left
const int S3_PIN = A2; // MIDDLE (The one that wants the line)
const int S4_PIN = A3; // Right
const int S5_PIN = A4; // Far Right

// Motor Driver Pins (Example for L298N)
// Adjust these to match your specific wiring
const int ENA = 3;  // PWM Speed Control Left
const int IN1 = 4;  // Left Motor Direction
const int IN2 = 5;  // Left Motor Direction
const int ENB = 6;  // PWM Speed Control Right
const int IN3 = 7;  // Right Motor Direction
const int IN4 = 8;  // Right Motor Direction

// --- CONSTANTS ---
const int MOTOR_SPEED = 120; // Base speed (0-255)
const int TURN_SPEED = 100;  // Speed during correction
const int BLACK = LOW;       // Sensor turns OFF on tape
const int WHITE = HIGH;      // Sensor turns ON on floor

// Timer for LoRa (Don't send every loop or robot lags)
unsigned long lastSendTime = 0;
const int sendInterval = 2000; // Send status every 2 seconds

void setup() {
  Serial.begin(9600);
  
  // 1. Setup LoRa
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setTxPower(2); // Min power for bench test
  Serial.println("LoRa Initialized.");

  // 2. Setup Sensors
  pinMode(S1_PIN, INPUT);
  pinMode(S2_PIN, INPUT);
  pinMode(S3_PIN, INPUT);
  pinMode(S4_PIN, INPUT);
  pinMode(S5_PIN, INPUT);

  // 3. Setup Motors
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // --- READ SENSORS ---
  int s1 = digitalRead(S1_PIN);
  int s2 = digitalRead(S2_PIN);
  int s3 = digitalRead(S3_PIN); // The Center
  int s4 = digitalRead(S4_PIN);
  int s5 = digitalRead(S5_PIN);

  String status = "Stop";

  // --- LOGIC: S3 Attracts, Others Repel ---

  // CASE 1: Perfect Alignment
  // S3 is on Black (LOW), Neighbors are on White (HIGH)
  if (s3 == BLACK && s2 == WHITE && s4 == WHITE) {
    moveForward();
    status = "Forward";
  }
  
  // CASE 2: Slight Drift to Right (Line is hitting S2)
  // S2 sees Black. Robot must turn Left to "repel" line from S2 back to S3.
  else if (s2 == BLACK) {
    turnLeft();
    status = "Correcting Left";
  }
  
  // CASE 3: Slight Drift to Left (Line is hitting S4)
  // S4 sees Black. Robot must turn Right to "repel" line from S4 back to S3.
  else if (s4 == BLACK) {
    turnRight();
    status = "Correcting Right";
  }

  // CASE 4: Extreme Drift to Right (Line hitting S1)
  // S1 sees Black. Hard Left turn needed.
  else if (s1 == BLACK) {
    sharpLeft();
    status = "Hard Left";
  }

  // CASE 5: Extreme Drift to Left (Line hitting S5)
  // S5 sees Black. Hard Right turn needed.
  else if (s5 == BLACK) {
    sharpRight();
    status = "Hard Right";
  }

  // CASE 6: Lost Line (All White) or Crossroad (All Black)
  // Defaulting to stop, but you might want to "search" here
  else if (s1 == WHITE && s2 == WHITE && s3 == WHITE && s4 == WHITE && s5 == WHITE) {
    stopMotors();
    status = "Lost Line";
  }
  else {
    // If multiple sensors trigger oddly, just go forward slowly or stop
    moveForward(); 
  }

  // --- NON-BLOCKING LORA UPDATE ---
  if (millis() - lastSendTime > sendInterval) {
    sendLoRaMessage(status);
    lastSendTime = millis();
  }
}

// --- MOTOR CONTROL FUNCTIONS ---

void moveForward() {
  // Left Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, MOTOR_SPEED);

  // Right Motor Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED);
}

void turnLeft() {
  // Left Motor Stop (or slow reverse)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  // Right Motor Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, TURN_SPEED);
}

void sharpLeft() {
  // Left Motor Reverse
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, TURN_SPEED);

  // Right Motor Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, TURN_SPEED);
}

void turnRight() {
  // Left Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, TURN_SPEED);

  // Right Motor Stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void sharpRight() {
  // Left Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, TURN_SPEED);

  // Right Motor Reverse
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, TURN_SPEED);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void sendLoRaMessage(String msg) {
  Serial.print("Sending LoRa: ");
  Serial.println(msg);
  
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
}