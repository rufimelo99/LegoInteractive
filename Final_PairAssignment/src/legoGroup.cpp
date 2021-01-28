#pragma once

#include "legoGroup.h"

LegoGroup::LegoGroup() {
	this->groupMap = {};
}

void LegoGroup::addLego(Lego* lego) {
	this->groupMap[lego->getName()] = lego;
	std::cout << "Adding a lego to the map: " << this->groupMap.size() << std::endl;
	lego->setAssociatedGroup(this);
} 

void LegoGroup::removeLego(Lego* lego) {
	if (getGroupSize() == 2) { //this LegoGroup will be having only one lego so we delete the group.
		removeAllLegosFromGroup();
		std::cout << "removed all legos from a group!" << std::endl;
		delete this;
	}
	else {
		this->groupMap.erase(lego->getName());
		lego->setAssociatedGroup(nullptr);
	}
}

void LegoGroup::mergeGroups(LegoGroup* legoGroup) {
	for (std::pair<std::string, Lego*> element : legoGroup->groupMap) {
		this->groupMap[element.second->getName()] = element.second;
		element.second->setAssociatedGroup(this);
	}
}

std::map<std::string, Lego*> LegoGroup::getGroupMap() {
	return this->groupMap;
};

int LegoGroup::getGroupSize() {
	return this->groupMap.size();
}

void LegoGroup::removeAllLegosFromGroup() {
	// desassociate the groups each lego independently
	for (std::pair<std::string, Lego*> element : this->groupMap) {
		element.second->setAssociatedGroup(nullptr);
	}
	//and then delete this groupMap with all the legos
	groupMap.clear();
}
