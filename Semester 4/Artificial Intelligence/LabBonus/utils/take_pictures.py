import cv2
import os
import argparse

def take_pictures(label, out_dir="dataset", count=100):
    save_dir = os.path.join(out_dir, label)
    os.makedirs(save_dir, exist_ok=True)

    cap = cv2.VideoCapture(0)
    img_counter = 0

    while img_counter < count:
        ret, frame = cap.read()
        if not ret:
            break
        cv2.imshow("frame", frame)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break
        elif key == ord('s'):
            img_counter += 1
            file_path = os.path.join(save_dir, str(img_counter) + ".jpg")
            cv2.imwrite(file_path, frame)

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--label", type=str, default="label")
    args = parser.parse_args()
    take_pictures(args.label)