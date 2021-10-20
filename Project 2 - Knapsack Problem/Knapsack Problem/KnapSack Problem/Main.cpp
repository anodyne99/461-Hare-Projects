// James Helm
// Fall 2021
// Project 2 - Knapsack Problem

#include "Main.h"
#include "Trunk.h"


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


//Breeding selection
deque<Trunk> breedingSelection(int size) {
	deque<Trunk> nextGeneration;
	while (nextGeneration.size() < size) {

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
void initialPopulation(Trunk emptyTrunk) {
	for (unsigned int i = 0; i < 20; i++) {

	}
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
	for (unsigned int i = 0; i < 20; i++) {
		cout <<  fullItemList.at(i).getItemWeight() << " " << fullItemList.at(i).getItemUtility() << endl;
	}
	for (int x = 0; x < 4; x++) {
		srand(unsigned(time(0))); //Random seeding
		maxPop = popSizes[x];
		for (int i = 0; i < maxPop; i++) {
			Trunk generatedTrunk(fullItemList);
			initialPopulation(generatedTrunk);
			trunkList.push_back(generatedTrunk);
		}
	}
	return 0;
}
