#include "MinMax.h"

MinMax::MinMax(Color color) {
    aiColor = color;
}

int MinMax::alpha_beta(Board state, vector<Coordinate> &actions) {
    return max_value(state, INT32_MIN, INT32_MAX, actions, MAX_DEPTH);
}

int MinMax::max_value(Board state, int alpha, int beta, vector<Coordinate> &actions, int depth) const {
    if (state.isOver()) return state.score(aiColor);
    if (depth == 0) return state.heuristic(aiColor);
    auto children = state.children();
    if (children.empty()) { // can't play (specific to othello)
        Board newState = state.clone();
        newState.changeTurn();
        return min_value(newState, alpha, beta, actions, depth - 1);
    }
    int v = INT32_MIN;
    for (Node s : children) {
        vector<Coordinate> tmp;
        int v2 = min_value(s.board, alpha, beta, tmp, depth - 1);
        if (v2 > v) {
            v = v2;
            actions = tmp;
            actions.insert(actions.begin(), s.coordinate);
        }
        if (v >= beta) return v;
        alpha = max(alpha, v);
    }
    return v;
}

int MinMax::min_value(Board state, int alpha, int beta, vector<Coordinate> &actions, int depth) const {
    if (state.isOver()) return state.score(aiColor);
    if (depth == 0) return state.heuristic(aiColor);
    auto children = state.children();
    if (children.empty()) { // can't play (specific to othello)
        Board newState = state.clone();
        newState.changeTurn();
        return max_value(newState, alpha, beta, actions, depth - 1);
    }
    int v = INT32_MAX;
    for (Node s : children) {
        vector<Coordinate> tmp;
        int v2 = max_value(s.board, alpha, beta, tmp, depth - 1);
        if (v2 < v) {
            v = v2;
            actions = tmp;
            actions.insert(actions.begin(), s.coordinate);
        }
        if (v <= alpha) return v;
        beta = min(beta, v);
    }
    return v;
}



