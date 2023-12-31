import numpy as np

from RayMeshIntersector import RayMeshIntersector


class GridRayIntersector:
    def __init__(self, mesh, offset, grid_resolution, verbose=False):
        self.mesh = mesh
        self.offset = offset
        self.grid_resolution = grid_resolution
        self.verbose = verbose
        self.intersections = []

    def generate_grid_points(self):
        min_point, max_point = self.mesh.get_bounding_box()
        min_x, min_y, min_z = min_point
        max_x, max_y, max_z = max_point

        # Creating an offset plane above the mesh
        z_plane = max_z + self.offset

        # Generate grid points
        grid_points = []
        x_range = np.linspace(min_x, max_x, self.grid_resolution)
        y_range = np.linspace(min_y, max_y, self.grid_resolution)

        for x in x_range:
            for y in y_range:
                grid_points.append((x, y, z_plane))

        return grid_points

    def intersect_rays(self):
        grid_points = self.generate_grid_points()
        ray_direction = np.array([0, 0, -1])  # Downward direction

        for point in grid_points:
            intersector = RayMeshIntersector(self.mesh)
            intersector.set_ray(origin=point, direction=ray_direction)
            intersection_point = intersector.intersect()

            if intersection_point:
                self.intersections.extend(intersection_point)

                if self.verbose:
                    print(f"Ray from {point} intersects at {intersection_point}")

    def get_intersections(self):
        return self.intersections