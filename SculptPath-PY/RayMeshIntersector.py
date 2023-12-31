import numpy as np

class RayMeshIntersector:
    def __init__(self, mesh):
        self.mesh = mesh
        self.ray_origin = None
        self.ray_direction = None

    def set_ray(self, origin, direction):
        self.ray_origin = np.array(origin)
        self.ray_direction = np.array(direction)
        self.ray_direction /= np.linalg.norm(self.ray_direction)  # Normalize the direction

    def intersect(self):
        intersection_points = []

        for triangle in self.mesh.triangles:
            intersection_point = self.ray_triangle_intersect(triangle)
            if intersection_point is not None:
                intersection_points.append(intersection_point)

        return intersection_points

    def ray_triangle_intersect(self, triangle):
        vertex0, vertex1, vertex2 = [np.array(v) for v in triangle]
        edge1 = vertex1 - vertex0
        edge2 = vertex2 - vertex0
        h = np.cross(self.ray_direction, edge2)
        a = np.dot(edge1, h)

        if abs(a) < 1e-6:
            return None  # This means the ray is parallel to the triangle.

        f = 1.0 / a
        s = self.ray_origin - vertex0
        u = f * np.dot(s, h)

        if u < 0.0 or u > 1.0:
            return None

        q = np.cross(s, edge1)
        v = f * np.dot(self.ray_direction, q)

        if v < 0.0 or u + v > 1.0:
            return None

        t = f * np.dot(edge2, q)

        if t > 1e-6:  # ray intersection
            intersection_point = self.ray_origin + self.ray_direction * t
            return intersection_point

        return None


