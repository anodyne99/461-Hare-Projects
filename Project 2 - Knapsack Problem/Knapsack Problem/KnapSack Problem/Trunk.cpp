#include "Trunk.h"

Trunk::Trunk() {
	deque<Item> itemsPacked = {};
	double fitness = 0.0;
	double totalWeight = 0.0;
}

void Trunk::setFitness() {
	deque<Item> items = this->itemsPacked;
	double totalFitness = 0;
	for (int i = 0; i < items.size(); i++) {
		if (items[i].getPacked()) {
			totalFitness += items.at(i).getItemUtility();
		}
	}
	this->fitness = totalFitness;
};

void Trunk::setWeight() {
	double totWeight = 0.0;
	deque<Item> items = this->itemsPacked;
	for (int i = 0; i < items.size(); i++) {
		if (items[i].getPacked()) {
			totWeight += items.at(i).getItemWeight();
		}
	}
	this->totalWeight = totWeight;
};

void Trunk::overWeightCheck() {
	if (this->getWeight() > 500) {
		this->fitness = 1;
	}
}
