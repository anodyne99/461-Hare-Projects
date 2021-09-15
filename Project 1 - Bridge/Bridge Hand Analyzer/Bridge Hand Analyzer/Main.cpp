// James Helm
// Fall 2021
// Project 1 - Bridge

#include "Deck.h"
#include "Card.h"
#include "Hand.h"
#include <ctime>
#include <map>
using namespace std;

int tests = 0, run = 1;
int pointSum;
int passTally = 0, partScoreTally = 0, gameTally = 0, smallSlamTally = 0, grandSlamTally = 0;
map<int, char> suits = { {0, 'S'}, {1, 'H'}, {2, 'C'}, {3, 'D'} };
map<int, char> faceCards = { {12, 'K'} , {11, 'Q'}, {10, 'J'}, {0, 'A'} };
Hand playerHand, partnerHand;

void shuffleDeck(Deck& deck) {
	random_shuffle(deck.cardsInPlay.begin(), deck.cardsInPlay.end());
}

void handOutPut() {
	for (unsigned int i = 0; i < 13; i++) {
		if (faceCards.find(playerHand.getCardsInHand()[i].getCardNumber()) == faceCards.end()) {
			cout << (playerHand.getCardsInHand()[i].getCardNumber()) + 1;
		}
		else {
			cout << faceCards[playerHand.getCardsInHand()[i].getCardNumber()];
		}
		cout << suits[playerHand.getCardsInHand()[i].getCardSuit()];
		cout << " ";
	}
}

void bestOutcomeCalculation() {
	if (pointSum < 20) {
		passTally++;
	}
	else if (20 <= pointSum <= 25) {
		partScoreTally++;
	}
	else if (25 < pointSum <= 31) {
		gameTally++;
	}
	else if (31 < pointSum <= 35) {
		smallSlamTally++;
	}
	else {
		grandSlamTally++;
	}
}

float bestOutcomePercentageOutput(float tally) {
	return (tally / 1000);
}

int main() {
	do {
		srand(unsigned(time(0)));
		Deck defaultDeck;
		shuffleDeck(defaultDeck);
		playerHand.dealToHand(defaultDeck);
		playerHand.setHandValue();
		cout << "Here is your hand: \n";
		handOutPut();
		cout << endl;
		cout << "This hand is worth " << playerHand.getHandValue() << " points." << endl;
		do {
			Deck deckToTest(defaultDeck.getDeck());
			shuffleDeck(deckToTest);
			partnerHand.dealToHand(deckToTest);
			partnerHand.setHandValue();
			int pointSum = (playerHand.getHandValue() + partnerHand.getHandValue());
			bestOutcomeCalculation();
			tests++;
		} while (tests < 1000);
		cout << "Pass: " << bestOutcomePercentageOutput(passTally) << endl;
		cout << "Part Score: " << bestOutcomePercentageOutput(partScoreTally) << endl;
		cout << "Game : ";
		run = 0;
	} while (run);
};