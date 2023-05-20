//  Name: Aaron Garcia
//  Course: CECS 325
//  Project Name: Assignment
//  Due Date: Mon/Aug 29/2022
//  
//  I certify that this program is my own original work.
//  I did not copy any part of this program from any other source.
//  I further certify that I typed each and every line of code in this program.

#include <iostream>

#include "Card.h"
#include "Deck.h"

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