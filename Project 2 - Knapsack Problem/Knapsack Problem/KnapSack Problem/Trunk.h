#pragma once
#include <deque>
#include "Item.h"
#include "Main.h"

class Trunk
{
private:
	deque<Item> itemsPacked;
	double fitness;
	double totalWeight;
	bool valid = false;
public:
	void overWeightCheck();
	deque<Item> getItemsPacked(){
		return this->itemsPacked;
	}
	void setItemsPacked(deque<Item> items) {
		items = itemsPacked;
	}
	void setValidFlag() {
		this->valid = true;
	}
	void setWeight(deque<Item> items);
	double getWeight() {
		return this->totalWeight;
	}
	void setFitness(deque<Item> items);
	double getFitness() {
		return this->fitness;
	}
};

