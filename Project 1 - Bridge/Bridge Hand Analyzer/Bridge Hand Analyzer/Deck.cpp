#include "Deck.h"

Deck::Deck() {
	for (unsigned int i = 0; i < 52; i++) {
		Card generatedCard(i);
		cardsInPlay.push_back(generatedCard);
	}
}

void Deck::shuffleDeck() {
	random_shuffle(this->cardsInPlay.begin(), this->cardsInPlay.end());
}

Deck::Deck(deque<Card> updatedDeck) {
	cardsInPlay = updatedDeck;
}

deque<Card> Deck::getDeck() {
	return this->cardsInPlay;
}

void Deck::removeFromPlay() {
	this->cardsInPlay.pop_front();
}