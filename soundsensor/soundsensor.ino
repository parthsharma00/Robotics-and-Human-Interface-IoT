const int soundSensor = 2; 
const int ledPin = 13;     
const int buzzerPin = 8;   

bool ledState = false; // Stores if the LED is ON (true) or OFF (false)

void setup() {
  pinMode(soundSensor, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(soundSensor);

  // If sound is detected
  if (sensorValue == HIGH) { 
    ledState = !ledState; // Flip the state (If it was true, it becomes false)
    
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    
    // Quick beep for feedback
    digitalWrite(buzzerPin, HIGH);
    delay(100); 
    digitalWrite(buzzerPin, LOW);

    Serial.print("LED is now: ");
    Serial.println(ledState ? "ON" : "OFF");

    // "Debounce" delay: prevents one clap from being counted as 10 claps
    delay(500); 
  }
}