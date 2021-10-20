#include "Trunk.h"

void Trunk::setFitness(deque<Item> items) {
	double totalFitness = 0;
	for (int i = 0; i < items.size(); i++) {
		totalFitness += items.at(i).getItemUtility();
	}
	this->fitness = totalFitness;
};

void Trunk::setWeight(deque<Item> items) {
	double totWeight = 0.0;
	for (int i = 0; i < items.size(); i++) {
		totWeight += items.at(i).getItemWeight();
	}
	this->totalWeight = totWeight;
};

void Trunk::overWeightCheck() {
	if (this->getWeight() > 500) {
		this->fitness = 1;
	}
}
