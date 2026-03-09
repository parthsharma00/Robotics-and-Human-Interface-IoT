#include <IRremote.h>

// --- PIN DEFINITIONS ---
const int RECV_PIN = 11;      
const int MOTOR_1 = 8;        
const int MOTOR_2 = 9;        
const int STATUS_LED = 13;    

// --- STATE TRACKING ---
bool m1State = false; 
bool m2State = false;

void setup() {
  Serial.begin(9600);
  
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  
  // Set Relays to OFF (Most are Active Low, so HIGH = OFF)
  digitalWrite(MOTOR_1, HIGH);
  digitalWrite(MOTOR_2, HIGH);
  digitalWrite(STATUS_LED, LOW);

  Serial.println("--- System Active ---");
  Serial.println("Motor 1: 0x2 | Motor 2: 0x3 | STOP: 0x12");
}

void loop() {
  if (IrReceiver.decode()) {
    uint16_t cmd = IrReceiver.decodedIRData.command;

    if (cmd != 0) {
      digitalWrite(STATUS_LED, HIGH); // Flash LED on any signal
      
      // --- LOGIC FOR MOTOR 1 ---
      if (cmd == 0x2) { 
        m1State = !m1State;
        digitalWrite(MOTOR_1, m1State ? LOW : HIGH);
        Serial.println(m1State ? "Motor 1: ON" : "Motor 1: OFF");
      }

      // --- LOGIC FOR MOTOR 2 ---
      else if (cmd == 0x3) {
        m2State = !m2State;
        digitalWrite(MOTOR_2, m2State ? LOW : HIGH);
        Serial.println(m2State ? "Motor 2: ON" : "Motor 2: OFF");
      }

      // --- MASTER OFF (0x12) ---
      else if (cmd == 0x12) {
        m1State = false;
        m2State = false;
        digitalWrite(MOTOR_1, HIGH); // Force OFF
        digitalWrite(MOTOR_2, HIGH); // Force OFF
        Serial.println("!!! EMERGENCY STOP: BOTH MOTORS OFF !!!");
      }

      delay(200); 
      digitalWrite(STATUS_LED, LOW);
    }
    IrReceiver.resume();
  }
}