#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

using namespace std;

struct Space {
    int value;

    Space(int v) {
        value = v;
    }
};

class Board {
    public:
        Board();

        int outputSpaceValue(int row, int column);

    private:
        int rows = 3;
        int columns = 3;
        vector<vector<Space*>> board;

        void initalizeBoard();

};

#endif