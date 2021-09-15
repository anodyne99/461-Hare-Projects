#pragma once
#include "Main.h"
#include "Deck.h"
#include "Card.h"

class Hand {
private:
	vector<Card> cardsInHand;
	int handValue;
public:
	Hand();
	void dealToHand(Deck& deck);
	void setFaceValuePoints();
	void setTonPoints();
	void setHandValue();
	void emptyHand();
	int getHandValue() {
		return handValue;
	}
	vector<Card> getCardsInHand() {
		return cardsInHand;
	}
};