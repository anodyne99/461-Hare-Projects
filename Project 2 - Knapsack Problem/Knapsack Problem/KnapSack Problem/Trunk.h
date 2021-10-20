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
public:
	Trunk(deque<Item> items);
	void overWeightCheck();
	deque<Item> getItemsPacked(){
		return this->itemsPacked;
	}
	void setItemsPacked(deque<Item> items) {
		items = itemsPacked;
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

