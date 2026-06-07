import cv2
import open3d as o3d
import numpy as np

# Initialize Open3D visualizer
visualizer = o3d.visualization.Visualizer()
visualizer.create_window(width=800, height=600)  # Set window size

# Load 3D Model (example: cube)
mesh = o3d.geometry.TriangleMesh.create_box(width=1.0, height=1.0, depth=1.0)
mesh.compute_vertex_normals()

# Add the mesh to visualizer
visualizer.add_geometry(mesh)

# Initialize OpenCV capture
cap = cv2.VideoCapture(0)

# Initialize variables for face detection and rotation
screen_width = 800
screen_height = 600
center_x = screen_width // 2
center_y = screen_height // 2
rotation_scale = 0.1  # Scaling factor for rotation angles

# Initialize face detection using Haar cascades
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Convert frame to grayscale for face detection
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    for (x, y, w, h) in faces:
        # Calculate center of the face
        face_center_x = x + w // 2
        face_center_y = y + h // 2

        # Calculate distances from face center to screen center
        delta_x = face_center_x - center_x
        delta_y = face_center_y - center_y

        # Convert distances to rotation angles
        angle_x = -rotation_scale * delta_y
        angle_y = rotation_scale * delta_x
        angle_z = 0.0  # Assume no rotation around z-axis

        # Apply rotation to the mesh (opposite direction)
        rotation = np.array([angle_x, angle_y, angle_z])
        mesh.rotate(mesh.get_rotation_matrix_from_xyz(rotation))

        # Draw a rectangle around the face
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        # Draw a circle at the nose coordinates
        cv2.circle(frame, (face_center_x, face_center_y), 2, (0, 0, 255), -1)

    # Update Open3D visualizer
    visualizer.update_geometry(mesh)
    visualizer.poll_events()
    visualizer.update_renderer()

    # Display the frame with face detection visualization
    cv2.imshow('Face Detection', frame)

    # Check for 'q' key press to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Clean up
cap.release()
cv2.destroyAllWindows()
visualizer.destroy_window()