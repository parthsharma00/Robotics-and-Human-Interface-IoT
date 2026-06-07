# Robotics & Human-Interface Computer Vision Suite

A comprehensive repository showcasing the evolution of Human-Computer Interaction (HCI) through Computer Vision, spanning advanced hand-gesture tracking spatial mice to real-time face-driven 3D coordinate transformations.

## � Repository Structure & Technical Evolution

### 1. Air Mouse Interface (`/air-mouse`)
Demonstrates 3 progressively advanced implementations of standard webcam cursor control:
- **`v1_mediapipe.py`:** Utilizes MediaPipe Hand Landmark tracking. Maps index finger coordinates to screen space and handles mouse click actions via continuous distance checks between the thumb and index fingertips.
- **`v2_contour.py`:** An legacy approach leveraging classical image processing. Tracks localized color/intensity contours to guide the OS cursor without deep landmark models.
- **`v3_cvzone_drag.py`:** A polished interactive implementation using `cvzone` tracking UI to seamlessly manipulate transparent interactive canvas components in real time.

### 2. Real-Time Face-to-3D Coordinate Control (`/face-to-3d-control`)
Implements real-time spatial manipulation of 3D objects using live facial tracking data, mapped across 3 separate engines:
- **`open3d_version.py`:** Processes live facial vectors to rotate a 3D bounding frame within a low-overhead Open3D point-cloud/mesh environment.
- **`pygame_version.py`:** An iterative version utilizing mathematical perspective projections to translate face position vectors into a rendered interactive Pygame 3D viewport.
- **`blender_version.py`:** Leverages Blender's native `bpy` API engine, using live external video frames to dynamically rotate internal 3D assets.

### 3. Computer Vision Utilities (`/computer-vision-tools`)
- **`face_detector.py`:** Classical Haar Cascade spatial tracking that performs face region isolation.
- **`image_filters_gui.py`:** A comprehensive Tkinter UI pipeline providing real-time CV parameter adjustments (HSV threshold limits, Gaussian blurring, Canny Edge tuning, Dilation, and Erosion matrix kernels).

### 4. Dual-Mode Robot (`/dual mode robot`)
Autonomous line-following robot with Bluetooth gamepad manual override. 
Ultrasonic emergency-stop logic prevents collisions in both modes.
- Hardware: Arduino Uno, HC-SR04 ultrasonic, HC-05 Bluetooth, IR sensors
- 30+ test runs with zero crashes. Sub-1 second Bluetooth control latency.

### 5. MPU6050 3D Orientation System (`/mpu6050plane`)
Real-time 6-axis gyroscope data mapped to a live 3D plane visualisation on-screen.
Handheld sensor mirrors a digital model in real time.
- Hardware: MPU6050, Arduino
- Stack: Python, matplotlib/OpenGL visualisation

### 6. Radar System (`/Radar system`)
Ultrasonic radar that sweeps a servo motor and plots detected objects on a 
Processing/Python radar display in real time.
- Hardware: Arduino, HC-SR04, servo motor
- Stack: Arduino C++, Processing/Python serial

### 7. LoRa Wireless Module (`/lora module`)
Long-range wireless communication system using LoRa SX1276 modules.
Transmits sensor data over 1km+ range without WiFi infrastructure.
- Hardware: LoRa SX1276, Arduino
- Stack: Arduino C++

### 8. WiFi Camera (`/wificamera`)
ESP32-CAM based wireless video streaming system. Live feed accessible 
over local network via browser.
- Hardware: ESP32-CAM
- Stack: Arduino C++, ESP32 WiFi library

### 9. IR Remote (`/IRRemote`)
Universal IR remote decoder and transmitter. Reads and replays any IR 
remote signal using TSOP receiver and IR LED.
- Hardware: Arduino, TSOP IR receiver, IR LED
- Stack: Arduino C++, IRremote library

### 10. Sound Sensor (`/soundsensor`)
Clap-activated trigger system using sound amplitude threshold detection.
- Hardware: Arduino, KY-038 sound sensor
- Stack: Arduino C++

### 11. Vibration Sensor (`/vibrationsensor`)
Impact and vibration detection system with configurable sensitivity threshold.
Triggers alerts on detected physical disturbance.
- Hardware: Arduino, SW-420 vibration sensor
- Stack: Arduino C++

## 🛠️ Prerequisites & Core Toolkits
- OpenCV, MediaPipe, `cvzone`, Open3D, Pygame, Blender `bpy`, Tkinter

