#ifndef __MESH_H__
#define __MESH_H__

#include "vectors.h"

#include <vector>
#include "shader.h"

using namespace Vectors;

class mesh{
    public:
        bool mPositionsLoaded;
        bool mNormalsLoaded;
        bool mTexCoordsLoaded;
        unsigned int mVaoId, mVboVertices, mVboTexcoords, mVboNormals;

    private:
        std::vector <vector3D> mVertices, vertexData;
        std::vector <vector2D> mTexCoords, texCoordData;
        std::vector <vector3D> mNormals, normalData;
        std::vector <unsigned int> vertexIdx, texCoordIdx, normalIdx;


    public:
        mesh();         //for debug in MeshTest.cpp
        mesh(std::string& meshPath);
        ~mesh();
        void draw();
    
    private:
        void parsePosition(std::stringstream& sin);
        void parseTexcoord(std::stringstream& sin);
        void parseNormal(std::stringstream& sin);
        void parseFace(std::stringstream& sin);
        void parseLine(std::stringstream& sin);
        void loadMeshData(std::string& filename);
        void processMeshData();
        void freeMeshData();
        const void createMesh(std::string& filename);
        void createBufferObjects();
        void destroyBufferObjects();

}; 

#endif