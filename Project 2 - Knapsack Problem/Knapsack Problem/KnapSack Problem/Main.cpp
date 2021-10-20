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


//Checks if input file exists
bool inputFileExists(ifstream &inputFile) {
	if (inputFile.fail()) {
		return false;
	}
	else {
		return true;
	}
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
void trunkGeneration() {

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
		if (inputFileExists(genes)) {
			cout << "\n Reading file: " << inputFileName << endl;
		}
		else {
			cout << "Error! File " << inputFileName << " not found.\n";
			cout << "Please check syntax and try again.\n\n";
			inputFileName.clear();
		}
	} while (!inputFileExists(genes));
	fullItemList = itemListGeneration(genes);
	for (int x = 0; x < 4; x++) {
		maxPop = popSizes[x];

	}

	return 0;
}
