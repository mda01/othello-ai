#ifndef OTHELLO_AI_H
#define OTHELLO_AI_H


#include "Board.h"

#define MAX_DEPTH 8

class AI {
private:
    int alpha, beta;
    Color aiColor;

public:
    explicit AI(Color color);

    pair<int, int> minmax(Board initBoard);

    int minmaxRec(Board node, int depth, bool maximizingPlayer, bool previousPass);
};


#endif //OTHELLO_AI_H
