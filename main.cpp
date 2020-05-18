#include "Board.h"
#include "MinMax.h"

using namespace std;

int main() {
    int tmp = 0;
    Color playerColor = undefined, enemyColor = undefined;
    while (playerColor != black && playerColor != white) {
        cout << "Choose your color: 0 black, 1 white" << endl;
        cin >> tmp;
        if (tmp == 0) {
            playerColor = black;
            enemyColor = white;
        } else if (tmp == 1) {
            playerColor = white;
            enemyColor = black;
        }
    }
    Board board(playerColor);
//    MinMax ai0 = MinMax(playerColor);
    MinMax ai1 = MinMax(enemyColor);
    vector<std::tuple<int, int, vector<int>>> a;
    while (!board.isOver()) {
        board.printBoard();
        a = board.nextMoves();
        if (!a.empty()) {
            if (board.getTurn() == board.getPlayer()) {
                board.askMove();
//                pair<int, int> move = ai0.minmax(board);
//                board.playOneMove(move.first, move.second);
            } else {
                pair<int, int> move = ai1.minmax(board);
                board.playOneMove(move.first, move.second);
            }
        } else {
            cout << "passed" << endl;
            board.changeTurn();
        }
    }
    cout << board.hasWon() << endl;
    board.printBoard();
    /*  Board b(black);
      for (auto &i : b.board)
          for (int &j : i)
              j = 0;
      b.board[0][0] = 1;
      b.printBoard();
      cout << "heur: " << b.heuristic(black) << endl;*/
    return 0;
}
