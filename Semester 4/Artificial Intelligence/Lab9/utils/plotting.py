import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def plot_function(func, xlim, ylim, title):
    x = np.linspace(*xlim, 400)
    y = np.linspace(*ylim, 400)
    X, Y = np.meshgrid(x, y)
    Z = func(X, Y)

    fig = plt.figure(figsize=(12, 5))

    ax1 = fig.add_subplot(1, 2, 1)
    cp = ax1.contourf(X, Y, Z, levels=50, cmap='viridis')
    fig.colorbar(cp, ax=ax1)
    ax1.set_title(f'{title} - Countor')

    ax2 = fig.add_subplot(1, 2, 2, projection='3d')
    ax2.plot_surface(X, Y, Z, cmap='viridis', edgecolor='none')
    ax2.set_title(f'{title} - 3D Surface')

    plt.tight_layout()
    plt.show()