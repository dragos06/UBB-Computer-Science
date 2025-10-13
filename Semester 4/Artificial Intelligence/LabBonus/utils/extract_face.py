import torch
from facenet_pytorch import MTCNN, InceptionResnetV1

device = 'cuda' if torch.cuda.is_available() else 'cpu'

mtcnn = MTCNN(keep_all=False, device=device)
facenet = InceptionResnetV1(pretrained='vggface2').eval().to(device)

def extract_face(frame):
    face = mtcnn(frame)
    if face is not None:
        with torch.no_grad():
            embedding = facenet(face.unsqueeze(0))
            embedding = embedding.cpu().numpy()
        return embedding[0]
    return None
            