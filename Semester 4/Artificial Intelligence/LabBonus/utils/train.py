import numpy as np
from PIL import Image
import os
import glob
from sklearn.neighbors import KNeighborsClassifier
from utils.extract_face import extract_face

def load_dataset(data_path="dataset"):
    embeddings = []
    labels = []

    for label in os.listdir(data_path):
        label_path = os.path.join(data_path, label)
        if not os.path.isdir(label_path):
            continue
        for image_path in glob.glob(os.path.join(label_path, "*.jpg")):
            try:
                image = Image.open(image_path).convert('RGB')
                embedding = extract_face(image)
                if embedding is not None:
                    embeddings.append(embedding)
                    labels.append(label)
            except Exception as e:
                print(e)
                continue

    return np.array(embeddings), np.array(labels)

def train_classifier(embeddings, labels):
    knn = KNeighborsClassifier(n_neighbors=1)
    knn.fit(embeddings, labels)
    return knn