import cv2
import numpy as np
import pygame
from pygame.locals import *


face_cap = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
video_cap = cv2.VideoCapture(0)

# Initialize Pygame
pygame.init()
screen_width, screen_height = 800, 600
screen = pygame.display.set_mode((screen_width, screen_height))
clock = pygame.time.Clock()

# Load 3D object
# Replace this with your 3D object loading code
# For simplicity, we'll just draw a cube
def draw_cube(surface, color, vertices):
    pygame.draw.polygon(surface, color, vertices)

cube_vertices = [
    (100, 100),
    (200, 100),
    (200, 200),
    (100, 200)
]

# Initialize OpenCV face detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
# cap is already initialized above as video_cap

# Constants
distance_to_screen = 50  # Distance between screen and viewer's face (in cm)

while True:
    ret, video_data = video_cap.read()
    col = cv2.cvtColor(video_data, cv2.COLOR_BGR2GRAY)
    faces = face_cap.detectMultiScale(
        col,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv2.CASCADE_SCALE_IMAGE
    )
    for (x, y, w, h) in faces:
        cv2.rectangle(video_data, (x, y), (x+w, y+h), (0, 255, 0), 2)
    cv2.imshow('video_live', video_data)
    if cv2.waitKey(10) == ord("a"):
        break

    # Clear screen
    screen.fill((0, 0, 0))

    # Draw cube
    draw_cube(screen, (255, 0, 0), cube_vertices)

    # Update Pygame display
    pygame.display.flip()

    # Calculate solid angle based on face position
    if len(faces) > 0:
        # Assuming only one face is detected
        face = faces[0]
        face_center_x = face[0] + face[2] // 2
        face_center_y = face[1] + face[3] // 2

        # Calculate the angle based on the position of the face
        angle_x = np.arctan((face_center_x - screen_width / 2) / distance_to_screen)
        angle_y = np.arctan((face_center_y - screen_height / 2) / distance_to_screen)

        # Move the 3D object in the opposite direction of the face movement
        # Here, we'll simply print the calculated angles
        print("Angle X:", angle_x)
        print("Angle Y:", angle_y)

    # Check for quit event
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            video_cap.release()
            cv2.destroyAllWindows()
            exit()

    # Limit frame rate
    clock.tick(30)

# Release resources
video_cap.release()
cv2.destroyAllWindows()