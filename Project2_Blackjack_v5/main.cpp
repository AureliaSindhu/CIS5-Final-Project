/* 
 * File:   main.cpp
 * Author: Aurelia Sindhunirmala
 *
 * Created on May 6, 2023, 12:20 PM
 * Purpose: Version 5 of Project 2
 *          Revision  : Implementing arrays and sorts in the code 
 */

// System Libraries
#include <iostream>     //Input/Output library
#include <iomanip>      //Format libary
#include <ctime>        //Set Random library 
#include <cstdlib>      //Random Functions
#include <fstream>      //File Stream Library
#include <string>       //String
#include <cmath>        //Math Library
#include <array>        //Array Library
#include <vector>       //Vector Library
using namespace std; 

//User Libraries

//Global Constants Math/Physics/Chemistry/Conversions ONLY!!!!!

//Function Prototypes
void first();   //First page of the game
void Menu(int&);    //Menu for the first page
int getN();     //Getting input for menu
void def(int);  //Default switch case for menu
void toc1();    //Menu option 1
bool toc2();    //Menu option 2
void toc3();    //Menu option 3
bool Rate();     //Rate the game 
bool exitGm();  //Exit game 
void printCS(int);
void printFV(int);
void slSt(int [], int);
bool linSc(int [], int , int);

//Execution Begins HERE!!!!
int main(int argc, char** argv) {
    //Set random number seed
    srand(static_cast <unsigned int>(time(0)));
    
    //Declare variables
   
    //Initialize Inputs
    
    //Map Inputs to Outputs - Process
    do{
        first();
    }
    while (!exitGm());
    //Display output

    //Exit stage right
    return 0;
}

void first(){   //First page of the game
    //Declare variables
    int choice, inp;
    static int gmCnt = 0;
        
    //Display output
    cout<<setw(25)<<"Welcome to Blackjack"<<endl;
    cout<<setw(28)<<"=========================="<<endl;
    
    do{
        Menu(choice);
        switch(choice){
            case 1:     toc1();break;
            case 2:     toc2();break;
            case 3:     toc3();break;
            default:    def(inp);
        }
    }
    while (inp < 3);
    
    // Increment gameCount
    gmCnt++;
    cout << "Number of games played: " << gmCnt << endl;
}

void Menu(int& option){    //Menu for the first page
    //Menu
        cout << setw(16) << "MENU" << endl;
        cout << setw(25) << "----------------------" << endl;
        cout << setw(27) << "Choose the options below:" << endl;
        cout << setw(12) << "1. Rules" << endl;
        cout << setw(12) << "2. Start" << endl;
        cout << setw(16) << "3. Exit Game" << endl;
        cout<<endl;
        cout << "Enter your choice: ";
        cin >> option;
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
    cout << "   c. Aces are worth 1 or 11 based on the system itself." << endl;
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

bool toc2(){    //Menu option 2
    //Declaring variables
    int card, faceVal, sum, sum2;
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
            card = rand() % 52 + 1;     //[1,52]
            faceVal = (card % 11) + 1;      //[1,11]
            sum += faceVal;
            cout << "Dealer's Card #1" << ": ";
            printFV(faceVal);
            printCS(rand() % 4 + 1); // Randomly generate and print card sign
            cout << endl << endl;
        }

    //Shuffle deck for player
    int pCrd[2];
    int numPC = 2;
    for (int i = 0; i < numPC; i++) {
        card = rand() % 52 + 1;     //[1,52]
        faceVal = (card % 11) + 1;      //[1,11]
        pCrd[i] = faceVal;
        cout << "Player's Card #" << i + 1 << ": ";
        printFV(faceVal);
        printCS(rand() % 4 + 1); // Randomly generate and print card sign
        cout << endl;
    }

    // Bubble sort the player's cards
    for (int i = 0; i < numPC - 1; i++) {
        for (int j = 0; j < numPC - i - 1; j++) {
            if (pCrd[j] > pCrd[j + 1]) {
                int temp = pCrd[j];
                pCrd[j] = pCrd[j + 1];
                pCrd[j + 1] = temp;
            }
        }
    } 
    
    // Selection sort the player's cards
    slSt(pCrd, numPC);
    
    // Calculate the sum of player's cards
    sum2 = 0;
    for (int i = 0; i < numPC; i++) {
        sum2 += pCrd[i];
    }
    
    // Display sum to player
    cout << "Player's Total  : " << sum2 << endl << endl;
    
    // Additional cards for player
    while (sum <= 21 || sum2 <= 21 || sum < sum2 || sum2 < sum
            || sum != 21 || sum2 != 21) {
        // Linear search for a specific card value (e.g., 10)
        int searchValue = 21;
        bool found = linSc(pCrd, numPC, searchValue);
        if (found) {
            cout << endl << "Player has a card with value " << searchValue << endl;
        } else {
            cout << "Player does not have a card with value " << searchValue << endl;
            cout << "Please proceed the game." << endl << endl;
        }
    
        cout << "Do you want to hit or stand? (H/S)" << endl;
        cin >> hsAns;
        cout << endl;

        // If player choose to hit
        if (hsAns == 'H' || hsAns == 'h') {
            card = rand() % 52 + 1;     //[1,52]
            faceVal = (card % 11) + 1;      //[1,11]
            sum2 += faceVal;
            cout << "Player's new card: ";
            printFV(faceVal);
            printCS(rand() % 4 + 1); // Randomly generate and print card sign
            cout << endl;
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
            card = rand() % 52 + 1;     //[1,52]
            faceVal = (card % 11) + 1;      //[1,11]
            sum += faceVal;
            cout << "Dealer's Card #2: ";
            printFV(faceVal);
            printCS(rand() % 4 + 1); // Randomly generate and print card sign
            cout << endl;
            cout << "Dealer's Total  : " << sum << endl << endl;
                
            // Dealer's additional cards
            if  (sum < 17) {
                card = rand() % 52 + 1;     //[1,52]
                faceVal = (card % 11) + 1;      //[1,11]
                sum += faceVal;
                cout << "Dealer's new card: ";
                printFV(faceVal);
                printCS(rand() % 4 + 1); // Randomly generate and print card sign
                cout << endl;
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

bool linSc(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return true;
        }
    }
    return false;
}

void printCS(int sign) {
    switch (sign) {
        case 1:
            cout << "Diamond";
            break;
        case 2:
            cout << "Club";
            break;
        case 3:
            cout << "Heart";
            break;
        case 4:
            cout << "Spade";
            break;
        default:
            break;
    }
}

void printFV(int value = 1) {
    if (value == 1) {
        cout << "Ace ";
    }
    else if (value >= 2 && value <= 10) {
        cout << value << " ";
    }
    else if (value == 11) {
        cout << "Jack ";
    }
    else if (value == 12) {
        cout << "Queen ";
    }
    else if (value == 13) {
        cout << "King ";
    }
}       
        
void slSt(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int indx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[indx]) {
                indx = j;
            }
        }
        // Swap the found minimum element with the first element
        int temp = arr[indx];
        arr[indx] = arr[i];
        arr[i] = temp;
    }
}

void toc3(){    //Menu option 3
    exitGm();
}

bool Rate(){     //Rate the game 
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
    return true;
}

bool exitGm(){
    char ext;
    cout << "Are you sure to exit the game? (y/n)" << endl;
    cin >> ext;
    if (ext == 'Y' || ext == 'y'){
        cout << "Exiting the game. Goodbye!" << endl;
        exit(0);
    }
    else {
        first();
    }
}