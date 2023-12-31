from PlaneIntersect import PlaneIntersect
import numpy as np

class EntryPointCalculator:

    def __init__(self, mesh):
        self.mesh = mesh
        self.entryPointList = []
        self.bestCandidate = None

    def calculate_directional_changes(self, points):
        changes = []
        for i in range(1, len(points) - 1):
            # For each point (excluding first and last), get the previous and next points
            prev, current, next = points[i - 1], points[i], points[i + 1]

            # Calculate directional vectors from the previous to the current point and from the current to the next point
            direction1 = np.array(current) - np.array(prev)
            direction2 = np.array(next) - np.array(current)

            # Calculate the angle between these two vectors using the dot product formula
            angle = np.arccos(
                np.dot(direction1, direction2) / (np.linalg.norm(direction1) * np.linalg.norm(direction2)))
            changes.append(angle)  # Store the calculated angle

        return sum(changes)  # Return the sum of all angle changes

    def calculate_entry_points(self, offset=0.1):
        # Retrieve the mesh's bounding box
        bbox = self.mesh.get_bounding_box()
        if not bbox:  # Exit if there's no bounding box
            return

        # Calculate the z-value of a plane slightly above the bottom of the mesh
        min_x, min_y, min_z = bbox[0]
        plane_z_value = min_z + offset

        # Create a PlaneIntersect object and calculate intersections with the plane
        plane_intersector = PlaneIntersect(self.mesh, plane_z_value)
        plane_intersector.calculate_intersections()
        self.entryPointList = plane_intersector.get_intersections()

        # If there are entry points, find the one with the least directional change
        if self.entryPointList:
            self.bestCandidate = min(self.entryPointList,
                                     key=lambda p: self.calculate_directional_changes(self.entryPointList))

    def add_entry_point(self, point):
        # Add a new point to the entry point list
        self.entryPointList.append(point)

    def get_best_candidate(self):
        # Retrieve the best candidate among the entry points
        return self.bestCandidate
