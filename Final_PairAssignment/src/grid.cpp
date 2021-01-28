#include "grid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
using namespace Vectors;

Grid::Grid() {
	sizeUnit = vector3D::vector3D(1.0, 1.0, 1.0);
	nbUnitX = 10;
	nbUnitY = 10;
	nbUnitZ = 10;
}

Grid::Grid(vector3D sizeUnit, int nbUnitX, int nbUnitY, int nbUnitZ) {
	this->sizeUnit = sizeUnit;
	this->nbUnitX = nbUnitX;
	this->nbUnitY = nbUnitY;
	this->nbUnitZ = nbUnitZ;
}

void Grid::drawGrid() {

}

void Grid::setOccupied(vector3D pos)
{
	int x = int(pos.x);
	int y = int(pos.y);
	int z = int(pos.z);
	occupiedUnits[x][y][z] = 1;
}

void Grid::setNonOccupied(vector3D pos)
{
	int x = int(pos.x);
	int y = int(pos.y);
	int z = int(pos.z);
	occupiedUnits[x][y][z] = 0;
}

bool Grid::getOccupied(vector3D pos)
{
	int x = int(pos.x);
	int y = int(pos.y);
	int z = int(pos.z);
	return occupiedUnits[x][y][z];
}

void Grid::printOccupiedUnits()
{
	for (int i = 0; i < nbUnitZ; i++)
	{
		std::string s;
		for (int j = 0; j < nbUnitX; j++)
		{
			s += " " + std::to_string(occupiedUnits[j][0][i]);
		}
	}
}
