#pragma once

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "mesh.h"
#include "scenegraph.h"
#include "grid.h"
#include "shader.h"
#include "vector3d.h"
#include "legoGroup.h"

class LegoGroup;//important line, so Lego can call LegoGroup and vice-versa Ass.Rui.. dont delete pls 
class Lego {
private:
	std::string name;
	mesh* legoMesh;
	std::string meshPath;
	Grid* grid;
	Vectors::vector3D gridPos;
	Vectors::vector3D gridSize;

	vector4D color;
	colorCallback* color_Callback;
	vector4D HighLightColor;
	colorCallback* highLightColor_Callback;
	bool isHighLight;

	sceneNode* legoNode;
	sceneNode* parent;
	sceneNode* child;
	ShaderManager* shaderManager;
	//grouping
	LegoGroup* associatedGroup;

	int nbUnit;

public:
	Lego() = default;

	Lego(std::string name, Grid* grid, Vectors::vector3D gridPos, std::string meshPath, vector4D color, ShaderManager* shader, sceneNode* parent);

	bool moove(Vectors::vector3D pos);

	bool turn();

	void setParent(sceneNode* parent);

	void addChild(sceneNode* child);

	void removeChild(sceneNode* child);

	void setNode(sceneNode* node);

	void setPosition(Vectors::vector3D pos);

	void setAssociatedGroup(LegoGroup* legoGroup);

	sceneNode* getNode();

	vector3D getPosition();

	vector3D getGridSize();

	sceneNode* getParent();

	sceneNode* getChild();

	std::string getName();

	vector4D getColor();

	std::string getMeshPath();

	void addInGroup(Lego* lego);

	void removeInGroup();

	std::list<vector3D> occupiedUnits(vector3D occ);

	bool checkMoove(Vectors::vector3D pos);

	void associate2Groups(LegoGroup* associatedGroup2);

	void associateNewGroup(Lego* lego);

	void removeGroup();

	void deleteGroupPointer(); //destructor personalized

	void highLight();
};
