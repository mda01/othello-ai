#ifndef OTHELLO_MINMAX_H
#define OTHELLO_MINMAX_H


#include "Board.h"

#define MAX_DEPTH 10


class MinMax {
private:
    Color aiColor;

public:
    /**
     * Creates a minmax AI, that maximise the @param color score
     * @param color the player we want to maximise
     */
    explicit MinMax(Color color);

    /**
     * Starts the minmax algorithm and uses alpha beta pruning, from a @param state, and memorises the best path into @param actions
     * @param state the initial state
     * @param actions the path
     * @return the confidence of the AI as int
     */
    int alpha_beta(Board state, vector<Coordinate> &actions) const;

    /**
     * Tries to maximize the score
     * @param state initial state
     * @param alpha alpha bound
     * @param beta beta bound
     * @param actions best path
     * @param depth how far we can explore from this state
     * @return the confidence of the AI as int
     */
    int max_value(Board state, int alpha, int beta, vector<Coordinate> &actions, int depth) const;

    /**
     * Tries to minimize the score
     * @param state initial state
     * @param alpha alpha bound
     * @param beta beta bound
     * @param actions best path
     * @param depth how far we can explore from this state
     * @return the confidence of the AI as int
     */
    int min_value(Board state, int alpha, int beta, vector<Coordinate> &actions, int depth) const;

};


#endif //OTHELLO_MINMAX_H
