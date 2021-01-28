#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "lego.h"
class Lego;//important line, so Lego can call LegoGroup and vice-versa Ass.Rui.. dont delete pls 
class LegoGroup {
private:
	std::map<std::string, Lego*> groupMap ; 

public:
	LegoGroup();

	void addLego(Lego* lego);

	void removeLego(Lego* lego);

	void mergeGroups(LegoGroup* legoGroup);

	std::map<std::string, Lego*> getGroupMap();

	int getGroupSize();

	void removeAllLegosFromGroup();
};