int vib_pin = 7;
int led_pin = 13;
int buzzer_pin = 8; // Define the buzzer pin

void setup() {
  pinMode(vib_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT); // Set buzzer as output
}

void loop() {
  int val;
  val = digitalRead(vib_pin);
  
  if (val == 1) {
    // Turn both LED and Buzzer ON
    digitalWrite(led_pin, HIGH);
    digitalWrite(buzzer_pin, HIGH); 
    delay(1000);
    
    // Turn both LED and Buzzer OFF
    digitalWrite(led_pin, LOW);
    digitalWrite(buzzer_pin, LOW);
    delay(1000);
  } else {
    digitalWrite(led_pin, LOW);
    digitalWrite(buzzer_pin, LOW); // Ensure buzzer stays off
  }
}