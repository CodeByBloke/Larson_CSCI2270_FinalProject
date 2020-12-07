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
    vector<Move*> children;

    Move(int moveRow, int moveColumn, Move* moveParent, vector<Move*> moveChildren) {
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

        vector<int> makeBestMove();
    private:
        Move* root;
        Board* board;

        void fillTree(Move* lastMove);
        vector<vector<int>> getMovesMade(Move* moveInTree);
        vector<vector<int>> getMovesMadeByWho(Move* moveInTree);
        vector<vector<int>> narrowMoveList(vector<vector<int>> possibleMoves, vector<vector<int>> movesMade);
        vector<vector<int>> getSimilarMoves(vector<int> move, vector<vector<int>> movesMade);
        void assignVictoryToMove(Move* move);
        int countGames(Move* move);
        void compressTree(Move* currentMove);
};

class AI {
    public:
        AI() {};
        AI(Board* board);

        vector<int> makeMove();
    private:
        Board* board;
        Move_Tree moveTree;

        void buildMoveTree();
};

#endif