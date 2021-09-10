#pragma once
#include "Main.h"
#include "Card.h"


class Deck {
public:
	Deck();
	Deck(deque<Card> updatedDeck);
	deque<Card> cardsInPlay;
	deque<Card> getDeck();
	Card getCard(int cardToPull){
		return this->cardsInPlay[cardToPull];
	}
	void removeFromPlay();
};