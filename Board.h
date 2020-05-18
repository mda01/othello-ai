#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <tuple>

#define SIZE 8
using namespace std;

enum Color {
    white = 1, black = 2, undefined = -1
};

class Board {

private:
    int board[8][8]{};
    int heuristicBoard[SIZE][SIZE] = {
            {410, 23,  13,  8,   8,   13,  23,  410},
            {23,  -75, -22, -51, -51, -22, -75, 23},
            {13,  -22, 41,  3,   3,   41,  -22, 13},
            {8,   -51, 3,   -87, -87, 3,   -51, 8},
            {8,   -51, 3,   -87, -87, 3,   -51, 8},
            {13,  -22, 41,  3,   3,   41,  -22, 13},
            {23,  -75, -22, -51, -51, -22, -75, 23},
            {410, 23,  13,  8,   8,   13,  23,  410}
    };
    Color player;
    Color turn;
public:
    explicit Board(Color playerColor);

    Board();

    void playOneMove(const int &x, const int &y);

    void playOneMove(const int &x, const int &y, const vector<int> &dirs);

    void askMove();

    void changeTurn();

    bool isOver();

    int heuristic(Color color);

    int score(Color color);

    bool hasWon();

    Color getPlayer() const;

    Color getTurn() const;

    int getValue(const int &x, const int &y) const;

    vector<int> possiblePlace(const int &x, const int &y, Color color);

    vector<std::tuple<int, int, vector<int>>> nextMoves();

    vector<Board> children();

    void printBoard() const;

    Board clone();


};


#endif //OTHELLO_BOARD_H
