#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

Board::Board() {
    cout<<"We good?"<<endl;
    initalizeBoard();
}

void Board::initalizeBoard() {
    // cout<<board[0][0].value<<endl;
    for(int i = 0; i < rows; ++i) {
        vector<Space*> column;
        for(int j = 0; j < columns; ++j) {
            column.push_back(new Space(2));
        }

        board.push_back(column);
    }
}

int Board::outputSpaceValue(int row, int column) {
    return board[row][column]->value;
}