// James Helm
// Fall 2021
// Project 2 - Knapsack Problem

#include "Main.h"
#include "Trunk.h"
#include "Norms.h"


int maxPop;
string inputFileName = "";
double prevGenAvgFitness = 0.0;
double currentGenAvgFitness;
double tenAgoFitness = 0.0;
double fitnessChangeOverTenGens = 0.0;
double maxFitness;
bool changeFlag = false;
double change;
ifstream genes;
ofstream results;
deque<Item> fullItemList;
deque<Trunk> trunkList;
float mutationRate = (1 / 10000);

bool changeChecker() {
	if (fitnessChangeOverTenGens < 1 && fitnessChangeOverTenGens > -1) {
		return true;
	}
}

// Handles crossover process
void crossover(Trunk a, Trunk b, deque<Trunk> &nextGen) {
	deque<Item> itemsA = a.getItemsPacked();
	deque<Item> itemsB = b.getItemsPacked();
	srand(time(0));
	int crossoverIndex = (rand() % 400);
	deque<Item> tempA, tempB; // Temp vectors for switching
	for (int i = 0; i < crossoverIndex; i++) {
		tempA.push_back(itemsA.at(i));
		tempB.push_back(itemsB.at(i));
	}
	for (int i = crossoverIndex; i < 400; i++) {
		tempA.push_back(itemsB.at(i));
		tempB.push_back(itemsA.at(i));
	}
	a.setItemsPacked(tempA);
	b.setItemsPacked(tempB);
	nextGen.push_back(a);
	nextGen.push_back(b);
	cout << "crossover done! \n";
}


// Calculates the average fitness for the generation
double averageFitnessCalculation(deque<Trunk> generated) {
	int size = generated.size();
	double totalTally = 0.0;
	for (int i = 0; i < size; i++) {
		totalTally += generated[i].getFitness();
	}
	cout << "Avg fit done \n";
	return (totalTally / size);
}


// L2 Normalization functionality
deque<Norms> normalization(deque<Trunk> thisGeneration) {
	deque<Norms> distributedNorms;
	int size = thisGeneration.size(); // Removes overhead of constant size calls;
	double squaredSum = 0;
	for (int i = 0; i <= 10; i++) {
		int mult = ((i + 1) * 100);
		Norms newNorm;
		newNorm.setRange(mult);
		distributedNorms.push_back(newNorm);
	}
	for (int i = 0; i < size; i++) {
		double fitness = thisGeneration.at(i).getFitness();
		// Most verbose but best readability and fastest runtime
		if (fitness < 100) {
			distributedNorms[0].incrementTally();
		}
		else if (fitness < 200) {
			distributedNorms[1].incrementTally();
		}
		else if (fitness < 300) {
			distributedNorms[2].incrementTally();
		}
		else if (fitness < 400) {
			distributedNorms[3].incrementTally();
		}
		else if (fitness < 500) {
			distributedNorms[4].incrementTally();
		}
		else if (fitness < 600) {
			distributedNorms[5].incrementTally();
		}
		else if (fitness < 700) {
			distributedNorms[6].incrementTally();
		}
		else if (fitness < 800) {
			distributedNorms[7].incrementTally();
		}
		else if (fitness < 900) {
			distributedNorms[8].incrementTally();
		}
		else if (fitness < 1000) {
			distributedNorms[9].incrementTally();
		}
	}
	for (unsigned int i = 0; i < 10; i++) {
		distributedNorms[i].squaredTally();
		squaredSum += distributedNorms[i].getTally();
	}
	for (unsigned int i = 0; i < 10; i++) {
		double tally = distributedNorms[i].getTally();
		distributedNorms[i].setWeight(tally / squaredSum);
	}
	cout << "Distribution done! \n";
	return distributedNorms;
}


// Finds where in the distribution the value selected is
int findMaxValue(deque<pair<double, int>> dist) {
	double runningCounter = dist[0].first;
	srand(time(0));
	double selected = ((double)rand() / (double)RAND_MAX); // Random float between 1 and zero
	for (int j = 0; j < dist.size(); j++) {
		if (selected > runningCounter) {
			int tempIndex = j + 1;
			runningCounter = (dist[tempIndex].first);
		}
		else {
			return (j);
		}
	}
}

Trunk pickTrunk(deque<Trunk> list, int max, int min) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i].getFitness() < max && list[i].getFitness() > min) {
			return list[i];
		}
	}
	cout << "Picktrunk done \n";
}


//Breeding process
deque<Trunk> breedingSelection(deque<Trunk> thisGeneration) {
	static const int pop = thisGeneration.size(); // Remove overhead of frequent size calls for loop
	deque<Trunk> nextGeneration;
	deque<Norms> normalizedTally = normalization(thisGeneration);
	deque<pair<double, int>> distribution;
	int maxValueA, maxValueB;
	Trunk a, b;
	double runningCounter;
	for (int i = 0; i < normalizedTally.size(); i++){
		if (normalizedTally[i].getTally() != 0) {
			distribution.push_back(make_pair(normalizedTally[i].getWeight(), normalizedTally[i].getRange()));
		}
	}
	// cycles through to create the full cdf values
	for (int i = 1; i < distribution.size(); i++) {
		int prev = (i - 1);
		distribution[i].first += distribution[prev].first;
	}
	cout << "cdf done! \n";
	double selected;
	while (nextGeneration.size() < pop) {
		srand(time(0));
		maxValueA = findMaxValue(distribution);
		maxValueB = findMaxValue(distribution);
		int lowerBoundA = 0;
		int lowerBoundB = 0;
		
		if (maxValueA != 0) { // < 0 error handling
			int prev = (maxValueA - 1);
			lowerBoundA = distribution[(prev)].second;
		}
		if (maxValueB != 0) { // < 0 error handling
			int prev = (maxValueB - 1);
			lowerBoundB = distribution[(prev)].second;
		}
		a = pickTrunk(thisGeneration, distribution[maxValueA].second, lowerBoundA);
		random_shuffle(thisGeneration.begin(), thisGeneration.end());
		b = pickTrunk(thisGeneration, distribution[maxValueB].second, lowerBoundB);
		crossover(a, b, nextGeneration);
		cout << "Currently generated: " << nextGeneration.size() << "/1000 \n";
	}
	return nextGeneration;
}


//Function to output generation results to a results file.
void resultsOutputToFile(ofstream &output, double max, double avg, int size) {

}


//initial population creation for each test
deque<Item> initialPopulation(deque<Item> items) {
	int successfulPack = 0; // to help with the occasional attempt to double-pack an item
	int randomIndex;
	while (successfulPack != 40) {
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
	cout << "Item list generation done \n";
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
	cout << "Initial item population done! \n";
	cout << "Enter the desired initial population size: \n";
	maxPop = 100;
	for (int i = 0; i < maxPop; i++) {
		Trunk generatedTrunk;
		generatedTrunk.setItemsPacked(initialPopulation(fullItemList));
		generatedTrunk.setFitness();
		trunkList.push_back(generatedTrunk);
	}
	cout << "Population creation done! \n";
	while (!changeFlag) {
		srand(unsigned(time(0))); //Random seeding changes with each trial
		currentGenAvgFitness = averageFitnessCalculation(trunkList);
		cout << "Current generation average fitness: " << currentGenAvgFitness << endl;
		trunkList = breedingSelection(trunkList);
		cout << "Next gen population done! \n";
	}
	return 0;
}
