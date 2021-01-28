#include "mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

///////////////////////////////////////////////// ERROR HANDLING (All versions)

static const std::string errorString(GLenum error)
{
	switch(error) {
	case GL_NO_ERROR:
		return "No error has been recorded.";
	case GL_INVALID_ENUM:
		return "An unacceptable value is specified for an enumerated argument.";
	case GL_INVALID_VALUE:
		return "A numeric argument is out of range.";
	case GL_INVALID_OPERATION:
		return "The specified operation is not allowed in the current state.";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "The framebuffer object is not complete.";
	case GL_OUT_OF_MEMORY:
		return "There is not enough memory left to execute the command.";
	case GL_STACK_UNDERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
	case GL_STACK_OVERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
	default: exit(EXIT_FAILURE);
	}
}

static bool isOpenGLError() 
{
	bool isError = false;
	GLenum errCode;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		std::cerr << "OpenGL ERROR [" << errorString(errCode) << "]." << std::endl;
	}
	return isError;
}

static void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

mesh::mesh(){}

mesh::mesh(std::string& meshPath){
    createMesh(meshPath);
    createBufferObjects();
}

mesh::~mesh(){
    destroyBufferObjects();
}
void mesh::draw(){//ShaderManager& shaderManager){
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mVertices.size());
    checkOpenGLError("MESH DRAW");
}

void mesh::parsePosition(std::stringstream& sin){
    vector3D v;
	sin >> v.x >> v.y >> v.z;
	vertexData.push_back(v);
}

void mesh::parseTexcoord(std::stringstream& sin){
	vector2D t;
	sin >> t.x >> t.y;
	texCoordData.push_back(t);
}

void mesh::parseNormal(std::stringstream& sin){
	vector3D n;
	sin >> n.x >> n.y >> n.z;
	normalData.push_back(n);
}

void mesh::parseFace(std::stringstream& sin){
	std::string token;
	if (normalData.empty() && texCoordData.empty())
	{
		for (int i = 0; i < 3; i++)
		{
			sin >> token;
			vertexIdx.push_back(std::stoi(token));
		}
	} 
	else 
	{
		for (int i = 0; i < 3; i++) 
		{
			std::getline(sin, token, '/');
			if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
			std::getline(sin, token, '/');
			if (token.size() > 0) texCoordIdx.push_back(std::stoi(token));
			std::getline(sin, token, ' ');
			if (token.size() > 0) normalIdx.push_back(std::stoi(token));
		}
	}
}

void mesh::parseLine(std::stringstream& sin){
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parsePosition(sin);
	else if (s.compare("vt") == 0) parseTexcoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);
}

void mesh::loadMeshData(std::string& filename){
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line)) 
	{
		std::stringstream sline(line);
		parseLine(sline);
	}
    mPositionsLoaded = (vertexIdx.size() > 0);
	mTexCoordsLoaded = (texCoordIdx.size() > 0);
	mNormalsLoaded = (normalIdx.size() > 0);
}

void mesh::processMeshData(){
	for (unsigned int i = 0; i < vertexIdx.size(); i++) {
		unsigned int vi = vertexIdx[i];
		vector3D v = vertexData[vi - 1];
		mVertices.push_back(v);
		if (mTexCoordsLoaded) 
		{
			unsigned int ti = texCoordIdx[i];
			vector2D t = texCoordData[ti - 1];
			mTexCoords.push_back(t);
		}
		if (mNormalsLoaded) 
		{
			unsigned int ni = normalIdx[i];
			vector3D n = normalData[ni - 1];
			mNormals.push_back(n);
		}
	}
}

void mesh::freeMeshData(){
	vertexData.clear();
	texCoordData.clear();
	normalData.clear();
	vertexIdx.clear();
	texCoordIdx.clear();
	normalIdx.clear();
}

const void mesh::createMesh(std::string& filename){
	loadMeshData(filename);
	processMeshData();
	freeMeshData();
}

void mesh::createBufferObjects(){
	//GLuint VboVertices, VboTexcoords, VboNormals;

	glGenVertexArrays(1, &mVaoId);
	glBindVertexArray(mVaoId);
	{
		glGenBuffers(1, &mVboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float) * 3.0, &mVertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3.0, 0);

		if (mTexCoordsLoaded)
		{
			glGenBuffers(1, &mVboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, mVboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, mTexCoords.size() * sizeof(float) * 2.0, &mTexCoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2.0, 0);
		}
		if (mNormalsLoaded)
		{
			glGenBuffers(1, &mVboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
			glBufferData(GL_ARRAY_BUFFER, mNormals.size() * sizeof(float) * 3.0, &mNormals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3.0, 0);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &mVboVertices);
	glDeleteBuffers(1, &mVboTexcoords);
	glDeleteBuffers(1, &mVboNormals);
}

void mesh::destroyBufferObjects(){
	glBindVertexArray(mVaoId);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(TEXCOORDS);
	glDisableVertexAttribArray(NORMALS);
	glDeleteVertexArrays(1, &mVaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
