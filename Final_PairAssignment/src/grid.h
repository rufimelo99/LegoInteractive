#pragma once

#include "vector3d.h"

class Grid {
public:
	Grid();
	Grid(Vectors::vector3D sizeUnit, int nbUnitX, int nbUnitY, int nbUnitZ);

	//~Grid();

	void drawGrid();

	void setOccupied(Vectors::vector3D pos);

	void setNonOccupied(Vectors::vector3D pos);

	bool getOccupied(Vectors::vector3D pos);


	Vectors::vector3D sizeUnit;

public:
	int nbUnitX, nbUnitY, nbUnitZ;
	int occupiedUnits[36][10][36] = { 0 };

	void printOccupiedUnits();
};


