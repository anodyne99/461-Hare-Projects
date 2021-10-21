#pragma once
#include <deque>
#include "Item.h"
#include "Main.h"

class Trunk
{
private:
	double fitness;
	deque<Item> itemsPacked;
	double totalWeight;
public:
	Trunk();
	bool operator < (const Trunk& trunkObj) const {
		return (fitness < trunkObj.fitness);
	}
	void overWeightCheck();
	deque<Item> getItemsPacked(){
		return this->itemsPacked;
	}
	void setItemsPacked(deque<Item> items) {
		itemsPacked = items;
	}
	void setWeight(deque<Item> items);
	double getWeight() {
		return this->totalWeight;
	}
	void setFitness();
	double getFitness() {
		return this->fitness;
	}
};

