class PlaneIntersect:
    def __init__(self, mesh, plane_z_value):
        self.mesh = mesh
        self.plane_z_value = plane_z_value
        self.intersections = []

    def calculate_intersections(self):
        for triangle in self.mesh.triangles:
            for i in range(3):
                p1 = triangle[i]
                p2 = triangle[(i + 1) % 3]
                if (p1[2] - self.plane_z_value) * (p2[2] - self.plane_z_value) < 0:
                    # Triangle edge intersects the plane
                    t = (self.plane_z_value - p1[2]) / (p2[2] - p1[2])
                    x = p1[0] + t * (p2[0] - p1[0])
                    y = p1[1] + t * (p2[1] - p1[1])
                    self.intersections.append((x, y, self.plane_z_value))

    def get_intersections(self):
        return self.intersections
