// James Helm
// Fall 2021
// Project 2 - Knapsack Problem

#include "Main.h"
#include "Trunk.h"


Trunk trunkGeneration() {

}


deque<Item> itemListGeneration(ifstream &inputStream) {
	double utility;
	double weight;
	deque<Item> itemList;
	while (inputStream >> utility >> weight) {
		Item generatedItem(utility, weight);
		itemList.push_back(generatedItem);
	}
	inputStream.close();
	return itemList;
}


int generations = 0;
double prevGenFitness, currentGenFitness;
ifstream genes;
deque<Item> fullItemList;
deque<Trunk> trunkList;


int main() {
	genes.open("Program2Input.txt");
	fullItemList = itemListGeneration(genes);
	do {

	} while ((currentGenFitness - prevGenFitness) < 1);
	for (int i = 0; i < 1000; i++);
	return 0;
}
