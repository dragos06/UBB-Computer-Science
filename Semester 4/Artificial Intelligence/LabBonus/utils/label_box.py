import cv2
from PIL import Image

def cv2_to_pil(image):
    return Image.fromarray(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))

def draw_label_circle(frame, box, label):
    box = [int(b) for b in box]
    center_x = (box[0] + box[2]) // 2
    center_y = (box[1] + box[3]) // 2
    radius = int(((box[2] - box[0])**2 + (box[3] - box[1])**2)**0.5 // 2)

    cv2.circle(frame, (center_x, center_y), radius, (0, 255, 0), 2, cv2.LINE_AA)
    cv2.putText(frame, label, (center_x - radius, center_y - radius - 10),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2, cv2.LINE_AA)
