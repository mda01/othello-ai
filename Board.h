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

struct Coordinate {
    int x;
    int y;
};

class Node;

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

    void initBoard();

    void playOneMove(const Coordinate &c);

    void playOneMove(const Coordinate &c, const vector<int> &dirs);

    void askMove();

    void changeTurn();

    bool isOver() const;

    int heuristic(Color color) const;

    int score(Color color) const;

    bool hasWon() const;

    Color getPlayer() const;

    Color getTurn() const;

    vector<int> possiblePlace(const Coordinate &c, Color color) const;

    vector<std::pair<Coordinate, vector<int>>> nextMoves() const;

    vector<Node> children() const;

    void printBoard() const;

    Board clone() const;


};


struct Node {
    Board board;
    Coordinate coordinate{};
};

#endif //OTHELLO_BOARD_H
