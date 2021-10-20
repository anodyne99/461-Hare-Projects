#include "Item.h"

Item::Item(double itemWeight, double utility) {
	ItemUtilityValue = utility;
	weight = itemWeight;
}

void Item::setMutation() {
	if (getPacked()) {
		this->packed = false;
	}
	else {
		this->packed = true;
	}
}

void Item::setPacked() {
	this->packed = true;
}
