import numpy as np
import random

from RayMeshIntersector import RayMeshIntersector
from NonPlanarNavigation import NonPlanarNavigator


class VolumeNavigator:
    def __init__(self, mesh, num_samples):
        self.mesh = mesh
        self.num_samples = num_samples
        self.intersections = []

    def is_point_inside_mesh(self, point):
        # Cast a ray from the point in an arbitrary direction
        ray_direction = np.array([1, 0, 0])  # Example: along the x-axis

        intersector = RayMeshIntersector(self.mesh)
        intersector.set_ray(origin=point, direction=ray_direction)
        intersections = intersector.intersect()

        # Determine inside/outside based on the number of intersections
        return len(intersections) % 2 == 1

    def generate_random_point_inside_mesh(self):
        min_point, max_point = self.mesh.get_bounding_box()
        while True:
            random_point = [random.uniform(min_point[i], max_point[i]) for i in range(3)]
            if self.is_point_inside_mesh(random_point):
                return random_point

    def create_globular_ray_burst(self, origin):
        # Generate rays in multiple directions from the origin
        # This requires a method to uniformly distribute directions in a sphere
        rays = []
        for _ in range(100):  # Example: 100 rays
            direction = np.random.randn(3)  # This gives a random direction
            direction /= np.linalg.norm(direction)  # Normalize the direction
            rays.append(direction)
        return rays

    def navigate(self, method='random'):
        if method == 'random':
            self.navigate_using_random_sampling()
        elif method == 'other':
            self.navigate_using_other_method()
        elif method == 'non_planar':
            self.navigate_non_planar()
        else:
            raise ValueError("Unknown navigation method")

    def navigate_using_random_sampling(self):
        for _ in range(self.num_samples):
            point = self.generate_random_point_inside_mesh()
            self.process_point(point)

    def navigate_using_other_method(self):
        # Placeholder for another point selection method
        pass

    # Method to navigate the volume with non-planar bounding rules
    def navigate_non_planar(self):
        non_planar_navigator = NonPlanarNavigator(self.mesh)
        non_planar_navigator.navigate()
        pass

    def process_point(self, point):
        rays = self.create_globular_ray_burst(point)
        for ray in rays:
            intersector = RayMeshIntersector(self.mesh)
            intersector.set_ray(origin=point, direction=ray)
            intersection_point = intersector.intersect()
            if intersection_point:
                self.intersections.extend(intersection_point)
                print(f"Ray from {point} intersects at {intersection_point}")

    def get_intersections(self):
        return self.intersections
