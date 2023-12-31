# This is a sample Python script.
from gcode.GcodeManager import ConcurrentThread


# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Usage in main.py
if __name__ == '__main__':
    concurrent_thread = ConcurrentThread()
    concurrent_thread.start()
    # Add tasks or interact with concurrent_thread as needed
    concurrent_thread.stop()
