/* 
 * File:   main.cpp
 * Author: Aurelia Sindhunirmala
 *
 * Created on June 7, 2023, 11:30 PM
 * Purpose: Version 9 of Project 2
 * 
 */

// System Libraries
#include <iostream>     //Input/Output library
#include <iomanip>      //Format library
#include <ctime>        //Set Random library 
#include <cstdlib>      //Random Functions
#include <fstream>      //File Stream Library
#include <string>       //String
#include <cmath>        //Math Library
#include <vector>       //Vector Library
using namespace std; 

//User Libraries

//Global Constants Math/Physics/Chemistry/Conversions ONLY!!!!!
const int OPTIONS = 3;
const string menuOpt[OPTIONS][2];

//Function Prototypes
void first();                        //First page of the game
void Menu(int&);                    //Menu for the first page
void display();                     //Display menu
void def(int);                      //Default switch case for menu
void toc1();                        //Menu option 1
bool toc2();                        //Menu option 2
void toc3();                        //Menu option 3
bool Rate();                        //Rate the game 
int vldRate(const vector<string>&); //Validating Rate Input
bool exitGm();                      //Exit game 
void printCS(int);                  //Print Card Suites
void printFV(int);                  //Print Card Face Val
void slSt(int [], int);             //Selection sort
bool linSc(int [], int , int);      //Linear search

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
    
    do{ //choice of menu 
        Menu(choice);
        switch(choice){
            case 1:     toc1();break;   //calling function toc1
            case 2:     toc2();break;   //calling function toc2
            case 3:     toc3();break;   //calling function toc3
            default:    def(inp);
        }
    }
    while (choice < 3);
    
    // Increment gameCount
    gmCnt++;
    cout << "Number of games played: " << gmCnt << endl;
}

void Menu(int& option){    //Menu for the first page
    bool vldInp = false;
    option = 0;
    while (!vldInp){
    display();
    cout << endl << "Enter your choice : ";
    cin >> option;
    
    if (option == '1' || option == '2' || option == '3') {
        cout << option;
    }
    else if (option < 1 || option > 3){  //If input is not within the requirements
        cout << "Input invalid." << endl << endl;
    }
    else{ vldInp = true;}
    }
}

void display(){
    string menuOpt[OPTIONS][2] = {    //2D arrays for printing out the menu 
        {"1. Rules", "Display the game rules"},
        {"2. Start", "Start the game"},
        {"3. Exit Game", "Exit the game"}
    };
    
    cout << setw(16) << "MENU" << endl;
    cout << setw(25) << "----------------------" << endl;
    cout << setw(27) << "Choose the options below:" << endl;
    
    for (int i = 0; i < OPTIONS; i++) {
        cout << setw(12);
        if (i == OPTIONS - 1){
            cout << setw(16);
        }
        cout << menuOpt[i][0] << " - " << menuOpt[i][1] << endl;    //Calling the menu with 2D arrays
    }
}

void def(int inp = 0){  //Default switch case for menu
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
    exitGm();
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
    else if (pBet < 0){
            pBet = abs(pBet);
    }
    cout << fixed << showpoint << setprecision(2);
    cout << "You put a bet for $ " << pBet << endl << endl;

    //Shuffle deck for dealer 
    sum = 0;
    for (int i = 0; i < 1; i++) {
            card = rand() % 52 + 1;         //[1,52]
            faceVal = (card % 11) + 1;      //[1,11]
            sum += faceVal;
            cout << "Dealer's Card #1" << ": ";
            printFV(faceVal);               // Printing Cards Face Value
            printCS(rand() % 4 + 1);        // Randomly generate and print card sign
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
        
        // Linear search for a specific card value 
        int scVal = 21;
        bool found = linSc(pCrd, numPC, scVal);
        if (found) {
            cout << endl << "Player has a card with value " << scVal << endl;
        } else {
            cout << "Player does not have a card with value " << scVal << endl;
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

bool linSc(int arr[], int size, int key) { //Linear search
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return true;
        }
    }
    return false;
}

void printCS(int sign) {    //Printing Card Suites
    switch (sign) {
        case 1: cout << "Diamond"; break;
        case 2: cout << "Club"; break;
        case 3: cout << "Heart"; break;
        case 4: cout << "Spade"; break;
        default: break;
    }
}

void printFV(int value) {   //Printing Face Value for cards
    if (value == 1 || value == 11) {
        cout << "Ace ";
    }
    else if (value >= 2 && value < 10) {
        cout << value << " ";
    }
    else if (value == 10) {
        cout << "Jack ";
    }
    else if (value == 11) {
        cout << "Queen ";
    }
    else if (value == 12) {
        cout << "King ";
    }
}       
        
void slSt(int arr[], int size) {    //Selection sort
    for (int i = 0; i < size - 1; i++) {
        int indx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[indx]) {
                indx = j;
            }
        }
        // Swap the found minimum val
        int temp = arr[indx];
        arr[indx] = arr[i];
        arr[i] = temp;
    }
}

void toc3(){    //Menu option 3
    exitGm();
}

bool Rate(const vector<string>& ratings){     //Rate the game 
    cout << "THANK YOU FOR VISITING BLACKJACK!" <<endl;
    cout << "Please rate us starting from 1-10" << endl;
    
    int inpRate = vldRate(ratings);
    
    //Printing out the category for the rating
    cout << "You have rated this program as " << ratings[inpRate - 1] << "." << endl;
    cout << "Thank you for rating this program! Hope you enjoy your visit!" << endl << endl;
    
    return true;
}

bool Rate(){
    //Calling the file and declaring variables inside the file
    fstream in;
    string rate;
    
    //Reading the file
    in.open("rate.dat", ios::in);
    vector<string> ratings;
    while (getline(in, rate)){
        ratings.push_back(rate);
    }
    in.close();
    
    return Rate(ratings);
}

int vldRate(const vector<string>& ratings) {   //Checking if the input is valid or not
    int inpRate;
    bool valid = false;
    
    //Asking user for input
    while (!valid) {
        cout << "Enter a number between 1 and " << ratings.size() << ": ";
        cin >> inpRate;

        //Validating user input
        if (inpRate >= 1 && inpRate <= ratings.size()) {
            valid = true;
        } else {
            cout << "Invalid rating. Please try again!" << endl;
        }
    }
    return inpRate;
}

bool exitGm(){  //Option to exit game
    char ext;
    cout << "Are you sure to exit the game? (y/n)" << endl;
    cin >> ext;

    //User input Y or N
    (ext == 'Y' || ext == 'y') ? 
        cout << "Exiting the game. Goodbye!" << endl, 
        exit(0) :  
        //If user choose N or n
        first();   
    return true;
}