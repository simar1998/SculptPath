import threading
import queue


class GCodeManager:
    def __init__(self):
        self.data = ""
        self.mode = None
        self.file_path = "gcode_file.gcode"

    def set_mode(self, mode):
        self.mode = mode

    def write_gcode(self, gcode):
        self.data += gcode
        with open(self.file_path, "w") as file:
            file.write(self.data)

    def process_gcode(self, task):
        if task["action"] == "write":
            self.write_gcode(task["data"])
        elif task["action"] == "set_mode":
            self.set_mode(task["data"])


class GCodeThread(threading.Thread):
    def __init__(self, gcode_manager):
        super().__init__()
        self.gcode_manager = gcode_manager
        self.queue = queue.Queue()
        self.running = False

    def run(self):
        self.running = True
        while self.running:
            try:
                task = self.queue.get(timeout=1)
                self.gcode_manager.process_gcode(task)
            except queue.Empty:
                continue

    def stop_thread(self):
        self.running = False

    def add_task(self, task):
        self.queue.put(task)
