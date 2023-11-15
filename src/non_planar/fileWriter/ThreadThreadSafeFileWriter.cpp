//
// Created by simar on 11/15/2023.
//

#include "ThreadThreadSafeFileWriter.h"

ThreadSafeFileWriter::ThreadSafeFileWriter(const std::string &filename) {
    file.open(filename, std::ios::out | std::ios::app); // Open in append mode
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
}

void ThreadSafeFileWriter::write(const std::string &message) {
    std::lock_guard<std::mutex> guard(file_mutex);
    if (file.is_open()) {
        file << message << std::endl;
    } else {
        throw std::runtime_error("Write attempt on closed file");
    }
}

ThreadSafeFileWriter::~ThreadSafeFileWriter() {
    if (file.is_open()) {
        file.close();
    }
}
