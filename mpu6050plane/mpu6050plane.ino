#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

float roll, pitch, yaw;
unsigned long lastTime;

// Buffer to store 3 floats (12 bytes) + Header
byte buffer[12]; 

void setup() {
  // Max stable Baud for most ESP32 USB-Serial chips
  Serial.begin(921600); 
  
  Wire.begin(21, 22);
  Wire.setClock(400000); 
  
  mpu.initialize();
  mpu.setSleepEnabled(false);
  
  // High-speed settings
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  lastTime = micros();
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float dt = (micros() - lastTime) / 1000000.0;
  lastTime = micros();

  // Optimized Filter Math
  float accRoll = atan2(ay, az) * 57.2958;
  float accPitch = atan2(-ax, sqrt((long)ay * ay + (long)az * az)) * 57.2958;

  roll = 0.98 * (roll + (gx / 131.0) * dt) + 0.02 * accRoll;
  pitch = 0.98 * (pitch + (gy / 131.0) * dt) + 0.02 * accPitch;
  yaw += (gz / 131.0) * dt;

  // BINARY PACKING: Convert 3 floats into 12 raw bytes
  memcpy(buffer, &roll, 4);
  memcpy(buffer + 4, &pitch, 4);
  memcpy(buffer + 8, &yaw, 4);

  // Send a 'Header' byte (0xFF) so Processing can sync, then the 12 bytes
  Serial.write(0xFF); 
  Serial.write(buffer, 12);
}