//
// Created by simar on 1/16/2024.
//

#ifndef SCULPTPATH_MESHEXCEPTION_H
#define SCULPTPATH_MESHEXCEPTION_H

//
// Created by simar on 1/16/2024.
//

#include <stdexcept>

class MeshException : public std::runtime_error {
public:
    MeshException(const std::string& message) : std::runtime_error(message) {}
};


#endif //SCULPTPATH_MESHEXCEPTION_H
