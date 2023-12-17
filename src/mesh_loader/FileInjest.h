//
// Created by simar on 12/16/2023.
//

#ifndef SCULPTPATH_FILEINJEST_H
#define SCULPTPATH_FILEINJEST_H

#include <string>

/**
 * This class will take in the input file and prepare it for the pipeline through cgal
 */

class FileInjest {

    std::string ogFilePath;
    std::string offFilePath;

public:

    bool ingest(std::string& filePath);

};


#endif //SCULPTPATH_FILEINJEST_H
