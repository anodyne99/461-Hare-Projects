// James Helm
// Fall 2021
// Project 1 - Bridge

#include "Deck.h"
#include "Card.h"
#include "Hand.h"
#include <cctype>
#include <ctime>
#include <map>
using namespace std;

int tests;
char userEntry;
int pointSum;
int passTally, partScoreTally, gameTally, smallSlamTally, grandSlamTally;
map<int, char> suits = { {0, 'S'}, {1, 'H'}, {2, 'C'}, {3, 'D'} };
map<int, char> faceCards = { {12, 'K'} , {11, 'Q'}, {10, 'J'}, {0, 'A'} };
Hand playerHand, partnerHand;

void gameCleanup() {
	tests = 0;
	passTally = 0;
	partScoreTally = 0;
	gameTally = 0;
	smallSlamTally = 0;
	grandSlamTally = 0;
	playerHand.emptyHand();
	userEntry = ' ';
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

void bestOutcomeCalculation(int pointSum) {
	if (pointSum < 20) {
		passTally++;
	}
	else if (20 <= pointSum && pointSum <=25) {
		partScoreTally++;
	}
	else if (25 < pointSum && pointSum <= 31) {
		gameTally++;
	}
	else if (31 < pointSum && pointSum <= 35) {
		smallSlamTally++;
	}
	else {
		grandSlamTally++;
	}
}

float bestOutcomePercentageOutput(float tally) {
	return (tally / 10);
}

int main() {
	srand(unsigned(time(0))); // Initial seed generation for random_shuffle functionality
	do {
		gameCleanup();
		Deck defaultDeck;
		defaultDeck.shuffleDeck();
		playerHand.dealToHand(defaultDeck);
		playerHand.setHandValue();
		cout << "Here is your hand: \n";
		handOutPut();
		cout << endl;
		cout << "This hand is worth " << playerHand.getHandValue() << " points." << endl;
		cout << "Running simulation..." << endl;
		cout << endl;
		do {
			Deck deckToTest(defaultDeck.getDeck());
			deckToTest.shuffleDeck();
			partnerHand.dealToHand(deckToTest);
			partnerHand.setHandValue();
			int pointSum = 0;
			pointSum = (playerHand.getHandValue() + partnerHand.getHandValue());
			bestOutcomeCalculation(pointSum);
			partnerHand.emptyHand();
			tests++;
		} while (tests < 1000);
		cout << "The estimated probability based on 1000 simulated hands:" << endl;
		cout << "Pass: " << bestOutcomePercentageOutput(passTally) << "%" << endl;
		cout << "Part Score: " << bestOutcomePercentageOutput(partScoreTally) << "%" << endl;
		cout << "Game : " << bestOutcomePercentageOutput(gameTally) << "%" << endl;
		cout << "Small Slam: " << bestOutcomePercentageOutput(smallSlamTally) << "%" << endl;
		cout << "Grand slam: " << bestOutcomePercentageOutput(grandSlamTally) << "%" << endl;
		while (userEntry != 'Y' && userEntry != 'N') {
			cout << "Another hand? [Y/N]?";
			cin >> userEntry;
			userEntry = toupper(userEntry);
			if (userEntry != 'Y' && userEntry != 'N') {
				cout << "Error! Please enter either Y or N" << endl;
			}
		}
		cout << endl;
	} while (userEntry == 'Y');
};