import subprocess
import sys

def run_volnav(stl_file, gcode_file, output_dir):
    # Path to the compiled C++ executable
    executable_path = 'C:\\Code\\nonplanar-toopath-gen\\cmake-build-debug\\nonplanar.exe'  # Adjust this path as necessary

    # Prepare the command to run the C++ program
    command = [executable_path, stl_file, gcode_file, output_dir]

    # Run the command
    try:
        result = subprocess.run(command, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        print("Output:", result.stdout)
        print("Program executed successfully.")
    except subprocess.CalledProcessError as e:
        print("Error:", e.stderr)
        sys.exit(e.returncode)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python call_volnav.py <stl_file> <gcode_file> <output_dir>")
        sys.exit(1)

    stl_file = sys.argv[1]
    gcode_file = sys.argv[2]
    output_dir = sys.argv[3]

    run_volnav(stl_file, gcode_file, output_dir)
