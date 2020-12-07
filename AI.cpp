#include <iostream>
#include <vector>
#include "AI.h"

using namespace std;

Move_Tree::Move_Tree(Board* currentBoard) {
    board = currentBoard;
    vector<Move*> rootChildren;
    root = new Move(-1, -1, nullptr, rootChildren);
    root->whoseMove = 1;
    fillTree(root);
    compressTree(root);
}

void Move_Tree::compressTree(Move* currentMove) {
    if(currentMove->children.size() == 0) {
        return;
    } 

    if(currentMove->gameResult == -1) {
        int gameResult = -1;
        for(int i = 0; i < currentMove->children.size(); ++i) {
            Move* nextMove = currentMove->children[i];
            if(nextMove->gameResult == -1) {
                compressTree(nextMove);
            }

            if(nextMove->gameResult > gameResult && currentMove->whoseMove == 1) {
                gameResult = nextMove->gameResult;
            }
        }
        currentMove->gameResult = gameResult;
    }

    return;
}

void Move_Tree::fillTree(Move* lastMove) {
    vector<vector<int>> movesMade = getMovesMade(lastMove);
    vector<vector<int>> allPossibleMoves = board->getPossibleMoves(movesMade);
    vector<vector<int>> possibleMoves = narrowMoveList(allPossibleMoves, movesMade);

    if(possibleMoves.size() == 0) {
        return;
    }

    for(int i = 0; i < possibleMoves.size(); ++i) {
        vector<Move*> moveChildren;
        Move* newMove = new Move(possibleMoves[i][0], possibleMoves[i][1], lastMove, moveChildren);
        if(newMove->parent->whoseMove == 0) {
            newMove->whoseMove = 1;
        } else if(newMove->parent->whoseMove == 1) {
            newMove->whoseMove = 0;
        }
        
        assignVictoryToMove(newMove);
        lastMove->children.push_back(newMove);

        if(newMove->gameResult == -1) {
            fillTree(newMove);
        } else {
            return;
        }
    }
}

void Move_Tree::assignVictoryToMove(Move* move) {
    vector<vector<int>> movesMadeByWho = getMovesMadeByWho(move);
    int gameResult = board->getGameResultForComputer(movesMadeByWho);
    move->gameResult = gameResult;
}

vector<vector<int>> Move_Tree::getMovesMadeByWho(Move* moveInTree) {
    vector<vector<int>> movesMade;
    while(moveInTree->parent != nullptr) {
        vector<int> move;
        move.push_back(moveInTree->row);
        move.push_back(moveInTree->column);
        move.push_back(moveInTree->whoseMove);
        movesMade.push_back(move);
        moveInTree = moveInTree->parent;
    }

    return movesMade;
}

vector<vector<int>> Move_Tree::getMovesMade(Move* moveInTree) {
    vector<vector<int>> movesMade;
    while(moveInTree->parent != nullptr) {
        vector<int> move;
        move.push_back(moveInTree->row);
        move.push_back(moveInTree->column);
        movesMade.push_back(move);
        moveInTree = moveInTree->parent;
    }

    return movesMade;
}

vector<vector<int>> Move_Tree::narrowMoveList(vector<vector<int>> possibleMoves, vector<vector<int>> movesMade) {
    vector<vector<int>> narrowedMoveList;
    vector<vector<int>> seenMoves;

    for(int i = 0; i < possibleMoves.size(); ++i) {
        vector<int> move = possibleMoves[i];

        bool isNewMove = true;
        for(int j = 0; j < seenMoves.size(); ++j) {
            vector<int> seenMove = seenMoves[j];
            if(move[0] == seenMove[0] && move[1] == seenMove[1]) {
                isNewMove = false;
                break;
            }
        }

        if(isNewMove) {
            narrowedMoveList.push_back(move);
            vector<vector<int>> similarMoves = getSimilarMoves(move, movesMade);
            for(int j = 0; j < similarMoves.size(); ++j) {
                seenMoves.push_back(similarMoves[j]);
            }
        }
    }

    return narrowedMoveList;
}

vector<vector<int>> Move_Tree::getSimilarMoves(vector<int> move, vector<vector<int>> movesMade) {
    vector<vector<int>> similarMoves;
    vector<int> horizontalReflectionMove = board->getHorizontalReflectionMove(move, movesMade);
    vector<int> verticalReflectionMove = board->getVerticalReflectionMove(move, movesMade);
    vector<int> oppositeCornerMove = board->getOppositeCornerMove(move, movesMade);
    vector<int> interiorReflectionMoveOne = board->getInteriorReflectionMoveOne(move, movesMade);
    vector<int> interiorReflectionMoveTwo = board->getInteriorReflectionMoveTwo(move, movesMade);

    if(horizontalReflectionMove.size() != 0) {
        similarMoves.push_back(horizontalReflectionMove);
    }

    if(verticalReflectionMove.size() != 0) {
        similarMoves.push_back(verticalReflectionMove);
    }

    if(oppositeCornerMove.size() != 0) {
        similarMoves.push_back(oppositeCornerMove);
    }

    if(interiorReflectionMoveOne.size() != 0) {
        similarMoves.push_back(interiorReflectionMoveOne);
    }

    if(interiorReflectionMoveTwo.size() != 0) {
        similarMoves.push_back(interiorReflectionMoveTwo);
    }

    return similarMoves;
}

int Move_Tree::countGames(Move* move) {
    int count = 1;
    if(move->children.size() != 0) {
        for(int i = 0; i < move->children.size(); ++i) {
            count+= countGames(move->children[i]);
        }
    }

    return count;
}

AI::AI(Board* initialBoard) {
    board = initialBoard;
}

vector<int> AI::makeMove() {
    moveTree = Move_Tree(board);
    vector<int> move = moveTree.makeBestMove();
    return move;
}

void AI::buildMoveTree() {
    moveTree = Move_Tree(board);
}

vector<int> Move_Tree::makeBestMove() {
    vector<int> move;
    vector<Move*> possibleMoves = root->children;
    for(int i = 0; i < possibleMoves.size(); ++i) {
        if(possibleMoves[i]->gameResult == 0) {
            move.push_back(possibleMoves[i]->row);
            move.push_back(possibleMoves[i]->column);
            return move;
        }
    }

    for(int i = 0; i < possibleMoves.size(); ++i) {
        if(possibleMoves[i]->gameResult == -1) {
            move.push_back(possibleMoves[i]->row);
            move.push_back(possibleMoves[i]->column);
            return move;
        }
    }

    for(int i = 0; i < possibleMoves.size(); ++i) {
        if(possibleMoves[i]->gameResult == 1) {
            move.push_back(possibleMoves[i]->row);
            move.push_back(possibleMoves[i]->column);
            return move;
        }
    }

    for(int i = 0; i < possibleMoves.size(); ++i) {
        if(possibleMoves[i]->gameResult == 2) {
            move.push_back(possibleMoves[i]->row);
            move.push_back(possibleMoves[i]->column);
            return move;
        }
    }

    move.push_back(possibleMoves[0]->row);
    move.push_back(possibleMoves[0]->column);
    return move;
}