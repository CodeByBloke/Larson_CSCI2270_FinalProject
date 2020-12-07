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

        int getSpaceValue(int row, int column);
        char getSpaceCharacter(int row, int column);
        void outputBoard(); // Draw a representation of the board on the terminal
        void setSpaceValue(int row, int column, char playerToken);
        bool isWinner(char playerToken); // Returns true if the player has a winning position
        bool isGameTied();
        vector<vector<int>> getPossibleMoves(vector<vector<int>> movesMade); // Returns a vector with the possible moves given the current state of the board
        vector<int> getHorizontalReflectionMove(vector<int> move, vector<vector<int>> movesMade);
        vector<int> getVerticalReflectionMove(vector<int> move, vector<vector<int>> movesMade);
        vector<int> getOppositeCornerMove(vector<int> move, vector<vector<int>> movesMade);
        vector<int> getInteriorReflectionMoveOne(vector<int> move, vector<vector<int>> movesMade);
        vector<int> getInteriorReflectionMoveTwo(vector<int> move, vector<vector<int>> movesMade);
        int getGameResultForComputer(vector<vector<int>> movesMade);

    private:
        int rows = 3;
        int columns = 3;
        vector<vector<Space*>> board;
        /*
        1 = User
        2 = Computer
        */
        int whoGoesFirst;
        int winningCombinations[8][3][2] = {{{0, 0}, {0, 1}, {0, 2}}, 
                                            {{1, 0}, {1, 1}, {1, 2}},
                                            {{2, 0}, {2, 1}, {2, 2}},
                                            {{0, 0}, {1, 0}, {2, 0}},
                                            {{0, 1}, {2, 1}, {2, 1}},
                                            {{0, 2}, {1, 2}, {2, 2}},
                                            {{0, 0}, {1, 1}, {2, 2}},
                                            {{2, 2}, {1, 1}, {0, 2}}};

        void initalizeBoard();
        bool moveInMoveList(int row, int column, vector<vector<int>> moveList);
        void resetBoard(vector<vector<int>> movesMadeByWho);
};

#endif