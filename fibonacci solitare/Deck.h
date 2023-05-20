#ifndef DECK_H
#define DECK_H
#include "Card.h"

class Deck{
    Card mDeck[52];
    int topOfDeck;

public:
    Deck();
    void refreshDeck();
    Card deal();
    void shuffle();
    bool isEmpty();
    void display();
};
#endif // !DECK_H