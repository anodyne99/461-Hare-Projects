#pragma once
#include "Main.h"

class Item
{
private:
	double ItemUtilityValue;
	double weight;
	bool packed = false;
public:
	Item(double itemWeight, double utility);
	double getItemWeight() {
		return this->weight;
	}
	double getItemUtility() {
		return this->ItemUtilityValue;
	}
	bool getPacked() {
		return this->packed;
	}
	void setMutation() {
		if (getPacked()) {
			this->packed = false;
		}
		else {
			this->packed = true;
		}
	}
};