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
    vector<Coordinate> actions;
    while (!board.isOver()) {
        board.printBoard();
        a = board.nextMoves();
        if (!a.empty()) {
            if (board.getTurn() == board.getPlayer()) {
                board.askMove();
//                pair<int, int> move = ai0.minmax_old(board);
//                board.playOneMove(move.first, move.second);
            } else {
                int conf = ai1.alpha_beta(board.clone(), actions);
                cout << "move: " << actions.front().x << " " << actions.front().y << endl;
                cout << "confidence: " << conf << endl;
                if (actions.size() > 1)
                    cout << "expected move: " << actions[1].x << " " << actions[1].y << endl;
                board.playOneMove(actions.front().x, actions.front().y);
            }
        } else {
            cout << "passed" << endl;
            board.changeTurn();
        }
    }
    cout << board.hasWon() << endl;
    board.printBoard();
    /*  Board board(black);
      for (auto &i : board.board)
          for (int &j : i)
              j = 0;
      board.board[0][0] = 1;
      board.printBoard();
      cout << "heur: " << board.heuristic(black) << endl;*/
    return 0;
}
