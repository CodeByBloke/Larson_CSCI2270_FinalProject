#include <iostream>
#include <vector>
#include <stdlib.h>
#include "board.cpp"
#include "Board.h"
#include "AI.cpp"
#include "AI.h"

using namespace std;

void outputMenu() { // Output the main menu
    cout<<"Main Menu:"<<endl;
    cout<<"  1. Play Tic-Tac-Toe"<<endl;
    cout<<"  2. Exit"<<endl<<endl;
    cout<<"Enter Your Selection: ";
}

void playTicTacToe() { // Play the game
    cout<<"Welcome to Tic-Tac-Toe!"<<endl<<endl;
    cout<<"Determining who will go first..."<<endl;

    int whoseTurn = rand() % 2 + 1; // Get random number between 1 and 2
    bool usersTurn;
    char userCharacter;
    char computerCharacter;
    Board* board;
    if(whoseTurn == 1) { // This condition is for the user going first
        cout<<"  -> You: X's (X's go first)"<<endl;
        cout<<"  -> Computer: O's"<<endl<<endl;
        usersTurn = true;
        userCharacter = 'X';
        computerCharacter = 'O';
        board = new Board(1);
    } else if(whoseTurn == 2) { // This condiiton is for the computer going first
        cout<<"  -> You: O's"<<endl;
        cout<<"  -> Computer: X's (X's go first)"<<endl<<endl;
        usersTurn = false;
        userCharacter = 'O';
        computerCharacter = 'X';
        board = new Board(2);
    }

    AI computer = AI(board);
    
    int turnNumber = 1;
    cout<<"Turn "<<turnNumber<<":"<<endl<<endl;
    board->outputBoard();
    cout<<endl;
    while(!board->isWinner('X') && !board->isWinner('O') && !board->isGameTied()) { // Keep playing while the game is not won loss or tied
        if(usersTurn) {
            int row;
            int column;

            // Get user input
            cout<<"It is your move..."<<endl;
            cout<<"  -> Type which row you want to place your "<<userCharacter<<": ";
            cin >> row;
            cout<<"  -> Type which column you want to place your "<<userCharacter<<": ";
            cin >> column;
            cout<<endl;

            board->setSpaceValue(row - 1, column - 1, userCharacter);
            board->outputBoard();
            cout<<endl;

            usersTurn = false;
        } else {
            cout<<"It is the computer's turn..."<<endl;
            cout<<"The computer is thinking..."<<endl;

            vector<int> move = computer.makeMove(); // Get computer move
            int row = move[0];
            int column = move[1];

            cout<<"The computer placed their "<<computerCharacter<<" on row "<<row + 1<<" and column "<<column + 1<<endl;
            cout<<endl;

            board->setSpaceValue(row, column, computerCharacter);
            board->outputBoard();
            cout<<endl;

            usersTurn = true;
        }
    }

    bool userWon = board->isWinner(userCharacter); // Check to see who won
    bool computerWon = board->isWinner(computerCharacter);

    if(userWon) {
        cout<<"Wow you won! This message is not supposed to appear. This means the AI is not good enough."<<endl;
    } else if(computerWon) {
        cout<<"The computer has won. Yet another blow to humans in the human vs. AI war."<<endl;
    } else {
        cout<<"You tied. Valient effort against an unbeatable computer!"<<endl;
    }

    cout<<endl;
}

int main() {
    srand(time(NULL)); // Generate seed to generate random numbers

    int userSelection;

    outputMenu();
    cin >> userSelection;

    while(userSelection != 2) {
        cout<<"***********************"<<endl<<endl;

        if(userSelection == 1) {
            playTicTacToe();
        }

        outputMenu();
        cin >> userSelection;
    }
}



