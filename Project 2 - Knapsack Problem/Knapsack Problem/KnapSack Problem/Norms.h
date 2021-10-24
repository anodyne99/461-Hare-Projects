#pragma once

class Norms
{
private:
	int tally = 0;
	int range = 0;
	double weight = 0.0;
public:
	void incrementTally() {
		tally++;
	}
	void squaredTally() {
		tally = (tally * tally);
	}
	void setRange(int increment) {
		range = increment;
	}
	void setWeight(double wt) {
		weight = wt;
	}
	int getRange() {
		return this->range;
	}
	int getTally() {
		return this->tally;
	}
	double getWeight() {
		return this->weight;
	}
};

