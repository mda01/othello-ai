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
    int heuristicBoard[SIZE][SIZE] = {
            {500,  -150, 30, 10, 10, 30, -150, 500},
            {-150, -250, 0,  0,  0,  0,  -250, -150},
            {30,   0,    1,  2,  2,  1,  0,    30},
            {10,   0,    2,  16, 16, 2,  0,    10},
            {10,   0,    2,  16, 16, 2,  0,    10},
            {30,   0,    1,  2,  2,  1,  0,    30},
            {-150, -250, 0,  0,  0,  0,  -250, -150},
            {500,  -150, 30, 10, 10, 30, -150, 500},
    };
    Color player;
    Color turn;
public:
    int board[8][8]{};

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
