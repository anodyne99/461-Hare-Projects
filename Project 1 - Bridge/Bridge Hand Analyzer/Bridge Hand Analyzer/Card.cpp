#include "Card.h"

Card::Card() {
	faceValue = NULL;
	suit = NULL;
	cardNumber = NULL;
}

Card::Card(int numberInDeck) {
	faceValue = 0;
	suit = int(floor(numberInDeck / 13));
	cardNumber = numberInDeck - (suit * 13);
	setCardValue(cardNumber);
}

void Card::setCardValue(int cardNumber) {
	switch (cardNumber) {
	case 0: {
		faceValue = 4;
		break;
	}
	case 12: {
		faceValue = 3;
		break;
	}
	case 11: {
		faceValue = 2;
		break;
	}
	case 10: {
		faceValue = 1;
		break;
	}
	default: faceValue = 0;
	}
}
