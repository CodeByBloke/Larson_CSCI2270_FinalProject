#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

using namespace std;

struct Space {
    /*
    value = 0 -> empty
    value = 1 -> X
    value = 2 -> O 
    */
    int value; 

    Space(int v) {
        value = v;
    }
};

class Board {
    public:
        Board(int firstPlayer);

        int getSpaceValue(int row, int column); // Get the value at a specific row and column
        char getSpaceCharacter(int row, int column); // Get the token at a specific row and column
        void outputBoard(); // Draw a representation of the board on the terminal
        void setSpaceValue(int row, int column, char playerToken); // Set the value of a space to a token
        bool isWinner(char playerToken); // Returns true if the player has a winning position
        bool isGameTied(); // Check to see if the board is a tied position
        vector<vector<int>> getPossibleMoves(vector<vector<int>> movesMade); // Returns a vector with the possible moves given the current state of the board
        vector<int> getHorizontalReflectionMove(vector<int> move, vector<vector<int>> movesMade); // Get the move that is a horizontal reflection
        vector<int> getVerticalReflectionMove(vector<int> move, vector<vector<int>> movesMade); // Get the move that is a vertical reflection
        vector<int> getOppositeCornerMove(vector<int> move, vector<vector<int>> movesMade); // Get the move that is on the opposite corner
        vector<int> getInteriorReflectionMoveOne(vector<int> move, vector<vector<int>> movesMade); // Get the move that is interiorally reflected
        vector<int> getInteriorReflectionMoveTwo(vector<int> move, vector<vector<int>> movesMade); // Get the move that is interiorally reflected
        int getGameResultForComputer(vector<vector<int>> movesMade); // Get the result of a current board for the computer

    private:
        int rows = 3;
        int columns = 3;
        vector<vector<Space*>> board;
        /*
        1 = User
        2 = Computer
        */
        int whoGoesFirst;
        int winningCombinations[8][3][2] = {{{0, 0}, {0, 1}, {0, 2}},  // This is a list of all the possible ways to win
                                            {{1, 0}, {1, 1}, {1, 2}},
                                            {{2, 0}, {2, 1}, {2, 2}},
                                            {{0, 0}, {1, 0}, {2, 0}},
                                            {{0, 1}, {1, 1}, {2, 1}},
                                            {{0, 2}, {1, 2}, {2, 2}},
                                            {{0, 0}, {1, 1}, {2, 2}},
                                            {{2, 0}, {1, 1}, {0, 2}}};

        void initalizeBoard();
        bool moveInMoveList(int row, int column, vector<vector<int>> moveList); // Check to see if a move in the given move list
        void resetBoard(vector<vector<int>> movesMadeByWho); // Reset the board to its position before doing checks
};

#endif
