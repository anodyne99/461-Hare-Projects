// James Helm
// Fall 2021
// Project 2 - Knapsack Problem

#include "Main.h"
#include "Trunk.h"
#include "Norms.h"


int popSizes[4] = { 1000, 2000, 5000, 10000 };
int maxPop;
int noChangeCounter = 0;
string inputFileName = "";
double prevGenAvgFitness, currentGenAvgFitness;
double maxFitness;
ifstream genes;
ofstream results;
deque<Item> fullItemList;
deque<Trunk> trunkList;
float mutationRate = (1 / 10000);


// Handles crossover process
void crossover(Trunk a, Trunk b) {

}


// L2 Normalization functionality
deque<Norms> normalization(deque<Trunk> thisGeneration) {
	deque<Norms> distributedNorms;
	int size = thisGeneration.size(); // Removes overhead of constant size calls;
	double squaredSum = 0;
	for (unsigned int i = 0; i <= 1000; (i + 100)) {
		Norms newNorm;
		newNorm.setRange(i);
		distributedNorms.push_back(newNorm);
	}
	for (unsigned int i = 0; i < size; i++) {
		double fitness = thisGeneration.at(i).getFitness(); // Most verbose but fasted run time
		if (fitness < 100) {
			distributedNorms[0].incrementTally();
		}
		if (fitness < 200) {
			distributedNorms[1].incrementTally();
		}
		if (fitness < 300) {
			distributedNorms[2].incrementTally();
		}
		if (fitness < 400) {
			distributedNorms[3].incrementTally();
		}
		if (fitness < 500) {
			distributedNorms[4].incrementTally();
		}
		if (fitness < 600) {
			distributedNorms[5].incrementTally();
		}
		if (fitness < 700) {
			distributedNorms[6].incrementTally();
		}
		if (fitness < 800) {
			distributedNorms[7].incrementTally();
		}
		if (fitness < 900) {
			distributedNorms[8].incrementTally();
		}
		if (fitness < 1000) {
			distributedNorms[9].incrementTally();
		}
	}
	return distributedNorms;
}


//Breeding selection
deque<Trunk> breedingSelection(deque<Trunk> thisGeneration) {
	static const int pop = thisGeneration.size(); // Remove overhead of frequent size calls for loop
	deque<Trunk> nextGeneration;
	deque<Norms> normalizedTally = normalization(thisGeneration);
	while (nextGeneration.size() < pop) {

	}
	return nextGeneration;
}


//Function to output 4 generation results to a results file.
void resultsOutputToFile(ofstream &output, double max, double avg, int size) {

}


//Checker function to see if end loop conditions are being met
//Should stop generating once the last 10 generations' average fitness
//doesn't increase more than 1 percent
void noChangeChecker(double prev, double curr) {
	if (abs((curr - prev) / prev) < .01) {
		noChangeCounter++;
	}
	else {
		noChangeCounter = 0;
	}
}


//initial population creation for each test
deque<Item> initialPopulation(deque<Item> items) {
	int successfulPack = 0; // to help with the occasional attempt to double-pack an item
	int randomIndex;
	while (successfulPack != 20) {
		randomIndex = (rand() % 400);
		if (!items[randomIndex].getPacked()) {
			items[randomIndex].setPacked();
			successfulPack++;
		}
	}
	return items;
}


// initially creates the full item list from input txt
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


int main() {
	do {
		cout << "Enter file name for input data for initial generation: \n";
		cin >> inputFileName;
		genes.open(inputFileName);
		if (genes.fail()) {
			cout << "Error! File " << inputFileName << " not found.\n";
			cout << "Please check syntax and try again.\n\n";
			inputFileName.clear();
		}
		else {
			cout << "\n Reading file: " << inputFileName << endl;
		}
	} while (genes.fail());
	fullItemList = itemListGeneration(genes);
	//Wasn't required but I felt like adding multiple trials.
	for (int x = 0; x < 4; x++) {
		srand(unsigned(time(0))); //Random seeding changes with each trial
		maxPop = popSizes[x];
		for (int i = 0; i < maxPop; i++) {
			// TODO: See if you can't find a way to encapsulate this into the population function
			Trunk generatedTrunk;
			generatedTrunk.setItemsPacked(initialPopulation(fullItemList));
			generatedTrunk.setFitness();
			trunkList.push_back(generatedTrunk);
		}
		breedingSelection(trunkList);
		while (noChangeCounter < 10) {
			trunkList.clear();
		}

	}
	return 0;
}
