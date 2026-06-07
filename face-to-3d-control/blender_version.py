# NOTE: This script requires Blender to be installed and bpy module to be available
# Run this script from within Blender or ensure Blender Python environment is set up
import bpy
import cv2
import numpy as np

# Initialize camera
cap = cv2.VideoCapture(0)

# Initialize previous face position
prev_face_position = None

while True:
    # Capture frame
    ret, frame = cap.read()
    if not ret:
        break

    # Convert frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces
    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # Draw rectangles around detected faces and track movement
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
        face_position = np.array([x + w / 2, y + h / 2])  # Face position: center of the face bounding box

        # Calculate movement direction
        if prev_face_position is not None:
            movement_direction = prev_face_position - face_position
            opposite_direction = -movement_direction  # Opposite direction
            print("Opposite Direction:", opposite_direction)

            # Rotate 3D object in Blender
            bpy.context.scene.objects['Cube'].rotation_euler.x += opposite_direction[1] * 0.01  # Adjust scale factor as needed
            bpy.context.scene.objects['Cube'].rotation_euler.y += opposite_direction[0] * 0.01  # Adjust scale factor as needed

        # Update previous face position
        prev_face_position = face_position

    # Display the resulting frame
    cv2.imshow('Face Tracking', frame)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources
cap.release()
cv2.destroyAllWindows()