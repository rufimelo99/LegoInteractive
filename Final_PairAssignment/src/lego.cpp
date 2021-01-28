#include "lego.h"
using namespace Vectors;


Lego::Lego(std::string name, Grid* grid, vector3D gridPos, std::string meshPath, vector4D color, ShaderManager* shader, sceneNode* parent)
{
	this->name = name;
	this->meshPath = meshPath;
	this->legoMesh = new mesh(meshPath);

	this->grid = grid;
	this->gridPos = gridPos;

	this->color = color;
	this->color_Callback = new colorCallback(color);
	this->shaderManager = shader;

	this->HighLightColor = color + vector4D(0.25, 0.25, 0.25, 0);
	this->highLightColor_Callback = new colorCallback(this->HighLightColor);
	this->isHighLight = false;

	if (meshPath == "src\\lego22.obj")
	{
		this->gridSize = vector3D(2, 1, 2);
	}
	else if (meshPath == "src\\legoBrickOK.obj")
	{
		this->gridSize = vector3D(2, 1, 4);
	}
	else {
		std::cout << "bad meshPath " << std::endl;
		return;
	}
	this->nbUnit = this->gridSize.getX() * this->gridSize.getZ();

	// check the movement
	std::list<vector3D> newOcc = occupiedUnits(gridPos);
	for (vector3D unit : newOcc)
	{
		if (!checkMoove(unit)) {
			std::cout << "unit occupied : lego not created" << std::endl;
			return;
		}
	}

	sceneNode* lego = parent->createChild();
	lego->setCallback(color_Callback);
	lego->setShader(shader);
	lego->setMesh(legoMesh);

	this->legoNode = lego;
	this->child = nullptr;

	for (vector3D unit : newOcc)
	{
		grid->setOccupied(unit);
	}

	vector3D trans = vector3D(grid->sizeUnit.getX() * gridPos.getX(),
		grid->sizeUnit.getY() * gridPos.getY(),
		grid->sizeUnit.getZ() * gridPos.getZ());
	this->legoNode->setTranslation(trans);

}

void Lego::highLight()
{
	if (this->isHighLight)
	{
		this->legoNode->setCallback(this->color_Callback);
		this->isHighLight = false;
	}
	else
	{
		this->legoNode->setCallback(this->highLightColor_Callback);
		this->isHighLight = true;
	}
}

void Lego::deleteGroupPointer() {
	if (associatedGroup) {
		LegoGroup* temp = associatedGroup;
		associatedGroup->removeAllLegosFromGroup();
		delete temp;
		std::cout << "Group deleted for " << this->name << std::endl;
	} 
}

bool Lego::moove(vector3D pos)
{
	std::list<vector3D> listOldPos; // list of the old position to dissocupy

	// disoccupy the old positions
	std::list<vector3D> oldOcc = occupiedUnits(this->gridPos);
	for (vector3D unit : oldOcc)
	{
		listOldPos.push_back(unit);
		grid->setNonOccupied(unit);
	}

	// disoccupy the old positions in group
	if (associatedGroup) {
		for (std::pair<std::string, Lego*> element : associatedGroup->getGroupMap()) {
			Lego* lego = element.second;

			std::list<vector3D> oldOccG = occupiedUnits(lego->gridPos);
			for (vector3D unit : oldOccG)
			{
				lego->grid->setNonOccupied(unit);
				listOldPos.push_back(unit);
			}
		}
	}
	// check the movement-----------------------------------------
	std::list<vector3D> newOcc = occupiedUnits(pos);
	for (vector3D unit : newOcc)
	{
		if (!checkMoove(unit)) {
			// re-occupied the old units
			for (vector3D unitold : listOldPos)
			{
				grid->setOccupied(unitold);
			}
			//this->grid->printOccupiedUnits();
			return false;
		}
	}
	//check the transformation for the grouped legos
	if (associatedGroup) {
		for (std::pair<std::string, Lego*> element : associatedGroup->getGroupMap()) {
			Lego* lego = element.second;
			vector3D diff = this->gridPos - pos;
			vector3D newPos = lego->getPosition() - diff;

			std::list<vector3D> newOccG = occupiedUnits(newPos);
			for (vector3D unit : newOccG)
			{
				if (!checkMoove(unit)) {
					// re-occupied the old units
					for (vector3D unitold : listOldPos)
					{
						grid->setOccupied(unitold);
					}
					//this->grid->printOccupiedUnits();
					return false;
				}
			}
		}
	}
	// occupy the new positions and move the legos--------------------------------------
	//occupy and move the transformation for the grouped legos
	if (associatedGroup) {
		for (std::pair<std::string, Lego*> element : associatedGroup->getGroupMap()) {
			Lego* lego = element.second;
			// do the transformation
			vector3D diff = this->gridPos - pos;
			vector3D newPos = lego->getPosition() - diff;

			lego->gridPos = newPos;
			std::list<vector3D> newOccG = occupiedUnits(newPos);
			for (vector3D unit : newOccG)
			{
				grid->setOccupied(unit);
			}
			vector3D trans = vector3D(lego->grid->sizeUnit.getX() * lego->gridPos.getX(),
				lego->grid->sizeUnit.getY() * lego->gridPos.getY(),
				lego->grid->sizeUnit.getZ() * lego->gridPos.getZ());
			lego->legoNode->setTranslation(trans);
		}
	}
	// occupy and move the current lego
	this->gridPos = pos;
	for (vector3D unit : newOcc)
	{
		grid->setOccupied(unit);
	}
	vector3D trans = vector3D(grid->sizeUnit.getX() * gridPos.getX(),
		grid->sizeUnit.getY() * gridPos.getY(),
		grid->sizeUnit.getZ() * gridPos.getZ());
	this->legoNode->setTranslation(trans);
		


	return true;



};

bool Lego::turn()
{
	if (this->gridSize == vector3D(2, 1, 1))
	{
		this->legoNode->setRotation(quaternion(0.0, vector4D(0, 1, 0, 1)));

		this->gridSize = vector3D(1, 1, 2);

		return true;
	}
	else if (this->gridSize == vector3D(1, 1, 2))
	{
		//quaternion q = quaternion::add(this->legoNode->getRotation(), quaternion(90.0f, vector4D(0, 1, 0, 1)));
		this->legoNode->setRotation(quaternion(110.0f, vector4D(0, 1, 0, 1)));
		this->gridSize = vector3D(2, 1, 1);
		return true;
	}
	else
	{
		return false;
	}
}

void Lego::setParent(sceneNode* parent)
{
	this->parent = parent;
}

void Lego::addChild(sceneNode* child)
{
	this->child = child;
}

void Lego::removeChild(sceneNode* child)
{
	this->child = nullptr;
}

void Lego::setNode(sceneNode* node)
{
	this->legoNode = node;
}

void Lego::setPosition(Vectors::vector3D pos)
{
	this->gridPos = pos;
}

sceneNode* Lego::getNode()
{
	return this->legoNode;
}

vector3D Lego::getPosition() {
	return this->gridPos;
}

vector3D Lego::getGridSize() {
	return this->gridSize;
}

sceneNode* Lego::getParent()
{
	return this->parent;
}

sceneNode* Lego::getChild()
{
	return this->child;
}

std::string Lego::getName()
{
	return this->name;
}

vector4D Lego::getColor()
{
	return this->color;
}

std::string Lego::getMeshPath()
{
	return this->meshPath;
}


bool Lego::checkMoove(Vectors::vector3D pos)
{

	//check if pos is not already occupied in the grid
	if (pos.x >= grid->nbUnitX || pos.x < 0) {
		return false;
	}
	else if (pos.z >= grid->nbUnitZ || pos.z < 0) {
		return false;
	}
	else if (pos.y >= grid->nbUnitY || pos.y < 0) {
		return false;
	}
	else if (grid->getOccupied(pos) == 1) {
		//grid->printOccupiedUnits();
		return false;
	}
	else {
		return true;
	}
}

std::list<vector3D> Lego::occupiedUnits(vector3D pos)
// return the unit xhich are occupied by the lego at pos
{
	std::list<vector3D> occ;
	for (int i = 0; i < this->gridSize.getX(); i++)
	{
		for (int j = 0; j < this->gridSize.getZ(); j++)
		{
			occ.push_back(vector3D(pos.getX() + i, pos.getY(), pos.getZ() + j));
		}
	}
	return occ;
}

void Lego::removeInGroup()
{
	if (associatedGroup) {
		associatedGroup->removeLego(this);
		std::cout << "Ungrouped " << this->name << "!" << std::endl;
	}
	else {
		std::cout << "Tried to remove " << this->name << " from a non-existing group." << std::endl;
	}	
}

void Lego::addInGroup(Lego* lego)
{
	if (!associatedGroup && !lego->associatedGroup) {
		std::cout << "New group formed!" << std::endl;
		associateNewGroup(lego);
		//lego->setAssociatedGroup(this->associatedGroup);
	}
	else if (associatedGroup && lego->associatedGroup) {
		//setAssociatedGroup(lego->associatedGroup);
		//TODO pensar na logica de perguntar ao user o que quer fazer.
	}
	else if (!associatedGroup && lego->associatedGroup) {
		lego->associatedGroup->addLego(this);
	}
	else if (associatedGroup && !lego->associatedGroup) {
		//std::cout << "Associating the " << lego->name << " to the group of " << this->name<< std::endl;
		this->associatedGroup->addLego(lego);
	}
}

void Lego::setAssociatedGroup(LegoGroup* legoGroup) {
	this->associatedGroup = legoGroup;
}

void Lego::associate2Groups(LegoGroup* associatedGroup2) {
	this->associatedGroup->mergeGroups(associatedGroup2);
}

void Lego::associateNewGroup(Lego* lego) {
	LegoGroup* lg1 = new LegoGroup();
	//este lego criou um grupo 
	//this->associatedGroup = lg1;
	lg1->addLego(this);
	lg1->addLego(lego);
}

void Lego::removeGroup() {
	associatedGroup->removeLego(this);
	associatedGroup = NULL;
}