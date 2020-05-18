#include "Board.h"

Board::Board() {
    player = black;
    turn = black;
    for (auto &i : board)
        for (int &j : i)
            j = 0;
    playOneMove(3, 4, vector<int>());
    playOneMove(4, 4, vector<int>());
    playOneMove(4, 3, vector<int>());
    playOneMove(3, 3, vector<int>());
}

Board::Board(Color playerColor) {
    player = playerColor;
    turn = black;
    for (auto &i : board)
        for (int &j : i)
            j = 0;
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
        cout << "Incorrect position: " << x << " " << y << endl;
}

void Board::playOneMove(const int &x, const int &y, const vector<int> &dirs) {
    for (int dir : dirs) {
        auto coord = make_pair(x, y);
        for (int i = 0; i < SIZE; i++) {
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
            if (board[coord.first][coord.second] == 0) {
                cout << "incorrect piece was allowed but filling is somehow incorrect" << endl;
                exit(789);
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
    int x = 0;
    int y = 0;
    cin >> x >> y;
    playOneMove(x, y);
}

void Board::changeTurn() {
    if (turn == white) turn = black; else turn = white;
}

bool Board::isOver() {
    Color other;
    other = turn == white ? black : white;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (!possiblePlace(i, j, turn).empty() or !(possiblePlace(i, j, other).empty()))
                return false;
    return true;
}

std::vector<std::tuple<int, int, vector<int>>> Board::nextMoves() {
    auto res = vector<std::tuple<int, int, vector<int>>>();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            vector<int> nb = possiblePlace(i, j, turn);
            if (!nb.empty()) {
                tuple<int, int, vector<int>> a = make_tuple(i, j, nb);
                res.push_back(a);
            }
        }
    }
    return res;
}

int Board::heuristic(Color color) {
    int h = 0;
    Color other;
    if (color == white)
        other = black;
    else
        other = white;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (color == board[i][j]) {
                h += heuristicBoard[i][j];
            } else if (other == board[i][j]) {
                h -= heuristicBoard[i][j];
            }
        }
    }
    return h;
}

int Board::score(Color color) {
    int score = 0;
    Color other;
    if (color == white)
        other = black;
    else
        other = white;
    for (auto &row : board)
        for (int cell : row)
            if (cell == color)
                score++;
            else if (cell == other)
                score--;
    return score * 100;
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

int Board::getValue(const int &x, const int &y) const {
    return board[x][y];
}

vector<int> Board::possiblePlace(const int &x, const int &y, Color color) {
    vector<int> res = vector<int>();
    if (x < 0 || y < 0 || x >= SIZE || y >= SIZE || board[x][y] != 0)
        return res;
    Color other;
    if (color == white) {
        other = black;
    } else {
        other = white;
    }

    if (x + 1 < SIZE && y + 1 < SIZE && board[x + 1][y + 1] == other) {
        for (int i = 2; x + i < SIZE && y + i < SIZE; i++) {
            if (board[x + i][y + i] == 0)
                break;
            if (board[x + i][y + i] == color)
                res.push_back(5);
        }
    }
    if (y + 1 < SIZE && board[x][y + 1] == other) {
        for (int i = 2; y + i < SIZE; i++) {
            if (board[x][y + i] == 0)
                break;
            if (board[x][y + i] == color)
                res.push_back(6);
        }
    }
    if (x + 1 < SIZE && board[x + 1][y] == other) {
        for (int i = 2; x + i < SIZE; i++) {
            if (board[x + i][y] == 0)
                break;
            if (board[x + i][y] == color)
                res.push_back(4);
        }
    }
    if (x - 1 >= 0 && y + 1 < SIZE && board[x - 1][y + 1] == other) {
        for (int i = 2; x - i >= 0 && y + i < SIZE; i++) {
            if (board[x - i][y + i] == 0)
                break;
            if (board[x - i][y + i] == color)
                res.push_back(7);
        }
    }
    if (x + 1 < SIZE && y - 1 >= 0 && board[x + 1][y - 1] == other) {
        for (int i = 2; x + i < SIZE && y - i >= 0; i++) {
            if (board[x + i][y - i] == 0)
                break;
            if (board[x + i][y - i] == color)
                res.push_back(3);
        }
    }
    if (x - 1 >= 0 && board[x - 1][y] == other) {
        for (int i = 2; x - i >= 0; i++) {
            if (board[x - i][y] == 0)
                break;
            if (board[x - i][y] == color)
                res.push_back(8);
        }
    }
    if (y - 1 >= 0 && board[x][y - 1] == other) {
        for (int i = 2; y - i >= 0; i++) {
            if (board[x][y - i] == 0)
                break;
            if (board[x][y - i] == color)
                res.push_back(2);
        }
    }
    if (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] == other) {
        for (int i = 2; x - i >= 0 && y - i >= 0; i++) {
            if (board[x - i][y - i] == 0)
                break;
            if (board[x - i][y - i] == color)
                res.push_back(1);
        }
    }
    return res;
}

vector<Node> Board::children() {
    vector<Node> res;
    auto moves = nextMoves();
    for (std::tuple<int, int, vector<int>> move : moves) {
        Board child = clone();
        Coordinate c{get<0>(move), get<1>(move)};
        child.playOneMove(c.x, c.y, get<2>(move));
        res.push_back(Node{child, c});
    }
    return res;
}

void Board::printBoard() const {
    std::string res;
    cout << "  y\t";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl << "x" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
//            cout << endl << i << " " << j << " :";
            if (j == 0) cout << i << "\t";
            switch (board[i][j]) {
                case white:
                    cout << "W" << " ";
                    break;
                case black:
                    cout << "B" << " ";
                    break;
                default:
                    cout << "-" << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


Board Board::clone() {
    Board b(player);
    b.turn = turn;
    b.player = player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            b.board[i][j] = board[i][j];
        }
    }
    return b;
}
