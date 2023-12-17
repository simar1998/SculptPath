//
// Created by simar on 12/16/2023.
//

#include "FileInjest.h"
#include <pybind11/pybind11.h>
#include <string>
#include <iostream>
#include <pybind11/embed.h>


namespace py = pybind11;

/**
 * Ingest the file and preprocesses it for the purposes of the pipeline
 * @param filePath
 * @return A boolean value informs of ingest status
 */
bool FileInjest::ingest(std::string &filePath) {


    py::scoped_interpreter guard{}; // Start the Python interpreter
    try {
        // Import your Python module
        py::module_ converter = py::module_::import("file_processor");

        // Call the function from the module
        py::tuple py_result = converter.attr("convert_to_off")(filePath);

        // Convert the result to a C++ vector
        ogFilePath = py_result[0].cast<std::string>();
        offFilePath = py_result[0].cast<std::string>();

        return true;

    } catch (py::error_already_set& e) {
        // Handle exceptions from Python
        std::cerr << "Python error: " << e.what() << std::endl;
    }




    return false;
}
