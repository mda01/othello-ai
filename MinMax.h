#ifndef OTHELLO_MINMAX_H
#define OTHELLO_MINMAX_H


#include "Board.h"

#define MAX_DEPTH 10


class MinMax {
private:
    Color aiColor;

public:
    explicit MinMax(Color color);

    int alpha_beta(Board state, vector<Coordinate> &actions);

    int max_value(Board state, int alpha, int beta, vector<Coordinate> &actions, int depth) const;

    int min_value(Board state, int alpha, int beta, vector<Coordinate> &actions, int depth) const;

};


#endif //OTHELLO_MINMAX_H
