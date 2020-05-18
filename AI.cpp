//
// Created by mdano on 15/05/2020.
//

#include "AI.h"

AI::AI(Color color) {
    alpha = -64;
    beta = 64;
    aiColor = color;
}


int AI::minmaxRec(Board node, int depth, bool maximizingPlayer, bool previousPass) {
    if (node.isOver()) {
        return node.score(node.getTurn());
    }
    if (depth == 0)
        return node.heuristic(node.getTurn());
    vector<Board> children = node.children();
    if (children.empty() && previousPass) { // also game over ? should never end here
        return node.score(node.getTurn());
    } else if (children.empty()) { // handles turn passing
        auto child = node.clone();
        child.changeTurn();
        return minmaxRec(child, depth - 1, !maximizingPlayer, true);
    } else {
        if (maximizingPlayer) {
            int v = -10000; // -inf
            for (Board child : children) {
                v = max(v, minmaxRec(child, depth - 1, false, false));
                if (v > beta)
                    return v;
                alpha = max(alpha, v);
            }
            return v;
        } else {
            int v = 10000; // +inf
            for (Board child : children) {
                v = min(v, minmaxRec(child, depth - 1, true, false));
                if (v < alpha)
                    return v;
                beta = min(beta, v);
            }
            return v;
        }
    }
}

pair<int, int> AI::minmax(Board initBoard) {
    int v = -10000; // -inf
    Board best;
    auto children = initBoard.children();
    for (Board child : children) {
        int minmax = minmaxRec(child, MAX_DEPTH - 1, false, false);
        if (minmax > v) {
            v = minmax;
            best = child.clone();
        }
    }
//    cout << "best :" << endl;
//    best.printBoard();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (initBoard.getValue(i, j) == 0 && best.getValue(i, j) != 0) {
                cout << "estimation: " << v << endl;
                cout << "move: " << i << " " << j << endl;
                return make_pair(i, j);
            }
        }
    }
    exit(666);
}

