#include "Hand.h"


Hand::Hand(){
	handValue = 0;
}

void Hand::dealToHand(Deck& deck) {
	for (unsigned int i = 0; i < 13; i++) {
		this->cardsInHand.push_back(deck.getCard(i));
		deck.removeFromPlay();
	}
}

void Hand::setFaceValuePoints() {
	for (unsigned int i = 0; i < 13; i++) {
		handValue += this->cardsInHand[i].getCardValue();
	}
}

void Hand::setDoubletonPoints() {
	for (unsigned int i = 0; i < 4; i++) {
		unsigned int count = 0;
		for (unsigned int j = 0; j < 13; j++) {
			if (this->cardsInHand[j].getCardSuit() == i) {
				count++;
			}
		}
		if (count == 2) {
			handValue++;
		}
	}
}

void Hand::setHandValue() {
	this->setFaceValuePoints();
	this->setDoubletonPoints();
}
