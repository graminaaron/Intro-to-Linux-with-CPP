#include <iostream>
#include "Card.h"

Card::Card(){
    rank = ' ';
    suit = ' ';
}

Card::Card(char r, char s){//rank, suit
    rank = r;
    suit = s;
}

void Card::setCard(char r, char s){
    rank = r;
    suit = s;
}

int Card::getValue(){
    int rankValue = 0;
    if (rank == 'A' || rank == 'a'){ // If its an ace
        rankValue = 1;
    }
    else if (rank == 'T' || rank == 't' ||
        rank == 'J' || rank == 'j' ||
        rank == 'Q' || rank == 'q' || 
        rank == 'K' || rank == 'k'){ //If it is an Jack, Queen, or King
            rankValue = 10; //The rank is valued at 10
        } 
    else if (rank >= '2' && rank <= '9'){ //Otherwise if it is a number
        rankValue = (int)rank - 48; // Convert from char to int
    }
    else{
        rankValue = 0;
    }
    
    return rankValue;
}

void Card::display(){
    int rankDisplay = rank;
    //if it is a Ten, display it as "10" rather than "T"
    if (rank == 'T' || rank == 't'){
        std::cout << getValue() << suit;
    }
    //else, just used its rank character
    else{
        std::cout << rank << suit;
    }
}