#pragma once
#include "Main.h"

class Card
{
private:
	int suit;
	int faceValue;
	int cardNumber;
public:
	Card();
	Card(int cardNumber);
	void setCardValue(int cardNumber);
	int getCardValue() {
		return faceValue;
	}
	int getCardNumber() {
		return cardNumber;
	}
	int getCardSuit() {
		return suit;
	}
};

