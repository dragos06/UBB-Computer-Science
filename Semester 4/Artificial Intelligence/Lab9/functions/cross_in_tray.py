import numpy as np

def cross_in_tray(x, y):
    # Cross-in-tray function
    term = np.abs(100 - np.sqrt(x**2 + y**2) / np.pi)
    return -0.0001 * (np.abs(np.sin(x) * np.sin(y) * np.exp(term)) + 1) ** 0.1

DOMAIN = (-10, 10)