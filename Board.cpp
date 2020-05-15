#include "Board.h"


Board::Board(Color playerColor) {
    player = playerColor;
    turn = black;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = 0;
    playOneMove(3, 4, vector<int>());
    playOneMove(4, 4, vector<int>());
    playOneMove(4, 3, vector<int>());
    playOneMove(3, 3, vector<int>());
}

void Board::playOneMove(const int &x, const int &y) {
    const vector<int> &a = possiblePlace(x, y, turn);
    if (!a.empty())
        playOneMove(x, y, a);
    else
        cout << "position incorrecte" << endl;
}

void Board::playOneMove(const int &x, const int &y, const vector<int> &dirs) {
    for (int dir : dirs) {
        auto coord = make_pair(x, y);
        for (int i = 0; i < size; i++) {
            switch (dir) {
                case 1:
                case 2:
                case 3:
                    coord.second--;
                    break;
                case 5:
                case 6:
                case 7:
                    coord.second++;
                    break;
                default:
                    break;
            }
            switch (dir) {
                case 1:
                case 8:
                case 7:
                    coord.first--;
                    break;
                case 3:
                case 4:
                case 5:
                    coord.first++;
                    break;
                default:
                    break;
            }
            if (board[coord.first][coord.second] != turn)
                board[coord.first][coord.second] = turn;
            else
                break;
        }
    }
    if (turn == white) {
        board[x][y] = white;
        turn = black;
    } else {
        board[x][y] = black;
        turn = white;
    }
}

void Board::askMove() {
    int x;
    int y;
    cin >> x >> y;
    playOneMove(x, y);
}

void Board::changeTurn() {
    if (turn == white) turn = black; else turn = white;
}

bool Board::isOver() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == 0)
                return false;
    return true;
}

std::vector<std::tuple<int, int, vector<int>>> Board::nextMoves() {
    auto res = vector<std::tuple<int, int, vector<int>>>();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            vector<int> nb = possiblePlace(i, j, turn);
            if (!nb.empty()) {
                tuple<int, int, vector<int>> a = make_tuple(i, j, nb);
                res.push_back(a);
            }
        }
    }
    return res;
}

int Board::score(Color color) {
    int score = 0;
    Color other;
    if (color == white)
        other = black;
    else
        other = white;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (color == board[i][j])
                score++;
            else if (other == board[i][j])
                score--;
    return score;
}

bool Board::hasWon() {
    return score(player) > 0;
}

Color Board::getPlayer() const {
    return player;
}

Color Board::getTurn() const {
    return turn;
}

vector<int> Board::possiblePlace(const int &x, const int &y, Color color) {
    vector<int> res = vector<int>();
    if (x < 0 || y < 0 || x >= size || y >= size || board[x][y] != 0)
        return res;
    Color other;
    if (color == white) {
        other = black;
    } else {
        other = white;
    }

    if (x + 1 < size && y + 1 < size && board[x + 1][y + 1] == other) {
        for (int i = 2; x + i < size && y + i < size; i++) {
            if (board[x + i][y + i] == color)
                res.push_back(5);
        }
    }
    if (y + 1 < size && board[x][y + 1] == other) {
        for (int i = 2; y + i < size; i++) {
            if (board[x][y + i] == color)
                res.push_back(6);
        }
    }
    if (x + 1 < size && board[x + 1][y] == other) {
        for (int i = 2; x + i < size; i++) {
            if (board[x + i][y] == color)
                res.push_back(4);
        }
    }
    if (x - 1 >= 0 && y + 1 < size && board[x - 1][y + 1] == other) {
        for (int i = 2; x - i >= 0 && y + i < size; i++) {
            if (board[x - i][y + i] == color)
                res.push_back(7);
        }
    }
    if (x + 1 < size && y - 1 >= 0 && board[x + 1][y - 1] == other) {
        for (int i = 2; x + i < size && y - i >= 0; i++) {
            if (board[x + i][y - i] == color)
                res.push_back(3);
        }
    }
    if (x - 1 >= 0 && board[x - 1][y] == other) {
        for (int i = 2; x - i >= 0; i++) {
            if (board[x - i][y] == color)
                res.push_back(8);
        }
    }
    if (y - 1 >= 0 && board[x][y - 1] == other) {
        for (int i = 2; y - i >= 0; i++) {
            if (board[x][y - i] == color)
                res.push_back(2);
        }
    }
    if (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] == other) {
        for (int i = 2; x - i >= 0 && y - i >= 0; i++) {
            if (board[x - i][y - i] == color)
                res.push_back(1);
        }
    }
    return res;
}

void Board::printBoard() const {
    std::string res;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
//            cout << endl << i << " " << j << " :";
            std::cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
