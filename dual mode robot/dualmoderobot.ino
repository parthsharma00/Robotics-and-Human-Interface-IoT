#include <SoftwareSerial.h>

// --- PIN DEFINITIONS ---
const int ENA = 11; const int IN1 = 10; const int IN2 = 9;
const int ENB = 3;  const int IN3 = 6;  const int IN4 = 5;

const int S4_OUT_L = A3; 
const int S3_IN_L  = A1; 
const int S2_IN_R  = A0; 
const int S1_OUT_R = A2;

const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
const int BUZZER_PIN = 4; // Annoying siren pin

SoftwareSerial BT(12, 13);

// --- STATE VARIABLES ---
bool isAuto = false;
int baseSpeed = 120;
int turnSpeed = 150;

void setup() {
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  BT.begin(9600);
}

void loop() {
  long distance = getDistance();
  
  if (distance > 0 && distance < 15) {
    stopMotors();
    playAnnoyingSiren(); // Kick off the alarm
  } 
  else {
    digitalWrite(BUZZER_PIN, LOW); // Silence when clear
    
    if (BT.available()) {
      char cmd = BT.read();
      if (cmd == 'X') isAuto = true;
      else if (cmd == 'F' || cmd == 'B' || cmd == 'L' || cmd == 'R' || cmd == 'S') {
        isAuto = false;
        executeManual(cmd);
      }
    }

    if (isAuto) {
      runLineFollower();
    }
  }
}

// --- ALARM FUNCTION ---
void playAnnoyingSiren() {
  // Rapidly oscillates between two high-pitched frequencies
  for (int i = 0; i < 5; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    delay(30);
  }
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH, 20000); 
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

// --- LINE FOLLOWER & MANUAL LOGIC ---
void runLineFollower() {
  int outL = digitalRead(S4_OUT_L);
  int inL  = digitalRead(S3_IN_L);
  int inR  = digitalRead(S2_IN_R);
  int outR = digitalRead(S1_OUT_R);

  if (outL == 1)      hardLeft(turnSpeed);
  else if (outR == 1) hardRight(turnSpeed);
  else if (inL == 0 && inR == 0) forward(baseSpeed);
  else if (inL == 1 && inR == 0) pivotLeft(turnSpeed);
  else if (inR == 1 && inL == 0) pivotRight(turnSpeed);
  else if (inL == 1 && inR == 1) stopMotors();
}

void executeManual(char cmd) {
  switch (cmd) {
    case 'F': forward(baseSpeed); break;
    case 'B': backward(baseSpeed); break;
    case 'L': hardLeft(turnSpeed); break;
    case 'R': hardRight(turnSpeed); break;
    case 'S': stopMotors(); break;
  }
}

// --- MOTOR DRIVE ---
void forward(int spd) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, spd);   analogWrite(ENB, spd);
}

void backward(int spd) {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, spd);   analogWrite(ENB, spd);
}

void pivotLeft(int spd) {
  analogWrite(ENA, 0);   analogWrite(ENB, spd);
}

void pivotRight(int spd) {
  analogWrite(ENA, spd); analogWrite(ENB, 0);
}

void hardLeft(int spd) {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, spd);   analogWrite(ENB, spd);
}

void hardRight(int spd) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  analogWrite(ENA, spd);   analogWrite(ENB, spd);
}

void stopMotors() {
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}