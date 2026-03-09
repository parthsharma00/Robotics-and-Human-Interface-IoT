#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>

// --- LCD PIN CONFIGURATION ---
#define TFT_CS     10
#define TFT_RST    8  
#define TFT_DC     9
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// --- COMPONENT PINS ---
const int trigPin = 2; 
const int echoPin = 3; 
const int ENA = 5;      
const int IN1 = 6;      
const int IN2 = 7;      

// --- VARIABLES ---
unsigned long moveStartTime;
const int sweepDuration = 10000; 
bool sweepingRight = true;
int lastAngle = -1;

void setup() {
  Serial.begin(115200);

  // Screen Init
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, HIGH); delay(50);
  digitalWrite(TFT_RST, LOW);  delay(100);
  digitalWrite(TFT_RST, HIGH); delay(100);

  tft.initR(INITR_BLACKTAB); // Updated for 1.8" 128x160
  tft.setRotation(1); 
  tft.fillScreen(ST7735_BLACK);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  moveStartTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  int currentAngle;

  // Check if it's time to change direction
  if (currentTime - moveStartTime >= sweepDuration) {
    sweepingRight = !sweepingRight;
    moveStartTime = currentTime;
    tft.fillScreen(ST7735_BLACK); 
  }

  // --- DIRECTION & SPEED LOGIC ---
  if (sweepingRight) {
    // Clockwise Sweep
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 120); // Speed set to 120
    currentAngle = map(currentTime - moveStartTime, 0, sweepDuration, 0, 180);
  } else {
    // Anti-Clockwise Sweep
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, 122); // Speed set to 122
    currentAngle = map(currentTime - moveStartTime, 0, sweepDuration, 180, 0);
  }

  // --- SENSOR & LCD UPDATE ---
  if (currentAngle != lastAngle) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);
    int distance = (int)(duration * 0.034 / 2);
    if (distance <= 0 || distance > 400) distance = 400;

    // Send to Processing
    Serial.print(currentAngle);
    Serial.print(",");
    Serial.print(distance);
    Serial.println("."); 

    drawRadar(currentAngle, distance);
    lastAngle = currentAngle;
  }
}

void drawRadar(int ang, int dist) {
  int cx = 80; // Center for 1.8" 160x128 screen
  int cy = 115; 
  float rad = radians(ang);
  int x2 = cx + cos(PI + rad) * 70;
  int y2 = cy + sin(PI + rad) * 70;

  uint16_t color = (dist < 40) ? ST7735_RED : ST7735_GREEN;
  tft.drawLine(cx, cy, x2, y2, color);
}