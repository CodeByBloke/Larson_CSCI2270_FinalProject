# Larson_CSCI2270_FinalProject

Project Summary:
This is a program to play against the AI in Tic-Tac-Toe. The game has a main menu and one difficulty. The computer is designed so that it can not be beat, howver you can tie it.
The AI works by generating a move tree each turn with all the possible moves. This tree would normally have hundres of thousands of moves, but this number is reduced significantly by pruning for duplicate and similar moves. The AI then assigns a value to each of the moves that result in some ort of end game condition (win, lose, tie) and uses these values to generate values for moves that get to those final moves. The board is stored in a 2D vector. The Tic-Tac-Toe board is drawn each turn and the program gets user input to place the user's token. 

How To Run:
1. Download the files
2. Type g++ -std=c++11 -o run main.cpp in the terminal
3. Type ./run in the terminal
4. Follow the instructions printed in the main menu

Dependencies:
None

System Requirements:
Definitely works on Windows 10, and it should work on other opperating systems

Team Members:
Blake Larson

Contributors:
Some Wiiki posts and Youtube!

Open Issues:
You can break the game by typign errant inputs. If you follow the instructions thought there are no known bugs.


