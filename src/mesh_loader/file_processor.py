import pymesh
import os

def convert_to_off(input_path):
    """
    Converts a 3D model file from STL or OBJ format to OFF format.
    Returns a tuple of the original file path and the converted OFF file path.
    """
    # Check if the file exists
    if not os.path.exists(input_path):
        raise FileNotFoundError(f"File {input_path} not found")

    # Load the mesh
    mesh = pymesh.load_mesh(input_path)

    # Create the output file path with .off extension
    output_path = os.path.splitext(input_path)[0] + '.off'

    # Save the mesh in OFF format
    pymesh.save_mesh(output_path, mesh, ascii=True)

    return input_path, output_path


