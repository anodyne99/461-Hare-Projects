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
	void setDoubletonPoints();
	void setHandValue();
};