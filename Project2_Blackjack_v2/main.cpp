/* 
 * File:   main.cpp
 * Author: Aurelia Sindhunirmala
 *
 * Created on May 6, 2023, 12:20 PM
 * Purpose: Version 2 of Project 2
 *          Revision  : Mistakes in functions 
 *          Addition  : Exit function
 */

// System Libraries
#include <iostream>     //Input/Output library
#include <iomanip>      //Format libary
#include <ctime>        //Set Random library 
#include <cstdlib>      //Random Functions
#include <fstream>      //File Stream Library
#include <string>       //String
#include <cmath>        //Math Library
using namespace std; 

//User Libraries

//Global Constants Math/Physics/Chemistry/Conversions ONLY!!!!!
const int NUMCRD = 52;

//Function Prototypes
void first();   //First page of the game
void Menu();    //Menu for the first page
int getN();     //Getting input for menu
void def(int);  //Default switch case for menu
void toc1();    //Menu option 1
void toc2();    //Menu option 2
void toc3();    //Menu option 3
int Rate();     //Rate the game 
void exitGm();  //Exit game 

//Execution Begins HERE!!!!
int main(int argc, char** argv) {
    //Set random number seed
    
    //Declare variables
    fstream in;
    int inp,
        card,
        faceVal,
        sum,
        sum2,
        rate;
    char hsAns;
    float pBet;
    string cmnt;
   
    //Initialize Inputs
    
    //Map Inputs to Outputs - Process
    first();
    
    //Display output

    //Exit stage right
    return 0;
}

void first(){   //First page of the game
    //Declare variables
    int inp;
        
    //Display output
    cout<<setw(25)<<"Welcome to Blackjack"<<endl;
    cout<<setw(28)<<"=========================="<<endl;
    
    do{
        Menu();
        inp = getN();
        switch(inp){
            case 1:     toc1();break;
            case 2:     toc2();break;
            case 3:     toc3();break;
            default:    def(inp);
        }
    }
    while (inp < 3);
}

void Menu(){    //Menu for the first page
    //Menu
        cout << setw(16) << "MENU" << endl;
        cout << setw(25) << "----------------------" << endl;
        cout << setw(27) << "Choose the options below:" << endl;
        cout << setw(12) << "1. Rules" << endl;
        cout << setw(12) << "2. Start" << endl;
        cout << setw(16) << "3. Exit Game" << endl;
        cout<<endl;
}

int getN(){     //Getting input for menu
    int inp;
    cin >> inp;
    return inp;
}

void def(int inp){  //Default switch case for menu
    cout<<endl<<"Typing "<<inp<<" exits the program."<<endl;
}

void toc1(){    //Menu option 1: Rules of the Game
    cout << "Here are the rules for the game!" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "1. The game starts with each player placing their bet on the table (max bet: $1000)." << endl;
    cout << "2. The dealer deals two cards to each player, including themselves." << endl;
    cout << "   The dealer's first card is dealt face up (shown), while the second card is dealt face down (not shown)." << endl;
    cout << "3. The value of each card is as follows: " << endl;
    cout << "   a. All numbered cards are worth their face value" << endl;
    cout << "   b. Face cards (such as Jacks, Queens,and Kings) are worth 10, and" << endl;
    cout << "   c. Aces are worth either 1 or 11, depending on which value would be more advantageous for the player." << endl;
    cout << "4. Players can choose to hit (receive another card) or stand (keep their current card) in order to get " << endl;
    cout << "   as close to 21 as possible without going over. Players can continue to hit until they decide to stand, " << endl;
    cout << "   or until they go over 21, or known as bust."<<endl;
    cout << "5. Once the player have completed their turn, the dealer reveals their hole card and hits or stands according" << endl;
    cout << "   to a set of predetermined rules" << endl;
    cout << "6. If the dealer busts, the player win their bets. If the dealer does not bust, then the player and the" << endl;
    cout << "   dealer with the hand value closest to 21 without going over wins. If the player's hand value is the same as " << endl;
    cout << "   the dealer's, it is a tie and the player's bet is returned."<<endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
}

void toc2(){    //Menu option 2
    //Declaring variables
    int inp,
        card,
        faceVal,
        sum,
        sum2,
        rate;
    char hsAns;
    float pBet;
    
    cout << "Let's Start!" << endl;
    cout << "Place your bet. (Bet should be less than $1000)"<<endl;
    cin >> pBet;
    if (pBet > 1000){
        cout << "Value exceed the maximum rule." << endl << endl;
    } 
    else{
        if (pBet < 0){
            pBet = abs(pBet);
        }
    cout << fixed << showpoint << setprecision(2);
    cout << "You put a bet for $ " << pBet << endl << endl;

    //Set random of seed 
    srand(static_cast <unsigned int>(time(0)));

    //Shuffle deck for dealer 
    sum = 0;
    for (int i = 0; i < 1; i++) {
        card = rand() % NUMCRD + 1;     //[1,52]
        faceVal = (card % 11) + 1;      //[1,11]
        sum += faceVal;
        cout << "Dealer's Card #1" << ": " << faceVal << endl << endl;
    }

    //Shuffle deck for player
    sum2 = 0;
    for (int i = 0; i < 2; i++) {
        card = rand() % NUMCRD + 1;     //[1,52]
        faceVal = (card % 11) + 1;      //[1,11]
        sum2 += faceVal;
        cout << "Player's Card #" << i + 1 << ": " << faceVal << endl;
    }

    // Display sum to player
    cout << "Player's Total  : " << sum2 << endl << endl;

    // Additional cards for player
    while (sum <= 21 || sum2 <= 21 || sum < sum2 || sum2 < sum
            || sum != 21 || sum2 != 21) {
        cout << "Do you want to hit or stand? (H/S)" << endl;
        cin >> hsAns;
        cout << endl;

        // If player choose to hit
        if (hsAns == 'H' || hsAns == 'h') {
            card = rand() % NUMCRD + 1;     //[1,52]
            faceVal = (card % 11) + 1;      //[1,11]
            sum2 += faceVal;
            cout << "Player's new card: " << faceVal << endl;
            cout << "Player's Total   : " << sum2 << endl << endl;

            // If player's card sum exceeds 21, player busts and loses the game
            if (sum2 > 21) {
                cout << "Player busts, dealer wins!" << endl;
                cout << "You lose your bet of " << "$" << pBet << endl;
                cout << endl;

                Rate();
                exitGm();
             }

            // If player's card sum is exactly 21, player wins the game
            else if (sum2 == 21) {
                cout << "Player wins!" << endl;
                cout << "Congrats! You win your bet of " << "$" << pBet << endl;
                cout << endl;

                Rate();
                exitGm();
            }
        }
        // If player choose to stand, dealer starts their turn
        else if (hsAns == 'S' || hsAns == 's') {
            // Dealer's 2nd card
            card = rand() % NUMCRD + 1;     //[1,52]
            faceVal = (card % 11) + 1;      //[1,11]
            sum += faceVal;
            cout << "Dealer's Card #2: " << faceVal << endl;
            cout << "Dealer's Total  : " << sum << endl << endl;

            // Dealer's additional cards
            if  (sum < 17) {
                card = rand() % NUMCRD + 1;     //[1,52]
                faceVal = (card % 11) + 1;      //[1,11]
                sum += faceVal;
                cout << "Dealer's new card: " << faceVal << endl;
                cout << "Dealer's Total   : " << sum << endl << endl;

                // If dealer's card sum exceeds 21, dealer busts and player wins
                if (sum > 21) {
                    cout << "Dealer busts, player wins!" << endl;
                    cout << "Congrats! You win your bet of " << "$" << pBet << endl;
                    cout << endl;

                    Rate();
                    exitGm();
                }
            }

            // If neither player nor dealer busts, compare their card sums
            if (sum <= 21 && sum2 <= 21) {
                if (sum > sum2) {
                    cout << "Dealer wins!" << endl;
                    cout << "You lose your bet of " << "$" << pBet << endl;
                    cout << endl;

                    Rate();
                    exitGm();
                }
                else if (sum < sum2) {
                    cout << "Player wins!" << endl;
                    cout << "Congrats! You win your bet of " << "$" << pBet << endl;
                    cout << endl;

                    Rate();
                    exitGm();
                }
                else {
                    cout << "It's a tie!" << endl;
                    cout << "You get your bet back!" << endl;
                    cout << endl;

                    Rate();
                    exitGm();
                    }
                }
            }
        }
    }
}

void toc3(){    //Menu option 3
    exitGm();
}

int Rate(){     //Rate the game 
    cout << "THANK YOU FOR VISITING BLACKJACK!" <<endl;
    cout << "Please rate us starting from 1-10" << endl;
    
    //Calling the file and declaring variables inside the file
    fstream in;
    int inpRate;
    string rate;
    
    //Reading the file
    in.open("rate.dat", ios::in);
    
    //Asking user for input
    cout << "Enter a number between 1 and 10: ";
    cin >> inpRate;
    
    //Rating = which line in rate.dat file 
    for (int i = 1; i <= inpRate; i++) {
        getline(in, rate);
    }
    
    //Printing out the category for the rating
    cout << "You have rated this program as " << rate << "." << endl;
    cout << "Thank you for rating this program! Hope you enjoy your visit!" << endl << endl;
    
    //Closing the file
    in.close();
    return inpRate;
}

void exitGm(){
    char ext;
    cout << "Are you sure to exit the game? (y/n)" << endl;
    cin >> ext;
    if (ext == 'Y' || ext == 'y'){
        cout << "Exiting the game. Goodbye!" << endl;
        exit(0);
    }
    else {
        Menu();
    }
}