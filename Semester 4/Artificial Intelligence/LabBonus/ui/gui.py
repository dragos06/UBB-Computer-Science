import cv2
from tkinter import Tk, messagebox
from tkinter import StringVar
from tkinter import N, S, E, W
from tkinter.ttk import Frame, Label, Button, Style
from PIL import Image, ImageTk
from sklearn.neighbors import KNeighborsClassifier
from sympy.printing.pytorch import torch
from utils.extract_face import mtcnn, facenet
from utils.train import load_dataset, train_classifier
from utils.label_box import cv2_to_pil, draw_label_circle

def launch_gui():
    App(Tk()).root.mainloop()

class App:
    def __init__(self, root):
        self.cap = None
        self.root = root
        self.root.title("Face Detection System")
        self.root.geometry("700x550")
        self.root.minsize(600, 450)
        self.root.configure(bg="#1e1e2f")  # Dark background

        # Modern style
        style = Style()
        style.theme_use("clam")
        style.configure("TFrame", background="#1e1e2f")
        style.configure("TLabel", font=("Segoe UI", 16), background="#1e1e2f", foreground="#ffffff")
        style.configure("TButton",
                        font=("Segoe UI", 12),
                        padding=(10, 6),
                        foreground="#ffffff",
                        background="#3c3f58",
                        borderwidth=0,
                        focuscolor=style.lookup("TButton", "background"))
        style.map("TButton",
                  background=[("active", "#5c5f78")],
                  relief=[("pressed", "sunken")])

        # Main frame
        self.main_frame = Frame(root, padding=20, style="TFrame")
        self.main_frame.pack(expand=True, fill="both")

        self.label = Label(self.main_frame, text="Real-Time Face Recognition", style="TLabel", anchor="center")
        self.label.pack(pady=(0, 20))

        # Video frame (larger and center-aligned)
        self.video_label = Label(self.main_frame, style="TLabel", borderwidth=2, relief="solid")
        self.video_label.pack(pady=10, ipadx=5, ipady=5)

        # Button frame
        self.button_frame = Frame(self.main_frame, padding=10, style="TFrame")
        self.button_frame.pack(pady=20)

        self.start_button = Button(self.button_frame, text="Start", command=self.start, style="TButton")
        self.start_button.grid(row=0, column=0, padx=10)

        self.stop_button = Button(self.button_frame, text="Stop", command=self.stop, style="TButton")
        self.stop_button.grid(row=0, column=1, padx=10)

        self.quit_button = Button(self.button_frame, text="Quit", command=self.root.quit, style="TButton")
        self.quit_button.grid(row=0, column=2, padx=10)

        # Load model and embeddings
        self.embeddings, self.labels = load_dataset()
        self.knn = train_classifier(self.embeddings, self.labels)
        self.running = False

    def start(self):
        consent = messagebox.askyesno("Consent",
                                      "Use your webcam to detect you, your pet, or others.\nDo you wish to continue?")
        if not consent:
            return
        self.cap = cv2.VideoCapture(0)
        self.running = True
        self.update_frame()

    def stop(self):
        self.running = False
        if hasattr(self, "cap"):
            self.cap.release()
        self.video_label.config(image='')

    def update_frame(self):
        if self.running:
            ret, frame = self.cap.read()
            if not ret:
                return
            pil_image = cv2_to_pil(frame)
            boxes, _ = mtcnn.detect(pil_image)

            label = "Nobody"
            if boxes is not None:
                for box in boxes:
                    face = pil_image.crop(box).convert("RGB")
                    emb = mtcnn(face)
                    if emb is not None:
                        with torch.no_grad():
                            pred = self.knn.predict(facenet(emb.unsqueeze(0)).detach().cpu().numpy())[0]
                        draw_label_circle(frame, box, pred)
                        label = pred
                    else:
                        draw_label_circle(frame, box, "Unknown")
            else:
                cv2.putText(frame, label, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)

            img_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            imgtk = ImageTk.PhotoImage(image=Image.fromarray(img_rgb))
            self.video_label.imgtk = imgtk
            self.video_label.configure(image=imgtk)
            self.root.after(10, self.update_frame)