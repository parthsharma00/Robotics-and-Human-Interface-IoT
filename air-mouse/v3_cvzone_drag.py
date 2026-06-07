import cv2
import cvzone
from cvzone.HandTrackingModule import HandDetector
import numpy as np

cap = cv2.VideoCapture(0)  # Open webcam

# Set resolution
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

detector = HandDetector(detectionCon=0.8, maxHands=1)
colorR = (255, 0, 0)  # Red color for rectangles

class DragRect:
    def __init__(self, posCenter, size=[200, 200]):
        self.posCenter = posCenter
        self.size = size

    def update(self, cursor):
        cx, cy = self.posCenter
        w, h = self.size

        # ONLY update position if the cursor is inside this specific rectangle
        if cx - w // 2 < cursor[0] < cx + w // 2 and cy - h // 2 < cursor[1] < cy + h // 2:
            self.posCenter = cursor

rectList = []
for x in range(5):
    rectList.append(DragRect([x * 250 + 150, 150]))  # Create rectangles

while True:
    success, img = cap.read()

    if not success:  # Handle potential capture failures
        print("Error: Unable to capture frame from webcam.")
        break

    img = cv2.flip(img, 1)  # Flip image horizontally

    # FIX 1: cvzone returns (hands, img). Unpack it correctly.
    hands, img = detector.findHands(img, draw=False) 
    
    if hands:
        hand = hands[0]
        lmList = hand['lmList']  # In modern cvzone, hand is a dictionary
        
        if len(lmList) > 12:  # Ensure we have enough landmarks
            # Get x, y of index (8) and middle (12) finger tips
            p1 = lmList[8][:2]  
            p2 = lmList[12][:2]  
            
            # FIX 2: Correct arguments for cvzone's findDistance
            l, _, _ = detector.findDistance(p1, p2, img)

            if l < 40:  # If fingers close together (pinched)
                cursor = p1  # Use index finger tip as cursor
                for rect in rectList:
                    rect.update(cursor)  # Checks boundaries before moving

    # Draw rectangles (transparency version)
    imgNew = np.zeros_like(img, np.uint8)
    alpha = 0.5  # Boosted alpha slightly so they are easier to see
    
    for rect in rectList:
        cx, cy = rect.posCenter
        w, h = rect.size
        cv2.rectangle(imgNew, (cx - w // 2, cy - h // 2), (cx + w // 2, cy + h // 2), colorR, cv2.FILLED)
        cvzone.cornerRect(imgNew, (cx - w // 2, cy - h // 2, w, h), 20, rt=0)

    # Apply transparency overlay accurately
    mask = imgNew.astype(bool)
    out = img.copy()
    out[mask] = cv2.addWeighted(img, alpha, imgNew, 1 - alpha, 0)[mask]

    cv2.imshow("Image", out)

    if cv2.waitKey(1) & 0xFF == ord('q'):  # Exit on 'q' press
        break

cap.release()
cv2.destroyAllWindows()