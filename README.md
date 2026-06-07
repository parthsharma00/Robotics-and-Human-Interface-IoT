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

## 🛠️ Prerequisites & Core Toolkits
- OpenCV, MediaPipe, `cvzone`, Open3D, Pygame, Blender `bpy`, Tkinter
