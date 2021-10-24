// James Helm
// Fall 2021
// Project 2 - Knapsack Problem

#include "Main.h"
#include "Trunk.h"
#include "Norms.h"


int maxPop;
int genTally;
string inputFileName = "";
double prevGenAvgFitness = 0.0;
double currentGenAvgFitness;
double tenAgoFitness = 0.0;
double fitnessChangeOverTenGens = 0.0;
bool changeFlag = false;
ifstream genes;
ofstream results ("results.txt");
deque<Item> fullItemList;
deque<Trunk> trunkList;

// Checks to make sure at least 1% change is happening each ten generations
bool changeChecker(double tenAgoFitness, double fitChange) {
	double onePercentChange = (abs(tenAgoFitness / 100));
	if (fitChange < onePercentChange) {
		return true;
	}
	else {
		return false;
	}
}

// Calculates fitness change each generation over ten generations
void fitnessChange(double currentGenFitness, double prevGenFitness) {
	double changeOverGeneration = (currentGenAvgFitness - prevGenFitness);
	fitnessChangeOverTenGens += changeOverGeneration;
}

// Handles the off chance process of mutation
void mutationHandler(Trunk &a, Trunk &b) {
	deque<Item> itemsA = a.getItemsPacked();
	deque<Item> itemsB = b.getItemsPacked();
	int randIndex = (rand() % 400);
	int coinFlip = (rand() % 2);
	if (coinFlip == 0) {
		itemsA[randIndex].setMutation();
		a.setItemsPacked(itemsA);
		a.setFitness();
	}
	else {
		itemsB[randIndex].setMutation();
		b.setItemsPacked(itemsB);
		b.setFitness();
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
	if ((rand() % 10000) == 4) {
		cout << "Mutation triggered!\n";
		mutationHandler(a, b);
	}
	a.setFitness();
	b.setFitness();
	nextGen.push_back(a);
	nextGen.push_back(b);
	
}


// Calculates the average fitness for the generation
double averageFitnessCalculation(deque<Trunk> generated) {
	int size = generated.size();
	double totalTally = 0.0;
	for (int i = 0; i < size; i++) {
		totalTally += generated[i].getFitness();
	}
	return (totalTally / size);
}


// Finds the maximum fitness in a generation
double findMaxFitness(deque<Trunk> list) {
	double max = 0.0;
	for (int i = 0; i < list.size(); i++) {
		if (list[i].getFitness() > max) {
			max = list[i].getFitness();
		}
	}
	return max;
}


// L2 Normalization functionality
deque<Norms> normalization(deque<Trunk> thisGeneration) {
	deque<Norms> distributedNorms;
	int size = thisGeneration.size(); // Removes overhead of constant size calls;
	double squaredSum = 0;
	for (int i = 0; i < 20; i++) {
		int mult = ((i + 1) * 50);
		Norms newNorm;
		newNorm.setRange(mult);
		distributedNorms.push_back(newNorm);
	}
	for (int i = 0; i < size; i++) {
		double fitness = thisGeneration.at(i).getFitness();
		// Most verbose but best readability
		if (fitness < 50) {
			distributedNorms[0].incrementTally();
		}
		else if (fitness < 100) {
			distributedNorms[1].incrementTally();
		}
		else if (fitness < 150) {
			distributedNorms[2].incrementTally();
		}
		else if (fitness < 200) {
			distributedNorms[3].incrementTally();
		}
		else if (fitness < 250) {
			distributedNorms[4].incrementTally();
		}
		else if (fitness < 300) {
			distributedNorms[5].incrementTally();
		}
		else if (fitness < 350) {
			distributedNorms[6].incrementTally();
		}
		else if (fitness < 400) {
			distributedNorms[7].incrementTally();
		}
		else if (fitness < 450) {
			distributedNorms[8].incrementTally();
		}
		else if (fitness < 500) {
			distributedNorms[9].incrementTally();
		}
		else if (fitness < 550) {
			distributedNorms[10].incrementTally();
		}
		else if (fitness < 600) {
			distributedNorms[11].incrementTally();
		}
		else if (fitness < 650) {
			distributedNorms[12].incrementTally();
		}
		else if (fitness < 700) {
			distributedNorms[13].incrementTally();
		}
		else if (fitness < 750) {
			distributedNorms[14].incrementTally();
		}
		else if (fitness < 800) {
			distributedNorms[15].incrementTally();
		}
		else if (fitness < 850) {
			distributedNorms[16].incrementTally();
		}
		else if (fitness < 900) {
			distributedNorms[17].incrementTally();
		}
		else if (fitness < 950) {
			distributedNorms[18].incrementTally();
		}
		else if (fitness < 1000) {
			distributedNorms[19].incrementTally();
		}
	}
	for (unsigned int i = 0; i < 20; i++) {
		distributedNorms[i].squaredTally();
		squaredSum += distributedNorms[i].getTally();
	}
	for (unsigned int i = 0; i < 20; i++) {
		double tally = distributedNorms[i].getTally();
		distributedNorms[i].setWeight(tally / squaredSum);
	}
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

// Picks the trunks that match the range for breeding
Trunk pickTrunk(deque<Trunk> list, int max, int min) {
	int size = list.size();
	while (true) {
		int randomIndex = (rand() % size);
		if (list[randomIndex].getFitness() < max && list[randomIndex].getFitness() > min) {
			return list[randomIndex];
		}
	}
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
	double selected;
	while (nextGeneration.size() < pop) {
		srand(unsigned(time(0)));
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
		// random_shuffle(thisGeneration.begin(), thisGeneration.end());
		b = pickTrunk(thisGeneration, distribution[maxValueB].second, lowerBoundB);
		crossover(a, b, nextGeneration);
		cout << "Currently generated: " << nextGeneration.size() << "/1000 \n";
	}
	return nextGeneration;
}

//Function to output generation results to a results file.
void resultsOutputToFile(ofstream &output, double max, double avg, int generation) {
	results << "Generation " << generation << " results: \n";
	results << "Average fitness: " << avg << endl;
	results << "Maximum fitness: " << max << endl;
	results << endl;
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
	cout << "Read complete!\n";
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
	maxPop = 1000;
	for (int i = 0; i < maxPop; i++) {
		Trunk generatedTrunk;
		generatedTrunk.setItemsPacked(initialPopulation(fullItemList));
		generatedTrunk.setFitness();
		trunkList.push_back(generatedTrunk);
	}
	int runningPopulationTally = 1;
	cout << "This will take a bit. Go grab a coffee or something.\n";
	cin.get(); // Little pause for readability
	while (!changeFlag) {
		double maxFitness;
		srand(unsigned(time(0))); //Random seeding changes with each trial
		currentGenAvgFitness = averageFitnessCalculation(trunkList);
		cout << "Current generation average fitness: " << currentGenAvgFitness << endl;
		maxFitness = findMaxFitness(trunkList);
		fitnessChange(currentGenAvgFitness, prevGenAvgFitness);
		prevGenAvgFitness = currentGenAvgFitness;
		trunkList = breedingSelection(trunkList);
		cout << "Generation " << runningPopulationTally << " breeding done!\n";
		genTally++;
		if (genTally == 10) {
			changeFlag = changeChecker(tenAgoFitness, fitnessChangeOverTenGens);
			genTally = 0;
			tenAgoFitness = currentGenAvgFitness;
			fitnessChangeOverTenGens = 0.0;
		}
		resultsOutputToFile(results, maxFitness, currentGenAvgFitness, runningPopulationTally);
		runningPopulationTally++;
	}
	cout << "Outputting final results to results.txt\n";
	results.close();
	return 0;
}
