//
// Created by simar on 11/8/2023.
//

#include "MeshLoad.h"
#include <fstream>
#include <vector>
#include "OBJ_Loader.h"
#include <CGAL/convex_hull_3.h>

/**
 * Standard constructor that sets up the file path for mesh
 * @param filePath
 */
MeshLoad::MeshLoad(std::string filePath) {
    MeshLoad::filePath = filePath;
}

/**
 * Gets the mesh file format and returns enum of the type
 * @param check
 * @return
 */
FileType MeshLoad::getMeshFormat(bool check) {

    std::string extension;
    size_t dotPos = filePath.find_last_of('.');

    if (dotPos != std::string::npos){
        extension = filePath.substr(dotPos + 1);
    }

    if (std::equal(extension.begin(), extension.end(),"stl")){
        return STL;
    } else if (std::equal(extension.begin(), extension.end(),"obj")){
        return OBJ;
    }
    else{
        std::cerr << "Error processing file extension" << extension;
    }
    return OBJ;

}

//TODO remove the write to file debug thingamajig
/**
 * Loads the mesh into CGAL's standard polygon mesh stuff based on type
 */
void MeshLoad::loadMesh() {

    /**
     * Standard stl file loader
     */
    if (getMeshFormat(false) == STL) {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file " << filePath << std::endl;
            return;
        }

        file.ignore(80); // Ignores STL header 80 bytes

        unsigned int numTriangles;
        file.read(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

        for (unsigned int i = 0; i < numTriangles; ++i) {
            float normal[3], vertex[3][3];
            file.read(reinterpret_cast<char*>(normal), 3 * sizeof(float)); // normal is not used

            for (int j = 0; j < 3; ++j) {
                file.read(reinterpret_cast<char*>(vertex[j]), 3 * sizeof(float));
            }

            file.ignore(2); // Skipping the attribute byte count

            std::vector<Mesh::Vertex_index> face_vertices;
            for (int j = 0; j < 3; ++j) {
                face_vertices.push_back(mesh.add_vertex(Point(vertex[j][0], vertex[j][1], vertex[j][2])));
            }
            mesh.add_face(face_vertices);
        }

        if (file.fail()) {
            std::cerr << "Error reading file " << filePath << std::endl;
        }

        file.close();
    }
    /**
     * Standard file mesh loader for OBJ file format
     */
     //TODO not OBJ | fixme
    else if (getMeshFormat(false) == OBJ) {
        std::cerr << "Opening OBJ file " << filePath << std::endl;

            //TODO set up CGAL obj load

        /** Testing **/

            objl::Loader Loader;

            bool loadout = Loader.LoadFile(filePath);


        // If so continue
        if (loadout)
        {
            // Create/Open e1Out.txt


            // Go through each loaded mesh and out its contents
            for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
            {
                // Copy one of the loaded meshes to be our current mesh
                objl::Mesh curMesh = Loader.LoadedMeshes[i];

                // Print Mesh Name
                std::cout << "Mesh " << i << ": " << curMesh.MeshName << "\n";

                // Print Vertices
                std::cout << "Vertices:\n";

                // Go through each vertex and print it's number,
                //  position, normal, and texture coordinate

                //Have to add mesh using triangular face descriptor

                std::map<int, vertex_descriptor> vertex_map;

                for (int i = 0; i < curMesh.Vertices.size(); i++) {
                    vertex_descriptor v = m.add_vertex(K::Point_3(curMesh.Vertices[i].Position.X,
                                                                  curMesh.Vertices[i].Position.Y,
                                                                  curMesh.Vertices[i].Position.Z));
                    vertex_map[i] = v;
                }

                // Now, add faces using the indices
                for (int j = 0; j < curMesh.Indices.size(); j += 3) {
                    vertex_descriptor v0 = vertex_map[curMesh.Indices[j]];
                    vertex_descriptor v1 = vertex_map[curMesh.Indices[j + 1]];
                    vertex_descriptor v2 = vertex_map[curMesh.Indices[j + 2]];

                    m.add_face(v0, v1, v2);
                }

                for (int j = 0; j < curMesh.Vertices.size(); j++)
                {

                   // m.add_vertex(K::Point_3(curMesh.Vertices[j].Position.X , curMesh.Vertices[j].Position.Y,curMesh.Vertices[j].Position.Z));

                    std::cout << "V" << j << ": " <<
                         "P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
                         "N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
                         "TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
                }

                // Print Indices
                std::cout  << "Indices:\n";

                // Go through every 3rd index and print the
                //	triangle that these indices represent
                for (int j = 0; j < curMesh.Indices.size(); j += 3)
                {
                   // vertex_descriptor v0 = m.add_vertex(K::Point_3(curMesh.Vertices[j].Position.X , curMesh.Vertices[j].Position.Y,curMesh.Vertices[j].Position.Z));
                   // vertex_descriptor v1 = m.add_vertex(K::Point_3(curMesh.Vertices[j+1].Position.X , curMesh.Vertices[j+1].Position.Y,curMesh.Vertices[j+1].Position.Z));
                  //  vertex_descriptor v2 = m.add_vertex(K::Point_3(curMesh.Vertices[j+2].Position.X , curMesh.Vertices[j+2].Position.Y,curMesh.Vertices[j+2].Position.Z));


                }

                CGAL::convex_hull_3(m.points().begin(), m.points().end(), ch);

                // Print Material
                std::cout  << "Material: " << curMesh.MeshMaterial.name << "\n";
                std::cout  << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
                std::cout  << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
                std::cout  << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
                std::cout  << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
                std::cout  << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
                std::cout  << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
                std::cout  << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
                std::cout  << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
                std::cout  << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
                std::cout  << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
                std::cout  << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
                std::cout  << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

                // Leave a space to separate from the next mesh
                std::cout  << "\n";
            }

            // Close File
            //file.close();
        }
            // If not output an error
        else
        {
            // Create/Open e1Out.txt
            std::ofstream file("e1Out.txt");

            // Output Error
            file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

            // Close File
            file.close();
        }


        /** Testing **/

    } else {
        std::cerr << "Unsupported file format." << std::endl;
    }
}

const MeshLoad::Mesh &MeshLoad::getMesh() const {
    return m;
}

std::vector<double> MeshLoad::getMeshBounding() {

    std::vector<double> boundingVals;

    if (mesh.is_empty()){
        std::cerr << "Mesh i;s empty please load mesh before" << std::endl;
    }

    CGAL::Bbox_3 bbox = CGAL::bbox_3(mesh.points().begin(), mesh.points().end());

    boundingVals.push_back(bbox.xmin());
    boundingVals.push_back(bbox.ymin());
    boundingVals.push_back(bbox.zmin());
    boundingVals.push_back(bbox.xmax());
    boundingVals.push_back(bbox.ymax());
    boundingVals.push_back(bbox.zmax());

    x_min = bbox.xmin();
    x_max = bbox.xmax();
    y_min = bbox.ymin();
    y_max = bbox.ymax();
    z_max = bbox.zmax();

    return boundingVals;
}

double MeshLoad::getXMin() const {
    return x_min;
}

double MeshLoad::getXMax() const {
    return x_max;
}

double MeshLoad::getYMin() const {
    return y_min;
}

double MeshLoad::getYMax() const {
    return y_max;
}

double MeshLoad::getZMax() const {
    return z_max;
}

