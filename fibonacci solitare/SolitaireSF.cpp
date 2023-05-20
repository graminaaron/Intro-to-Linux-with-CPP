//  Name: Aaron Garcia
//  Course: CECS 325
//  Project Name: Assignment
//  Due Date: Mon/Aug 29/2022
//  
//  I certify that this program is my own original work.
//  I did not copy any part of this program from any other source.
//  I further certify that I typed each and every line of code in this program.

#include <iostream>

class Card{
    char rank;
    char suit;

public:
    Card(){
        rank = ' ';
        suit = ' ';
    }
    Card(char r, char s){//rank, suit
        rank = r;
        suit = s;
    }
    void setCard(char r, char s){
        rank = r;
        suit = s;
    }
    int getValue(){
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
    void display(){
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
};

class Deck{
    Card mDeck[52];
    int topOfDeck;

public:
    Deck(){
        refreshDeck();
    }

    void refreshDeck(){
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
    
    Card deal(){
        //take card off of the top
        Card tCard = mDeck[topOfDeck];
        topOfDeck = topOfDeck - 1;
        //return said card
        return tCard;
    }
    void shuffle(){
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

    bool isEmpty(){
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
    
    void display(){
        //loop through all card and display them using the classes function
        for (int i = 0; i < 52; i++){
            mDeck[i].display();
            std::cout << ", ";
        }
    }
};



int main(){
    Deck myDeck; // Create Deck
    bool playing = true; // Start Playing
    int userInput; // Number 1-5
    int numOfGames = 0; //Aggregator for the number of games

    std::cout << "Welcome to Fibonacci Solitare!" << std::endl;

    while(playing == true){
        //Display options
        std::cout << "Please Select an Option:" << std::endl;
        std::cout << "1) New Deck" << std::endl;
        std::cout << "2) Display Deck" << std::endl;
        std::cout << "3) Shuffle Deck" << std::endl;
        std::cout << "4) Play Solitaire" << std::endl;
        std::cout << "5) Exit" << std::endl;

        std::cin >> userInput;
        std::cin.clear();

        if (userInput == 1){
            std::cout << "Refreshing Deck..." << std::endl;
            myDeck.refreshDeck();
        }
        else if(userInput == 2){
            std::cout << "Displaying Deck..." << std::endl;
            myDeck.display();
        }
        else if(userInput == 3){ 
            std::cout << "Shuffling Deck..." << std::endl;
            myDeck.shuffle();
        }
        else if(userInput == 4){ //Game Condition
            std::cout << "Let's Play Solitare!" << std::endl;
            
            Card currentCard;
            int fiboNum[] = {0,1,2,3,5,8,13,21,34,55,89,144,233}; 
                // Next num in the sequence is 377 
                // I chose all fibonacci sequence characters below 340 here,
                // since they cannot add up past 340.
            int totalSum = 0; //sum of cards
            int piles = 0; //the amount of card piles accumulated
            bool sumIsFibo = false;
            bool deckEmpty = myDeck.isEmpty(); 

            while(!deckEmpty){
                sumIsFibo=false; //reset
                totalSum = 0; //reset
                while(!sumIsFibo){ 
                    currentCard = myDeck.deal(); //deal a card
                    deckEmpty = myDeck.isEmpty(); //ask if out of cards
                    currentCard.display();
                    std::cout << ", ";
                    totalSum = totalSum + currentCard.getValue();

                    // if the sum of the cards is in the fibonacci sequence, 
                    // break sequence and restart from the beginning
                    for (int i = 0; i < 13; i++){
                        if (totalSum == fiboNum[i]){
                            sumIsFibo = true;
                            std::cout << std::endl << "Fibo! ";
                            break;
                        }
                    }
                    if(deckEmpty == true){ // If I am out of cards, begin exit sequence
                        std::cout << std::endl;
                        break;
                    }
                }
                piles = piles + 1;
                std::cout << "Sum: " << totalSum << std::endl;
            }
            if (sumIsFibo){ //Determine if the last card drawn gave a fibo pile, declare winner
                std::cout << "Winner in " << piles << " piles!" << std::endl;
            }
            else{ //... else declare loss
                std::cout << "Loser in " << piles << " piles..." << std::endl;
            }
            numOfGames = numOfGames + 1;
            std::cout << "Games Played: " << numOfGames << std::endl;
        }
        else if(userInput == 5){
            break;
        }
        else{// only accept nums 1-5
            std::cout << "Invald Input, please enter a # from 1-5." << std::endl;
        }
    }//exit program
    std::cout << "Thanks for playing!" << std::endl;
}