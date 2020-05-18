#ifndef OTHELLO_MINMAX_H
#define OTHELLO_MINMAX_H


#include "Board.h"

#define MAX_DEPTH 10

class MinMax {
private:
    int alpha, beta;
    Color aiColor;

public:
    explicit MinMax(Color color);

    pair<int, int> minmax(Board initBoard);

    int minmaxRec(Board node, int depth, bool maximizingPlayer, bool previousPass);
};


#endif //OTHELLO_MINMAX_H
