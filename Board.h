#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <tuple>

using namespace std;

enum Color {
    white = 1, black = 2
};

class Board {

private:
    int size = 8;
    int board[8][8]{};
    Color player;
    Color turn;
public:
    explicit Board(Color playerColor);

    void playOneMove(const int &x, const int &y);

    void playOneMove(const int &x, const int &y, const vector<int> &dirs);

    void askMove();

    void changeTurn();

    bool isOver();

    int score(Color color);

    bool hasWon();

    Color getPlayer() const;

    Color getTurn() const;

    vector<int> possiblePlace(const int &x, const int &y, Color color);

    vector<std::tuple<int, int, vector<int>>> nextMoves();

    void printBoard() const;


};


#endif //OTHELLO_BOARD_H
