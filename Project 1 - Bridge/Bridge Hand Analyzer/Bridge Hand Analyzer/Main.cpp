// James Helm
// Fall 2021
// Project 1 - Bridge

#include "Deck.h"
#include "Card.h"
#include "Hand.h"
#include <map>
using namespace std;

void shuffleDeck(Deck& deck) {
	random_shuffle(deck.cardsInPlay.begin(), deck.cardsInPlay.end());
}


int run = 0;
map<int, char> suits = { {0, 'S'}, {1, 'H'}, {2, 'C'}, {3, 'D'} };
Hand playerHand;
Hand partnerHand;

int main() {
	Deck defaultDeck;
	shuffleDeck(defaultDeck);
	playerHand.dealToHand(defaultDeck);
	playerHand.setHandValue();
	do {
		Deck deckToTest(defaultDeck.getDeck());
		shuffleDeck(deckToTest);
		partnerHand.dealToHand(deckToTest);
		partnerHand.setHandValue();
		run++;
	} while (run < 500);
};