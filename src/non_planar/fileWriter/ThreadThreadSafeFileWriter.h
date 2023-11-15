#ifndef SCULPTPATH_THREADTHREADSAFEFILEWRITER_H
#define SCULPTPATH_THREADTHREADSAFEFILEWRITER_H

#include <string>
#include <fstream>
#include <mutex>

class ThreadSafeFileWriter {
public:
    // Constructor
    explicit ThreadSafeFileWriter(const std::string& filename);

    // Prevent copy construction and assignment
    ThreadSafeFileWriter(const ThreadSafeFileWriter&) = delete;
    ThreadSafeFileWriter& operator=(const ThreadSafeFileWriter&) = delete;

    // Method to write a message to the file
    void write(const std::string& message);

    // Destructor
    ~ThreadSafeFileWriter();

private:
    std::ofstream file;
    std::mutex file_mutex;
};

#endif // SCULPTPATH_THREADTHREADSAFEFILEWRITER_H