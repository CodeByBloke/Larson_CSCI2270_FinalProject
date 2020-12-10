#include <iostream>
#include <vector>
#include "AI.h"

using namespace std;

Move_Tree::Move_Tree(Board* currentBoard) { 
    board = currentBoard;
    vector<Move*> rootChildren; 
    root = new Move(-1, -1, nullptr, rootChildren); // Make the root node in the tree
    root->whoseMove = 1;
    fillTree(root);
    compressTree(root);
}

void Move_Tree::compressTree(Move* currentMove) {
    if(currentMove->children.size() == 0) { // This means you have reached the bottom of the tree
        return;
    } 

    if(currentMove->gameResult == -1) { // If the current move does not have a game result then execute the following code
        int gameResult = -1;
        bool userCanWin = false;
        bool userCanTie = false;
        bool computerCanWin = false;
        bool computerCanTie = false;
        for(int i = 0; i < currentMove->children.size(); ++i) { // Loop through each child move of the current move
            Move* nextMove = currentMove->children[i];
            if(nextMove->gameResult == -1) { // Recursively call this function if the child move does not have a game result
                compressTree(nextMove);
            }

            // Execute a series of checks to determine the current move's game result based on its children's game results
            if(nextMove->gameResult == 2) {
                userCanWin = true;
            } 

            if(nextMove->gameResult == 0) {
                computerCanWin = true;
            }

            if(nextMove->whoseMove == 0 && (nextMove->gameResult == 1 || nextMove->gameResult == -1)) {
                computerCanTie = true;
            }

            if(nextMove->whoseMove == 1 && (nextMove->gameResult == 1 || nextMove->gameResult == -1)) {
                userCanTie = true;
            }
        }

        if(currentMove->whoseMove == 0) {
            if(computerCanWin && !userCanTie) {
                gameResult = 0;
            } 

            if(userCanWin) {
                gameResult = 2;
            }
        }

        if(currentMove->whoseMove == 1) {
            if(userCanWin && !computerCanTie) {
                gameResult = 2;
            }

            if(computerCanWin) {
                gameResult = 0;
            }
        }

        currentMove->gameResult = gameResult; // Set the current move's game result to the value calculated above
    }

    return;
}

void Move_Tree::fillTree(Move* lastMove) {
    vector<vector<int>> movesMade = getMovesMade(lastMove); // Get a list of the moves made to get to this current move
    vector<vector<int>> allPossibleMoves = board->getPossibleMoves(movesMade); // Get a list of all of the possible moves from the current position
    vector<vector<int>> possibleMoves = narrowMoveList(allPossibleMoves, movesMade); // Reduce this list to make the AI's time easier

    if(possibleMoves.size() == 0) {
        return;
    }

    for(int i = 0; i < possibleMoves.size(); ++i) { // Loop through the moves in the possible move list
        vector<Move*> moveChildren;
        Move* newMove = new Move(possibleMoves[i][0], possibleMoves[i][1], lastMove, moveChildren); // Create a new move
        if(newMove->parent->whoseMove == 0) {
            newMove->whoseMove = 1;
        } else if(newMove->parent->whoseMove == 1) {
            newMove->whoseMove = 0;
        }
        
        lastMove->children.push_back(newMove);
        assignVictoryToMove(newMove);

        if(newMove->gameResult == -1) {
            fillTree(newMove); // If this move does not result in a win, loss, or tie recursively call the function
        } else {
            return;
        }
    }
}

void Move_Tree::assignVictoryToMove(Move* move) {
    vector<vector<int>> movesMadeByWho = getMovesMadeByWho(move);
    int gameResult = board->getGameResultForComputer(movesMadeByWho); // Determine if a move has a game conclusion 
    move->gameResult = gameResult;
}

vector<vector<int>> Move_Tree::getMovesMadeByWho(Move* moveInTree) {
    vector<vector<int>> movesMade;
    while(moveInTree->parent != nullptr) { // Follow the move's parents until the root move is reached
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
    while(moveInTree->parent != nullptr) { // Follow the move's parents until the root move is reached
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

    for(int i = 0; i < possibleMoves.size(); ++i) { // Loop through the possible moves
        vector<int> move = possibleMoves[i];

        bool isNewMove = true; // Condition to determine if the move is unique
        for(int j = 0; j < seenMoves.size(); ++j) { // Loop though the list of seen moves
            vector<int> seenMove = seenMoves[j];
            if(move[0] == seenMove[0] && move[1] == seenMove[1]) { // If the move has already been seen then change the isNewMove variable to false
                isNewMove = false;
                break;
            }
        }

        if(isNewMove) {
            narrowedMoveList.push_back(move); // Add the unique move to the list
            vector<vector<int>> similarMoves = getSimilarMoves(move, movesMade); // Get similar moves
            for(int j = 0; j < similarMoves.size(); ++j) { // Add the similar moves to the seen moves list
                seenMoves.push_back(similarMoves[j]);
            }
        }
    }

    return narrowedMoveList;
}

vector<vector<int>> Move_Tree::getSimilarMoves(vector<int> move, vector<vector<int>> movesMade) {
    vector<vector<int>> similarMoves;
    vector<int> horizontalReflectionMove = board->getHorizontalReflectionMove(move, movesMade); // Get the horizontal reflection move
    vector<int> verticalReflectionMove = board->getVerticalReflectionMove(move, movesMade); // Get the vertical reflection move
    vector<int> oppositeCornerMove = board->getOppositeCornerMove(move, movesMade); // Get the opposite corner move
    vector<int> interiorReflectionMoveOne = board->getInteriorReflectionMoveOne(move, movesMade); // Get the interior reflection move
    vector<int> interiorReflectionMoveTwo = board->getInteriorReflectionMoveTwo(move, movesMade); // Get the second interior reflection move

    // If these moves exist add them to the similar moves list
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
            count+= countGames(move->children[i]); // Add to the count for every move encountered in the tree
        }
    }

    return count;
}

AI::AI(Board* initialBoard) {
    board = initialBoard;
}

vector<int> AI::makeMove() {
    moveTree = Move_Tree(board);
    vector<int> move = moveTree.makeBestMove(); // Get the best move from the tree
    return move;
}

void AI::buildMoveTree() {
    moveTree = Move_Tree(board);
}

vector<int> Move_Tree::makeBestMove() {
    vector<int> move;
    vector<Move*> possibleMoves = root->children;
 
    for(int i = 0; i < possibleMoves.size(); ++i) { // First check to see if there is a move that results in a win
        if(possibleMoves[i]->gameResult == 0 || (possibleMoves[i]->row == 1 && possibleMoves[i]->column == 1)) {
            move.push_back(possibleMoves[i]->row);
            move.push_back(possibleMoves[i]->column);
            return move;
        }
    }

    for(int i = 0; i < possibleMoves.size(); ++i) { // Check to see if there is a move that results in an undecided result
        if(possibleMoves[i]->gameResult == -1) {
            move.push_back(possibleMoves[i]->row);
            move.push_back(possibleMoves[i]->column);
            return move;
        }
    }

    for(int i = 0; i < possibleMoves.size(); ++i) { // Check to see if there is a move that results in a tie
        if(possibleMoves[i]->gameResult == 1) {
            move.push_back(possibleMoves[i]->row);
            move.push_back(possibleMoves[i]->column);
            return move;
        }
    }

    for(int i = 0; i < possibleMoves.size(); ++i) { // Finally get a move that results in a loss
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
