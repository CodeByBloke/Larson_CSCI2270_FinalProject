#ifndef AI_H
#define AI_H

#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

struct Move {
    int row;
    int column;
    
    /*
    -1 = Unknown
    0 = Win
    1 = Tie
    2 = Lose
    */
    int gameResult = -1;

    /*
    0 = Computer
    1 = User
    */
    int whoseMove;
    
    Move* parent;
    vector<Move*> children; // Stores the children moves for this move object

    Move(int moveRow, int moveColumn, Move* moveParent, vector<Move*> moveChildren) { // Constructor
        row = moveRow;
        column = moveColumn;
        parent = moveParent;
        children = moveChildren;
    }
};

class Move_Tree {
    public:
        Move_Tree() {};
        Move_Tree(Board* board);

        vector<int> makeBestMove(); // Returns the best available move for the AI
    private:
        Move* root;
        Board* board;

        void fillTree(Move* lastMove); // This method builds the tree
        vector<vector<int>> getMovesMade(Move* moveInTree); // This returns all of the moves made prior to the move that is passed in
        vector<vector<int>> getMovesMadeByWho(Move* moveInTree); // This returns all of the moves made prior to the move that is passed in and the player who made each move
        vector<vector<int>> narrowMoveList(vector<vector<int>> possibleMoves, vector<vector<int>> movesMade); // This method narrows the list of all possible moves for a given turn
        vector<vector<int>> getSimilarMoves(vector<int> move, vector<vector<int>> movesMade); // This method returns moves that are similar to the passed in move.
        void assignVictoryToMove(Move* move); // This method assigns a end game value to a move
        int countGames(Move* move); // This method counts the number of moves in the tree
        void compressTree(Move* currentMove); // This method determines the end game value for every move in the tree by starting from the bottom of the tree and working up the tree
};

class AI {
    public:
        AI() {};
        AI(Board* board);

        vector<int> makeMove(); // This method is called to get a move from the AI
    private:
        Board* board;
        Move_Tree moveTree;

        void buildMoveTree(); // This method builds a move tree for the current turn
};

#endif
