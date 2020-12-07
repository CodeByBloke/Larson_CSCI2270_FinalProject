#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

Board::Board(int firstPlayer) {
    whoGoesFirst = firstPlayer;
    initalizeBoard();
}

void Board::initalizeBoard() {
    for(int i = 0; i < rows; ++i) {
        vector<Space*> column;
        for(int j = 0; j < columns; ++j) {
            column.push_back(new Space(0));
        }

        board.push_back(column);
    }
}

int Board::getSpaceValue(int row, int column) {
    return board[row][column]->value;
}

char Board::getSpaceCharacter(int row, int column) {
    int value = getSpaceValue(row, column);
    if(value == 0) {
        return '_';
    } else if(value == 1) {
        return 'X';
    } else {
        return 'O';
    }
}

void Board::outputBoard() {
    cout<<"Current Board:"<<endl;
    cout<<" ------------"<<endl;
    cout<<" |   1 2 3  |"<<endl;
    for(int i = 0; i < rows; ++i) {
        cout<<" | ";
        cout<<(i + 1);
        for(int j = 0; j < columns; ++j) {
            cout<<" ";
            cout<<getSpaceCharacter(i, j);
        }
        cout<<"  |"<<endl;
    }
    cout<<" ------------"<<endl;
}

void Board::setSpaceValue(int row, int column, char playerToken) {
    int playerID;
    if(playerToken == 'X') {
        playerID = 1;
    } else if(playerToken == 'O') {
        playerID = 2;
    } else {
        playerID = 0;
    }

    board[row][column]->value = playerID;
}

bool Board::isWinner(char playerToken) {
    int playerID;
    if(playerToken == 'X') {
        playerID = 1;
    } else if(playerToken == 'O') {
        playerID = 2;
    } else {
        return false;
    }

    for(int i = 0; i < 8; ++i) {
        int value1 = board[winningCombinations[i][0][0]][winningCombinations[i][0][1]]->value;
        int value2 = board[winningCombinations[i][1][0]][winningCombinations[i][1][1]]->value;
        int value3 = board[winningCombinations[i][2][0]][winningCombinations[i][2][1]]->value;
        if((playerID == value1) && (playerID == value2) && (playerID == value3)) {
            return true;
        }
    }

    return false;
}

vector<vector<int>> Board::getPossibleMoves(vector<vector<int>> movesMade) {
    vector<vector<int>> possibleMoves; 
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(board[i][j]->value == 0 && !moveInMoveList(i, j, movesMade)) {
                vector<int> move;
                move.push_back(i);
                move.push_back(j);
                possibleMoves.push_back(move);
            }
        }
    }

    return possibleMoves;
}

bool Board::moveInMoveList(int row, int column, vector<vector<int>> moveList) {
    for(int i = 0; i < moveList.size(); ++i) {
        if(row == moveList[i][0] && column == moveList[i][1]) {
            return true;
        }
    }

    return false;
}

vector<int> Board::getHorizontalReflectionMove(vector<int> move, vector<vector<int>> movesMade) {
    if(move[0] == 1) {
        return vector<int>();
    }
    
    if(board[0][0]->value != 0 || board[0][1]->value != 0 || board[0][2]->value != 0 || board[2][0]->value != 0 || board[2][1]->value != 0 || board[2][2]->value != 0) {
        return vector<int>();
    }

    for(int i = 0; i < movesMade.size(); ++i) {
        int row = movesMade[i][0];
        if(row == 0 || row == 2) {
            return vector<int>();
        }
    }

    if(move[0] == 0) {
        vector<int> moveToReturn;
        moveToReturn.push_back(2);
        moveToReturn.push_back(move[1]);
        return moveToReturn;
    } else if(move[0] == 2) {
        vector<int> moveToReturn;
        moveToReturn.push_back(0);
        moveToReturn.push_back(move[1]);
        return moveToReturn;
    }

    return vector<int>();
}

vector<int> Board::getVerticalReflectionMove(vector<int> move, vector<vector<int>> movesMade) {
    if(move[1] == 1) {
        return vector<int>();
    }
    
    if(board[0][0]->value != 0 || board[1][0]->value != 0 || board[2][0]->value != 0 || board[0][2]->value != 0 || board[1][2]->value != 0 || board[2][2]->value != 0) {
        return vector<int>();
    }

    for(int i = 0; i < movesMade.size(); ++i) {
        int column = movesMade[i][1];
        if(column == 0 || column == 2) {
            return vector<int>();
        }
    }

    if(move[1] == 0) {
        vector<int> moveToReturn;
        moveToReturn.push_back(move[0]);
        moveToReturn.push_back(2);
        return moveToReturn;
    } else if(move[1] == 2) {
        vector<int> moveToReturn;
        moveToReturn.push_back(move[0]);
        moveToReturn.push_back(0);
        return moveToReturn;
    }

    return vector<int>();
}

vector<int> Board::getOppositeCornerMove(vector<int> move, vector<vector<int>> movesMade) {
    if(move[0] == 1 || move[1] == 1) {
        return vector<int>();
    }
    
    if(board[0][1]->value != 0 || board[1][0]->value != 0 || board[1][2]->value != 0 || board[2][1]->value != 0) {
        return vector<int>();
    }

    for(int i = 0; i < movesMade.size(); ++i) {
        int row = movesMade[i][0];
        int column = movesMade[i][1];
        if((row == 1 && column != 1) || (column == 1 && row != 1)) {
            return vector<int>();
        }
    }

    if(move[0] == 0 && move[1] == 0) {
        vector<int> moveToReturn;
        moveToReturn.push_back(2);
        moveToReturn.push_back(2);
        return moveToReturn;
    } else if(move[0] == 0 && move[1] == 2) {
        vector<int> moveToReturn;
        moveToReturn.push_back(2);
        moveToReturn.push_back(0);
        return moveToReturn;
    } else if(move[0] == 2 && move[1] == 1) {
        vector<int> moveToReturn;
        moveToReturn.push_back(0);
        moveToReturn.push_back(2);
        return moveToReturn;
    } else if(move[0] == 2 && move[1] == 2) {
        vector<int> moveToReturn;
        moveToReturn.push_back(0);
        moveToReturn.push_back(0);
        return moveToReturn;
    }

    return vector<int>();
}

vector<int> Board::getInteriorReflectionMoveOne(vector<int> move, vector<vector<int>> movesMade) {
    if(move[0] == 0 && move[1] == 1) {
        if(board[0][1]->value != 0 || board[0][2]->value != 0 || board[1][2]->value != 0 || board[1][0]->value != 0 || board[2][0]->value != 0 || board[2][1]->value != 0) {
            return vector<int>();
        }

        for(int i = 0; i < movesMade.size(); ++i) {
            int row = movesMade[i][0];
            int column = movesMade[i][1];
            if(row != column) {
                return vector<int>();
            }
        }

        vector<int> moveToReturn;
        moveToReturn.push_back(1);
        moveToReturn.push_back(0);
        return moveToReturn;
    }

    if(move[0] == 1 && move[1] == 2) {
        if(board[0][1]->value != 0 || board[0][2]->value != 0 || board[1][2]->value != 0 || board[1][0]->value != 0 || board[2][0]->value != 0 || board[2][1]->value != 0) {
            return vector<int>();
        }

        for(int i = 0; i < movesMade.size(); ++i) {
            int row = movesMade[i][0];
            int column = movesMade[i][1];
            if(row != column) {
                return vector<int>();
            }
        }

        vector<int> moveToReturn;
        moveToReturn.push_back(2);
        moveToReturn.push_back(1);
        return moveToReturn;
    }

    return vector<int>();
}

vector<int> Board::getInteriorReflectionMoveTwo(vector<int> move, vector<vector<int>> movesMade) {
    if(move[0] == 0 && move[1] == 1) {
        if(board[0][0]->value != 0 || board[0][1]->value != 0 || board[1][0]->value != 0 || board[1][2]->value != 0 || board[2][1]->value != 0 || board[2][2]->value != 0) {
            return vector<int>();
        }

        for(int i = 0; i < movesMade.size(); ++i) {
            int row = movesMade[i][0];
            int column = movesMade[i][1];
            if(abs(row - column) != 0 || abs(row - column) != 2) {
                return vector<int>();
            }
        }

        vector<int> moveToReturn;
        moveToReturn.push_back(1);
        moveToReturn.push_back(2);
        return moveToReturn;
    }

    if(move[0] == 1 && move[1] == 0) {
        if(board[0][0]->value != 0 || board[0][1]->value != 0 || board[1][0]->value != 0 || board[1][2]->value != 0 || board[2][1]->value != 0 || board[2][2]->value != 0) {
            return vector<int>();
        }

        for(int i = 0; i < movesMade.size(); ++i) {
            int row = movesMade[i][0];
            int column = movesMade[i][1];
            if(abs(row - column) != 0 || abs(row - column) != 2) {
                return vector<int>();
            }
        }

        vector<int> moveToReturn;
        moveToReturn.push_back(2);
        moveToReturn.push_back(1);
        return moveToReturn;
    }

    return vector<int>();
}

int Board::getGameResultForComputer(vector<vector<int>> movesMadeByWho) {
    int totalMovesMade = movesMadeByWho.size();
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(board[i][j]->value != 0) {
                totalMovesMade++;
            }
        }
    }

    if(totalMovesMade < 5) {
        return -1;
    }

    for(int i = 0; i < movesMadeByWho.size(); ++i) {
        if(movesMadeByWho[i][2] == 0) {
            if(whoGoesFirst == 1) {
                setSpaceValue(movesMadeByWho[i][0], movesMadeByWho[i][1], 'O');
            } else {
                setSpaceValue(movesMadeByWho[i][0], movesMadeByWho[i][1], 'X');
            }
        } else if(movesMadeByWho[i][2] == 1) {
            if(whoGoesFirst == 1) {
                setSpaceValue(movesMadeByWho[i][0], movesMadeByWho[i][1], 'X');
            } else {
                setSpaceValue(movesMadeByWho[i][0], movesMadeByWho[i][1], 'O');
            }
        }
    }

    bool computerWon;
    if(whoGoesFirst == 1) {
        computerWon = isWinner('O');
    } else {
        computerWon = isWinner('X');
    }

    if(computerWon) {
        resetBoard(movesMadeByWho);
        return 0;
    }

    bool userWon;
    if(whoGoesFirst == 1) {
        userWon = isWinner('X');
    } else {
        userWon = isWinner('O');
    }

    if(userWon) {
        resetBoard(movesMadeByWho);
        return 2;
    }

    bool isTie = isGameTied();
    if(isTie) {
        resetBoard(movesMadeByWho);
        return 1;
    }

    resetBoard(movesMadeByWho);
    return -1;
}

void Board::resetBoard(vector<vector<int>> movesMadeByWho) {
    for(int i = 0; i < movesMadeByWho.size(); ++i) {
        setSpaceValue(movesMadeByWho[i][0], movesMadeByWho[i][1], ' ');
    }
}

bool Board::isGameTied() {
    int spacesOccupied = 0;
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(board[i][j]->value != 0) {
                spacesOccupied++;
            }
        }
    }

    if(spacesOccupied == 9) {
        return true;
    } 

    return false;
}