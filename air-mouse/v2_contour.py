import cv2
import numpy as np
import pyautogui

# Capture video from the webcam
cap = cv2.VideoCapture(0)

# Get the screen size
screen_width, screen_height = pyautogui.size()

while True:
    # Read the frame from the camera
    _, frame = cap.read()

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Apply Gaussian blur to the frame
    blurred = cv2.GaussianBlur(gray, (35, 35), 0)

    # Apply thresholding to the blurred frame
    _, thresh = cv2.threshold(blurred, 127, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    # Find contours in the threshold frame
    contours, _ = cv2.findContours(thresh.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    # If contours were found
    if contours:
        # Find the largest contour
        largest_contour = max(contours, key=cv2.contourArea)

        # Get the moments of the largest contour
        moments = cv2.moments(largest_contour)

        # Calculate the centroid of the largest contour
        if moments['m00'] != 0:
            cx = int(moments['m10'] / moments['m00'])
            cy = int(moments['m01'] / moments['m00'])

            # Move the cursor to the position of the centroid
            pyautogui.moveTo(cx * screen_width // frame.shape[1], cy * screen_height // frame.shape[0])

    # Display the frame
    cv2.imshow('Frame', frame)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and destroy all windows
cap.release()
cv2.destroyAllWindows()
