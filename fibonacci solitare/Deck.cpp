#include <iostream>
#include <cstdlib>

#include "Card.h"
#include "Deck.h"

Deck::Deck(){
    refreshDeck();
}

void Deck::refreshDeck(){
    //recall 52nd card is indexed at 51
    topOfDeck = 51;
    int cardNum = 0;
    //Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King
    char ranks[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    //Spade, Heart, Diamond, Club
    char suits[] = {'S', 'H', 'D', 'C'};
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 13; j++){
            mDeck[cardNum] = Card(ranks[j],suits[i]);
            cardNum = cardNum + 1;
        }
    }
}

Card Deck::deal(){
    //take card off of the top
    Card tCard = mDeck[topOfDeck];
    topOfDeck = topOfDeck - 1;
    //return said card
    return tCard;
}

void Deck::shuffle(){
    topOfDeck = 51;
    Card tCard;

    for (int i = 0; i < 52; i++){
        //Swap an even indexed card with 
        //a random odd indexed card, ascending index
        int randOddCard = std::rand()%52;
        if (randOddCard%2 == 0){
            randOddCard = randOddCard + 1;
        }
        //swap cards
        tCard = mDeck[randOddCard];
        mDeck[randOddCard] = mDeck[i];
        mDeck[i] = tCard;
        //Swap an even indexed card with 
        //a random odd indexed card, descending index
        randOddCard = std::rand()%52;
        if (randOddCard%2 == 0){
            randOddCard = randOddCard + 1;
        }
        //iOpp is th opposite of i, it is variable to determine 
        //number of cards from the top rather than bottom
        int iOpp = 51 - (i);
        //swap cards
        tCard = mDeck[randOddCard];
        mDeck[randOddCard] = mDeck[iOpp];
        mDeck[iOpp] = tCard;
    }
}

bool Deck::isEmpty(){
    //if out of bounds of the index of the deck, deck is empty
    if (topOfDeck == -1){
        topOfDeck = 51;
        return true;
    }
    //else, continue
    else{
        return false;
    }
}

void Deck::display(){
    //loop through all card and display them using the classes function
    for (int i = 0; i < 52; i++){
        mDeck[i].display();
        std::cout << ", ";
    }
}