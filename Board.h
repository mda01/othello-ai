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
    /**
     * Creates a Board, where the player 1 (referred as player) plays the @param playerColor color
     * @param playerColor the color of player
     */
    explicit Board(Color playerColor);

    /**
     * Creates a Board, where the player 1 (referred as player) plays the black
     */
    Board();

    /**
     * Puts the 4 first pieces on the Board
     */
    void initBoard();

    /**
     * Put a piece of a given player on the Board, at the position @param c, and changes turn
     * @param c the position of the piece
     */
    void playOneMove(const Coordinate &c);

    /**
     * Put a piece of a given player on the Board, at the position @param c, and changes turn
     * @param c the position of the piece
     * @param dirs the direction of capture (to fasten calculations)
     */
    void playOneMove(const Coordinate &c, const vector<int> &dirs);

    /**
     * Prompts a move, so a human can enter coordinates
     */
    void askMove();

    /**
     * Changes the turn
     */
    void changeTurn();

    /**
     * Checks if the game is over, i.e. there is one color left or no one can play. The first condition implies the second one, so only the possible places is checked
     * @return true if the game is over, else false
     */
    bool isOver() const;

    /**
     * Returns the value of a board, from the @param color point of view
     * @param color the player whom the heuristic is calculated
     * @return the heuristic of the Board as int
     */
    int heuristic(Color color) const;

    /**
     * Returns the value of a Board, when a game is over, from the @param color point of view
     * @param color the player whom the color is calculated
     * @return the score of the Board as int
     */
    int score(Color color) const;

    /**
     * Checks if the player has won
     * @return true if the game is over and player has won
     */
    bool hasWon() const;

    /**
     * @return the player's color
     */
    Color getPlayer() const;

    /**
     * @return the color of the player that will play
     */
    Color getTurn() const;

    /**
     * Checks if a place is suitable to put a piece of the color @param color at the coordinate @param c
     * @param c the coordinate that is checked
     * @param color the color of the piece
     * @return all the directions where the piece can capture, if capture is possible
     */
    vector<int> possiblePlace(const Coordinate &c, Color color) const;

    /**
     * Get the next possible positions for the player turn
     * @return a vector of all possible positions
     */
    vector<std::pair<Coordinate, vector<int>>> nextMoves() const;

    /**
     * Get the next states using possiblePlace
     * @return a vector of states
     */
    vector<Node> children() const;

    /**
     * Prints the Board in the console
     */
    void printBoard() const;

    /**
     * Clones the Board
     * @return
     */
    Board clone() const;


};


struct Node {
    Board board;
    Coordinate coordinate{};
};

#endif //OTHELLO_BOARD_H
