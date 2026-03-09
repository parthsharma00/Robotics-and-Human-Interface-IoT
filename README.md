# 🎮 Robotics & Human Interface Lab

This repository explores the intersection of **Mechatronics** and **User Interaction**. It features projects that transform physical movement and environmental signals into digital visualizations and robotic actions.

## 🚀 Overview
The projects here focus on **Feedback Loops**—how a machine "sees" its surroundings (Radar, Cam) and how a human "controls" the machine (IR, Sound, Gyro).

---

## 🛠️ Included Projects

### 1. 🛰️ Ultrasonic Radar Visualization
* **What it does:** Scans the environment using a rotating sonar. Objects are visualized on a screen as a green sweep that turns red when an obstacle is detected within range.
* **Key Components:** HC-SR04 Ultrasonic Sensor, Servo Motor, Processing/OLED.
* **Use Case:** Proximity awareness for autonomous vehicles.

### 2. 📐 3D Gyroscopic Orientation (MPU6050)
* **What it does:** Tracks 6-axis movement (accelerometer + gyro) to tilt a digital 3D model in real-time as the physical hardware is moved.
* **Key Components:** MPU6050 IMU, Complementary Filtering.
* **Use Case:** Flight stabilization and motion-capture input.

### 3. 📹 ESP32-Cam Wireless Node
* **What it does:** Hosts a local web server that streams live video over Wi-Fi, accessible from any browser on the same network.
* **Key Components:** ESP32-Cam Module, OV2640 Camera.
* **Use Case:** Remote inspection and DIY security monitoring.

### 4. 📶 Infrared (IR) Power Controller
* **What it does:** Uses an IR receiver to decode signals from a remote control, allowing a user to toggle high-power motors via a dual-relay module.
* **Key Components:** TSOP IR Receiver, 2-Channel Relay Module.
* **Use Case:** Universal remote control for home appliances.

### 5. 👏 Acoustic Trigger (Sound Sensor)
* **What it does:** Listens for specific sound thresholds (like a clap) to trigger an LED or actuator.
* **Key Components:** High-sensitivity Sound Microphone Module.
* **Use Case:** Hands-free lighting control and sound-activated security.

---

## 📂 Project Structure
- `/Radar-Scanner` -> Includes both the Arduino code and the Visualization script.
- `/Gyro-3D-Model` -> Logic for translating raw IMU data into 3D coordinates.
- `/Wireless-Cam` -> Web server configuration and Wi-Fi credentials setup.

---
*Focused on the development of intuitive Human-Machine Interfaces (HMI).*
