import numpy as np


def bukin_n6(x, y):
    # Bukin N6 function
    return 100 * np.sqrt(np.abs(y - 0.01 * x**2)) + 0.01 * np.abs(x + 10)

DOMAIN_X = (-15, -5)
DOMAIN_Y = (-3, 3)