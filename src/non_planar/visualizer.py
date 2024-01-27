import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.colors as mcolors

def cartesian_to_polar(x, y, z):
    r = np.sqrt(x**2 + y**2 + z**2)
    theta = np.arctan2(y, x)  # Azimuthal angle
    phi = np.arccos(z / r)  # Polar angle
    return r, theta, phi
def plot_3d_points(file_path):
    xs, ys, zs = [], [], []
    origin = None

    with open(file_path, 'r') as file:
        for line in file:
            if 'Origin:' in line:
                _, ox, oy, oz = line.split()
                origin = (float(ox), float(oy), float(oz))
            else:
                x, y, z = map(float, line.split())
                xs.append(x)
                ys.append(y)
                zs.append(z)

    fig = plt.figure(figsize=(18, 6))
    ax1 = fig.add_subplot(131, projection='3d')
    ax2 = fig.add_subplot(132)
    ax3 = fig.add_subplot(133, projection='3d')

    # 1st Visualization: Plot the intersection points in 3D
    ax1.scatter(xs, ys, zs)
    ax1.set_title("3D Scatter of Intersection Points")

    # Highlight the origin point in 3D scatter plot
    if origin:
        ax1.scatter(*origin, color='red', s=100)
        ax1.text(*origin, "Origin", color='red')

    # 2nd Visualization: Plot the distances in 2D
    if origin:
        distances = [np.sqrt((x - origin[0])**2 + (y - origin[1])**2 + (z - origin[2])**2) for x, y, z in zip(xs, ys, zs)]
        ax2.plot(distances, 'o-')
        ax2.set_title("Distance from Origin to Points")
        ax2.set_xlabel("Point Index")
        ax2.set_ylabel("Distance")

    # 3rd Visualization: Represent points in polar coordinates
    if origin:
        ax3 = fig.add_subplot(133, projection='3d')
        for x, y, z in zip(xs, ys, zs):
            r, theta, phi = cartesian_to_polar(x - origin[0], y - origin[1], z - origin[2])
            ax3.scatter(theta, phi, r)  # Plot in polar coordinates
        ax3.set_title("Polar Coordinate Representation")
        ax3.set_xlabel("Azimuthal Angle (Theta)")
        ax3.set_ylabel("Polar Angle (Phi)")
        ax3.set_zlabel("Radius (r)")

    plt.show()

if __name__ == "__main__":
    plot_3d_points("intersection_points.txt")
