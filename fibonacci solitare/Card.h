#ifndef CARD_H
#define CARD_H

class Card{
    char rank;
    char suit;
    
public:
    Card();
    Card(char, char); //rank, suit
    void setCard(char, char);
    int getValue();
    void display();
};
#endif // !CARD_H