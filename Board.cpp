#include "Board.h"

Board::Board() {
    player = black;
    turn = black;
    initBoard();
}

Board::Board(Color playerColor) {
    player = playerColor;
    turn = black;
    initBoard();
}

void Board::initBoard() {
    for (auto &i : board)
        for (int &j : i)
            j = 0;
    playOneMove({3, 4}, vector<int>());
    playOneMove({4, 4}, vector<int>());
    playOneMove({4, 3}, vector<int>());
    playOneMove({3, 3}, vector<int>());
}

void Board::playOneMove(const Coordinate &c) {
    const vector<int> &a = possiblePlace(c, turn);
    if (!a.empty())
        playOneMove(c, a);
    else
        cout << "Incorrect position: " << c.x << " " << c.y << endl;
}

void Board::playOneMove(const Coordinate &c, const vector<int> &dirs) {
    for (int dir : dirs) {
        auto coord = Coordinate{c.x, c.y};
        for (int i = 0; i < SIZE; i++) {
            switch (dir) {
                case 1:
                case 2:
                case 3:
                    coord.y--;
                    break;
                case 5:
                case 6:
                case 7:
                    coord.y++;
                    break;
                default:
                    break;
            }
            switch (dir) {
                case 1:
                case 8:
                case 7:
                    coord.x--;
                    break;
                case 3:
                case 4:
                case 5:
                    coord.x++;
                    break;
                default:
                    break;
            }
            if (board[coord.x][coord.y] == 0) {
                cout << "incorrect piece was allowed but filling is somehow incorrect" << endl;
                exit(789);
            }
            if (board[coord.x][coord.y] != turn)
                board[coord.x][coord.y] = turn;
            else
                break;
        }
    }
    if (turn == white) {
        board[c.x][c.y] = white;
        turn = black;
    } else {
        board[c.x][c.y] = black;
        turn = white;
    }
}

void Board::askMove() {
    int x = 0;
    int y = 0;
    cin >> x >> y;
    playOneMove(Coordinate{x, y});
}

void Board::changeTurn() {
    if (turn == white) turn = black; else turn = white;
}

bool Board::isOver() const {
    Color other;
    other = turn == white ? black : white;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            Coordinate c = {i, j};
            if (!possiblePlace(c, turn).empty() or !(possiblePlace(c, other).empty()))
                return false;
        }
    return true;
}

std::vector<std::pair<Coordinate, vector<int>>> Board::nextMoves() const {
    auto res = vector<std::pair<Coordinate, vector<int>>>();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            vector<int> nb = possiblePlace({i, j}, turn);
            if (!nb.empty()) {
                pair<Coordinate, vector<int>> a = make_pair(Coordinate{i, j}, nb);
                res.push_back(a);
            }
        }
    }
    return res;
}

int Board::heuristic(const Color color) const {
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

int Board::score(const Color color) const {
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
    return score * 5;
}

bool Board::hasWon() const {
    return score(player) > 0;
}

Color Board::getPlayer() const {
    return player;
}

Color Board::getTurn() const {
    return turn;
}

vector<int> Board::possiblePlace(const Coordinate &c, Color color) const {
    vector<int> res = vector<int>();
    const int x = c.x, y = c.y;
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

vector<Node> Board::children() const {
    vector<Node> res;
    auto moves = nextMoves();
    for (std::pair<Coordinate, vector<int>> move : moves) {
        Board child = clone();
        child.playOneMove(move.first, move.second);
        res.push_back(Node{child, move.first});
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


Board Board::clone() const {
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
