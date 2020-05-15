#include "Board.h"

using namespace std;

int main() {
    Board b(black);
    vector<std::tuple<int, int, vector<int>>> a;
    while (!b.isOver()) {
        b.printBoard();
        if (b.getTurn() == b.getPlayer()) {
            b.askMove();
        } else {
            a = b.nextMoves();
            if (!a.empty()) {
                b.playOneMove(get<0>(a[0]), get<1>(a[0]), get<2>(a[0]));
            } else {
                cout << "passed" << endl;
                b.changeTurn();
            }
        }
    }
    cout << b.hasWon() << endl;
    return 0;
}
