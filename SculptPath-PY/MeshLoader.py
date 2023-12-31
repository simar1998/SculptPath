import os

class MeshLoader:
    def __init__(self):
        self.triangles = []

    def load_file(self, file_path):
        if not os.path.exists(file_path):
            raise FileNotFoundError(f"File {file_path} not found")

        extension = os.path.splitext(file_path)[1].lower()
        if extension == '.stl':
            self.load_stl(file_path)
        elif extension == '.obj':
            self.load_obj(file_path)
        elif extension == '.off':
            self.load_off(file_path)
        else:
            raise ValueError("Unsupported file format")

    def load_stl(self, file_path):
        with open(file_path, 'r') as file:
            for line in file:
                if line.startswith('facet normal'):
                    # Skip the next line 'outer loop'
                    next(file)
                    # Read the three vertices of the triangle
                    vertices = []
                    for _ in range(3):
                        vertex_line = next(file).strip().split()
                        vertex = tuple(map(float, vertex_line[1:4]))
                        vertices.append(vertex)
                    self.triangles.append(vertices)

    def load_obj(self, file_path):
        vertices = []
        faces = []
        with open(file_path, 'r') as file:
            for line in file:
                if line.startswith('v '):
                    vertex_line = line.strip().split()
                    vertex = tuple(map(float, vertex_line[1:4]))
                    vertices.append(vertex)
                elif line.startswith('f '):
                    face_line = line.strip().split()
                    face = tuple(map(int, face_line[1:4]))
                    faces.append(face)

        for face in faces:
            triangle = [vertices[idx - 1] for idx in face]
            self.triangles.append(triangle)

    def load_off(self, file_path):
        with open(file_path, 'r') as file:
            if file.readline().strip() != 'OFF':
                raise ValueError("File is not in OFF format")

            parts = file.readline().strip().split()
            num_vertices, num_faces, _ = map(int, parts)

            vertices = [tuple(map(float, file.readline().strip().split())) for _ in range(num_vertices)]

            for _ in range(num_faces):
                face_line = file.readline().strip().split()
                face = tuple(map(int, face_line[1:4]))
                triangle = [vertices[idx] for idx in face]
                self.triangles.append(triangle)

    def print_triangles(self):
        for i, triangle in enumerate(self.triangles):
            print(f"Triangle {i}: Vertices {triangle}")

    def get_bounding_box(self):
        if not self.vertices:
            return None

        min_x = min_y = min_z = float('inf')
        max_x = max_y = max_z = float('-inf')

        for vertex in self.vertices:
            x, y, z = vertex
            min_x, max_x = min(min_x, x), max(max_x, x)
            min_y, max_y = min(min_y, y), max(max_y, y)
            min_z, max_z = min(min_z, z), max(max_z, z)

        return (min_x, min_y, min_z), (max_x, max_y, max_z)
