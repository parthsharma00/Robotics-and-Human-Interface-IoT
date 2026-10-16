# Robotics & Human-Interface Computer Vision Suite

A comprehensive repository showcasing the evolution of Human-Computer Interaction (HCI) through Computer Vision, spanning advanced hand-gesture tracking spatial mice to real-time face-driven 3D coordinate transformations.

## 🗂️ Repository Structure & Technical Evolution

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
Real-time roll / pitch / yaw from a 6-axis IMU, fused with a **complementary filter** (98% gyro, 2% accelerometer) to cancel gyro drift, then streamed to a PC as compact binary packets at 921,600 baud so a 3D plane model can mirror the handheld sensor with minimal lag.
- Hardware: ESP32, MPU6050 (I²C at 400 kHz)
- Stack: Arduino C++ (the PC-side visualiser isn't included yet)

### 6. Radar System (`/Radar system`)
Ultrasonic radar that sweeps a servo and draws detected objects as a live radar sweep on a 1.8" TFT screen, also logging angle and distance over serial.
- Hardware: Arduino, HC-SR04, servo motor, ST7735 128×160 TFT
- Stack: Arduino C++, Adafruit GFX / ST7735

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

## 🛠️ Tech Stack
Python · OpenCV · MediaPipe · cvzone · Open3D · Pygame · Blender `bpy` · Tkinter · PyAutoGUI · Arduino C++ · ESP32 · LoRa

## 🚀 Running the projects

### Computer-vision projects (Python)
Requires Python 3.9+ and a webcam.
```bash
git clone https://github.com/parthsharma00/Robotics-and-Human-Interface-IoT.git
cd Robotics-and-Human-Interface-IoT
pip install opencv-python mediapipe cvzone pyautogui numpy open3d pygame pillow

python air-mouse/v1_mediapipe.py            # move the cursor with your index finger, pinch to click
python face-to-3d-control/open3d_version.py # rotate a 3D model with your head
python computer-vision-tools/image_filters_gui.py
```
`face-to-3d-control/blender_version.py` runs inside Blender: open the **Scripting** tab, load the file, and press **Run Script** (Blender's bundled Python needs `opencv-python` installed into it).

> On macOS, give your terminal Camera and Accessibility permissions so PyAutoGUI can move the cursor.

### Hardware projects (Arduino / ESP32)
1. Install the [Arduino IDE](https://www.arduino.cc/en/software). For the ESP32 projects, add the ESP32 board package (**Boards Manager → esp32**).
2. Install libraries as needed: `IRremote`, `LoRa` (Sandeep Mistry), `MPU6050`, `Adafruit GFX`, `Adafruit ST7735`, `LiquidCrystal I2C`.
3. For `wificamera/`, enter your own Wi-Fi name and password at the top of `wificamera.ino`, select **AI Thinker ESP32-CAM**, and open the IP address printed in the Serial Monitor.
4. Open the sketch, select the board and port, then click **Upload**.

> 📸 _Demo GIFs of the air mouse and face-to-3D control coming soon_ <!-- add docs/*.gif -->

## 👤 Author
**Parth Sharma**, Computer Science & Design at the Singapore University of Technology and Design (SUTD)
[GitHub](https://github.com/parthsharma00) · [LinkedIn](https://www.linkedin.com/in/parth-sharmasutd) · parthsharma72007@gmail.com
