#include "Chess.h"

int Chess::perform(string Move, int board[][8])
{
    int original;
    original = board[Move[2] - 48][Move[3] - 48];
    board[Move[2] - 48][Move[3] - 48] = board[Move[0] - 48][Move[1] - 48];
    board[Move[0] - 48][Move[1] - 48] = 0;
    return original;
}

string Chess::push(int row, int col, int desrow, int descol, int board[][8])
{
    string mystr = to_string(row) + to_string(col) + to_string(desrow) + to_string(descol);
    return mystr;
}

container Chess::getallmoves(bool turn, int board[][8])
{
    int original = 0;
    pseudomoves.clear();
    legal_moves.clear();
    if (turn == true) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (!board[i][j]) continue;
                if (board[i][j] == 1) getpawnmoves(true, i, j, board);
                else if (board[i][j] == 2) getdiagonalmoves(true, i, j, board);
                else if (board[i][j] == 3) getknightmoves(true, i, j, board);
                else if (board[i][j] == 5) getstraigtmoves(true, i, j, board);
                else if (board[i][j] == 6) {
                    getdiagonalmoves(true, i, j, board);
                    getstraigtmoves(true, i, j, board);
                }
                else if (board[i][j] == 10) getkingmoves(true, i, j, board);
            }
        }
        for (string i : pseudomoves) {
            original = perform(i, board);
            if (check(true, board) == false) {
                legal_moves.push_back(i);
            }
            undomove(original, i, board);
        }
    }
    else if (!turn) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (!board[i][j]) continue;
                else if (board[i][j] == -1) {
                    getpawnmoves(false, i, j, board);
                }
                else if (board[i][j] == -2) getdiagonalmoves(false, i, j, board);
                else if (board[i][j] == -3) getknightmoves(false, i, j, board);
                else if (board[i][j] == -5) getstraigtmoves(false, i, j, board);
                else if (board[i][j] == -6) {
                    getdiagonalmoves(false, i, j, board);
                    getstraigtmoves(false, i, j, board);
                }
                else if (board[i][j] == -10) getkingmoves(false, i, j, board);
            }
        }
        for (string i : pseudomoves) {
            original = perform(i, board);
            if (check(false, board) == false) {
                legal_moves.push_back(i);
            }
            undomove(original, i, board);
        }
    }
    return legal_moves;
}

string Chess::computer_move(unsigned short int depth,int board[][8])
{
    cout << "let's begin" << endl;
    string bestmove = miniMaxroot(depth, false, board);
    perform(bestmove, board);
    return bestmove;
}

bool Chess::check(bool turn, int board[][8])
{
    if (turn == true) {
        bool found = false;
        int row, col;
        //Finding the king on the board

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == 10) {
                    row = i;
                    col = j;
                    found = true;
                    break;
                }
            }
        }
        if (found == false) {
            return false;
        }

        //Finding the king on the board
        if (row != 0 && col != 0 && board[row - 1][col - 1] == -1) return true;
        else if (row != 0 && col != 7 && board[row - 1][col + 1] == -1) return true;
        int a, b;
        a = row;
        b = col;
        if (a != 0 && b != 0) {
            for (;;) {
                a -= 1;
                b -= 1;
                if (board[a][b] == -6 || board[a][b] == -2) return true;
                if (board[a][b] != 0 || a == 0 || b == 0) break;
            }
        }
        a = row;
        b = col;
        if (a != 0 && b != 7) {
            for (;;) {
                a -= 1;
                b += 1;
                if (board[a][b] == -6 || board[a][b] == -2) return true;
                if (board[a][b] != 0 || a == 0 || b == 7) break;
            }
        }
        a = row;
        b = col;
        if (a != 7 && b != 0) {
            for (;;) {
                a += 1;
                b -= 1;
                if (board[a][b] == -6 || board[a][b] == -2) return true;
                if (board[a][b] != 0 || a == 7 || b == 0) break;
            }
        }
        a = row;
        b = col;
        if (a != 7 && b != 7) {
            for (;;) {
                a += 1;
                b += 1;
                if (board[a][b] == -6 || board[a][b] == -2) return true;
                if (board[a][b] != 0 || a == 7 || b == 7) break;
            }
        }

        a = row;
        b = col;
        if (a != 7) {
            for (;;) {
                a += 1;
                if (board[a][b] == -6 || board[a][b] == -5) return true;
                if (board[a][b] != 0 || a == 7) break;
            }
        }
        a = row;
        b = col;
        if (a != 0) {
            for (;;) {
                a -= 1;
                if (board[a][b] == -6 || board[a][b] == -5) return true;
                if (board[a][b] != 0 || a == 0) break;
            }
        }

        a = row;
        b = col;
        if (b != 7) {
            for (;;) {
                b += 1;
                if (board[a][b] == -6 || board[a][b] == -5) return true;
                if (board[a][b] != 0 || b == 7) break;
            }
        }
        a = row;
        b = col;
        if (b != 0) {
            for (;;) {
                b -= 1;
                if (board[a][b] == -6 || board[a][b] == -5) return true;
                if (board[a][b] != 0 || b == 0) break;
            }
        }

        if (row > 0 && col < 6 && board[row - 1][col + 2] == -3)return true;
        if (row > 1 && col < 7 && board[row - 2][col + 1] == -3)return true;
        if (row < 7 && col < 6 && board[row + 1][col + 2] == -3)return true;
        if (row < 6 && col < 7 && board[row + 2][col + 1] == -3)return true;
        if (row < 6 && col > 0 && board[row + 2][col - 1] == -3)return true;
        if (row < 7 && col > 1 && board[row + 1][col - 2] == -3)return true;
        if (row > 1 && col > 0 && board[row - 2][col - 1] == -3)return true;
        if (row > 0 && col > 1 && board[row - 1][col - 2] == -3)return true;

        if (row != 7 && board[row + 1][col] == -10)return true;
        if (row != 0 && board[row - 1][col] == -10)return true;
        if (col != 7 && board[row][col + 1] == -10) return true;
        if (col != 0 && board[row][col - 1] == -10) return true;
        if (row != 7 && col != 7 && board[row + 1][col + 1] == -10)return true;
        if (row != 7 && col != 0 && board[row + 1][col - 1] == -10) return true;
        if (row != 0 && col != 7 && board[row - 1][col + 1] == -10) return true;
        if (row != 0 && col != 0 && board[row - 1][col - 1] == -10) return true;


    }

    else if (turn == false) {
        bool found = false;
        int row, col;
        //Finding the king on the board

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == -10) {
                    row = i;
                    col = j;
                    found = true;
                    break;
                }
            }
        }
        if (found == false) {
            return false;
        }

        //Finding the king on the board

        if (row != 7 && col != 0 && board[row + 1][col - 1] == 1) return true;
        else if (row != 7 && col != 7 && board[row + 1][col + 1] == 1) return true;

        int a, b;
        a = row;
        b = col;
        if (a != 0 && b != 0) {
            for (;;) {
                a -= 1;
                b -= 1;
                if (board[a][b] == 6 || board[a][b] == 2) return true;
                if (board[a][b] != 0 || a == 0 || b == 0) break;
            }
        }
        a = row;
        b = col;
        if (a != 0 && b != 7) {
            for (;;) {
                a -= 1;
                b += 1;
                if (board[a][b] == 6 || board[a][b] == 2) return true;
                if (board[a][b] != 0 || a == 0 || b == 7) break;
            }
        }
        a = row;
        b = col;
        if (a != 7 && b != 0) {
            for (;;) {
                a += 1;
                b -= 1;
                if (board[a][b] == 6 || board[a][b] == 2) return true;
                if (board[a][b] != 0 || a == 7 || b == 0) break;
            }
        }
        a = row;
        b = col;
        if (a != 7 && b != 7) {
            for (;;) {
                a += 1;
                b += 1;
                if (board[a][b] == 6 || board[a][b] == 2) return true;
                if (board[a][b] != 0 || a == 7 || b == 7) break;
            }
        }

        a = row;
        b = col;
        if (a != 7) {
            for (;;) {
                a += 1;
                if (board[a][b] == 6 || board[a][b] == 5) return true;
                if (board[a][b] != 0 || a == 7) break;
            }
        }
        a = row;
        b = col;
        if (a != 0) {
            for (;;) {
                a -= 1;
                if (board[a][b] == 6 || board[a][b] == 5) return true;
                if (board[a][b] != 0 || a == 0) break;
            }
        }

        a = row;
        b = col;
        if (b != 7) {
            for (;;) {
                b += 1;
                if (board[a][b] == 6 || board[a][b] == 5) return true;
                if (board[a][b] != 0 || b == 7) break;
            }
        }
        a = row;
        b = col;
        if (b != 0) {
            for (;;) {
                b -= 1;
                if (board[a][b] == 6 || board[a][b] == 5) return true;
                if (board[a][b] != 0 || b == 0) break;
            }
        }

        if (row > 0 && col < 6 && board[row - 1][col + 2] == 3)return true;
        if (row > 1 && col < 7 && board[row - 2][col + 1] == 3)return true;
        if (row < 7 && col < 6 && board[row + 1][col + 2] == 3)return true;
        if (row < 6 && col < 7 && board[row + 2][col + 1] == 3)return true;
        if (row < 6 && col > 0 && board[row + 2][col - 1] == 3)return true;
        if (row < 7 && col > 1 && board[row + 1][col - 2] == 3)return true;
        if (row > 1 && col > 0 && board[row - 2][col - 1] == 3)return true;
        if (row > 0 && col > 1 && board[row - 1][col - 2] == 3)return true;

        if (row != 7 && board[row + 1][col] == 10)return true;
        if (row != 0 && board[row - 1][col] == 10)return true;
        if (col != 7 && board[row][col + 1] == 10) return true;
        if (col != 0 && board[row][col - 1] == 10) return true;
        if (row != 7 && col != 7 && board[row + 1][col + 1] == 10)return true;
        if (row != 7 && col != 0 && board[row + 1][col - 1] == 10) return true;
        if (row != 0 && col != 7 && board[row - 1][col + 1] == 10) return true;
        if (row != 0 && col != 0 && board[row - 1][col - 1] == 10) return true;

    }

    return false;
}

void Chess::getdiagonalmoves(bool turn, int row, int col, int board[][8])
{
    int a, b;
    if (turn) {
        a = row;
        b = col;
        if (a != 0 && b != 0) {
            for (;;) {
                a -= 1;
                b -= 1;
                if (board[a][b] > 0) break;
                if (board[a][b] < 0 || a == 0 || b == 0) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b])pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (a != 0 && b != 7) {
            for (;;) {
                a -= 1;
                b += 1;
                if (board[a][b] > 0) break;
                if (board[a][b] < 0 || a == 0 || b == 7) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b])pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));

            }
        }
        a = row;
        b = col;
        if (a != 7 && b != 7) {
            for (;;) {
                a += 1;
                b += 1;
                if (board[a][b] > 0) break;
                if (board[a][b] < 0 || a == 7 || b == 7) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b])pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (a != 7 && b != 0) {
            for (;;) {
                a += 1;
                b -= 1;
                if (board[a][b] > 0) break;
                if (board[a][b] < 0 || a == 7 || b == 0) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b])pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
    }
    else if (!turn) {

        a = row;
        b = col;
        if (a != 0 && b != 0) {
            for (;;) {
                a -= 1;
                b -= 1;
                if (board[a][b] < 0) break;
                if (board[a][b] > 0 || a == 0 || b == 0) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b])pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (a != 0 && b != 7) {
            for (;;) {
                a -= 1;
                b += 1;
                if (board[a][b] < 0)
                    break;
                if (board[a][b] > 0 || a == 0 || b == 7) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (board[a][b] == 0)
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));

            }
        }
        a = row;
        b = col;
        if (a != 7 && b != 7) {
            for (;;) {
                a += 1;
                b += 1;
                if (board[a][b] < 0) break;
                if (board[a][b] > 0 || a == 7 || b == 7) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b])pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (a != 7 && b != 0) {
            for (;;) {
                a += 1;
                b -= 1;
                if (board[a][b] < 0) break;
                if (board[a][b] > 0 || a == 7 || b == 0) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b])pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }

    }
}

void Chess::getstraigtmoves(bool turn, int row, int col, int board[][8])
{
    int a, b;
    if (turn) {// white player
        a = row;
        b = col;
        if (a != 0) {
            for (;;) {
                a -= 1;
                if (board[a][b] > 0) break;
                if (board[a][b] < 0 || a == 0) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b]) pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (a != 7) {
            for (;;) {
                a += 1;
                if (board[a][b] > 0) break;
                if (board[a][b] < 0 || a == 7) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b]) pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (b != 0) {
            for (;;) {
                b -= 1;
                if (board[a][b] > 0) break;
                if (board[a][b] < 0 || b == 0) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b]) pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (b != 7) {
            for (;;) {
                b += 1;
                if (board[a][b] > 0) break;
                if (board[a][b] < 0 || b == 7) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b]) pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
    }

    else if (!turn) // black player
    {
        a = row;
        b = col;
        if (a != 0) {
            for (;;) {
                a -= 1;
                if (board[a][b] < 0) break;
                if (board[a][b] > 0 || a == 0) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b]) pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (a != 7) {
            for (;;) {
                a += 1;
                if (board[a][b] < 0) break;
                if (board[a][b] > 0 || a == 7) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b]) pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (b != 0) {
            for (;;) {
                b -= 1;
                if (board[a][b] < 0) break;
                if (board[a][b] > 0 || b == 0) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b]) pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
        a = row;
        b = col;
        if (b != 7) {
            for (;;) {
                b += 1;
                if (board[a][b] < 0) break;
                if (board[a][b] > 0 || b == 7) {
                    pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
                    break;
                }
                if (!board[a][b]) pseudomoves.insert(pseudomoves.begin(), push(row, col, a, b, board));
            }
        }
    }
}

void Chess::getknightmoves(bool turn, int row, int col, int board[][8])
{
    if (turn) {

        if (row > 0 && col < 6 && board[row - 1][col + 2] <= 0) // one up two right
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col + 2, board));

        if (row > 1 && col < 7 && board[row - 2][col + 1] <= 0) // two up one right
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 2, col + 1, board));

        if (row < 7 && col < 6 && board[row + 1][col + 2] <= 0) // one down two right
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col + 2, board));

        if (row < 6 && col < 7 && board[row + 2][col + 1] <= 0) // two down one right
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 2, col + 1, board));

        if (row < 6 && col > 0 && board[row + 2][col - 1] <= 0) //two down one left
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 2, col - 1, board));

        if (row < 7 && col > 1 && board[row + 1][col - 2] <= 0) // one down two left
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col - 2, board));

        if (row > 1 && col > 0 && board[row - 2][col - 1] <= 0) // two up one left
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 2, col - 1, board));

        if (row > 0 && col > 1 && board[row - 1][col - 2] <= 0) // one up two left
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col - 2, board));
    }

    else if (!turn) {
        if (row > 0 && col < 6 && board[row - 1][col + 2] >= 0)pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col + 2, board));
        if (row > 1 && col < 7 && board[row - 2][col + 1] >= 0)pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 2, col + 1, board));
        if (row < 7 && col < 6 && board[row + 1][col + 2] >= 0)pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col + 2, board));
        if (row < 6 && col < 7 && board[row + 2][col + 1] >= 0)pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 2, col + 1, board));
        if (row < 6 && col > 0 && board[row + 2][col - 1] >= 0)pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 2, col - 1, board));
        if (row < 7 && col > 1 && board[row + 1][col - 2] >= 0)pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col - 2, board));
        if (row > 1 && col > 0 && board[row - 2][col - 1] >= 0)pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 2, col - 1, board));
        if (row > 0 && col > 1 && board[row - 1][col - 2] >= 0)pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col - 2, board));
    }
}

void Chess::getpawnmoves(bool turn, int row, int col, int board[][8])
{
    if (turn) {
        if (row == 0) {
            return;
            //en passant
        }
        if (row == 6 && board[row - 1][col] == 0 && board[row - 2][col] == 0)
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 2, col, board));
        if (board[row - 1][col] == 0)
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col, board));
        if (col != 0 && board[row - 1][col - 1] < 0)
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col - 1, board));
        if (col != 7 && board[row - 1][col + 1] < 0)
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col + 1, board));
    }

    else if (!turn) {
        if (row == 7) {
            return;
            //en passant
        }
        if (row == 1 && board[row + 1][col] == 0 && board[row + 2][col] == 0) {
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 2, col, board));
        }
        if (board[row + 1][col] == 0)
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col, board));
        if (col != 0 && board[row + 1][col - 1] > 0)
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col - 1, board));
        if (col != 7 && board[row + 1][col + 1] > 0)
            pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col + 1, board));
    }
}

void Chess::getkingmoves(bool turn, int row, int col, int board[][8])
{
    if (!turn) {
        if (row != 7 && board[row + 1][col] >= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col, board));
        if (row != 0 && board[row - 1][col] >= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col, board));
        if (col != 7 && board[row][col + 1] >= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row, col + 1, board));
        if (col != 0 && board[row][col - 1] >= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row, col - 1, board));
        if (row != 7 && col != 7 && board[row + 1][col + 1] >= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col + 1, board));
        if (row != 7 && col != 0 && board[row + 1][col - 1] >= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col - 1, board));
        if (row != 0 && col != 7 && board[row - 1][col + 1] >= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col + 1, board));
        if (row != 0 && col != 0 && board[row - 1][col - 1] >= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col - 1, board));
    }
    else if (turn) {
        if (row != 7 && board[row + 1][col] <= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col, board));
        if (row != 0 && board[row - 1][col] <= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col, board));
        if (col != 7 && board[row][col + 1] <= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row, col + 1, board));
        if (col != 0 && board[row][col - 1] <= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row, col - 1, board));
        if (row != 7 && col != 7 && board[row + 1][col + 1] <= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col + 1, board));
        if (row != 7 && col != 0 && board[row + 1][col - 1] <= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row + 1, col - 1, board));
        if (row != 0 && col != 7 && board[row - 1][col + 1] <= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col + 1, board));
        if (row != 0 && col != 0 && board[row - 1][col - 1] <= 0) pseudomoves.insert(pseudomoves.begin(), push(row, col, row - 1, col - 1, board));
    }
}

int Chess::evaluation(int board[][8])
{
    const short int pawn = 95, bishop = 330, knight = 320, rook = 500, queen = 900, king = 2000;
    const int pawnt[8][8] = {
     {0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
     {5,  5, 10, 45, 45, 10,  5,  5},
     {0,  0,  0, 20, 20,  0,  0,  0},
    {5, -5,-10,  0,  0,-10, -5,  5},
    {5, 10, 10,-20,-20, 10, 10,  5},
    {0,  0,  0,  0,  0,  0,  0,  0}
    };

    const int bishopt[8][8] = {
        {-20,-10,-10,-10,-10,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5, 10, 10,  5,  0,-10},
        {-10,  5,  5, 10, 10,  5,  5,-10},
        {-10,  0, 10, 10, 10, 10,  0,-10},
        {-10, 10, 10, 10, 10, 10, 10,-10},
        {-10,  5,  0,  0,  0,  0,  5,-10},
        {-20,-10,-10,-10,-10,-10,-10,-20},
    };

    const int knightt[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50},
    };

    const int queent[8][8] = {
        {-20,-10,-10, -5, -5,-10,-10,-20},
        {-10,  0,  0,  0,  0,  0,  0,-10},
        {-10,  0,  5,  5,  5,  5,  0,-10},
         {-5,  0,  5,  5,  5,  5,  0, -5},
          {0,  0,  5,  5,  5,  5,  0, -5},
        {-10,  5,  5,  5,  5,  5,  0,-10},
        {-10,  0,  5,  0,  0,  0,  0,-10},
        {-20,-10,-10, -5, -5,-10,-10,-20}
    };
    const int kingt[8][8] = {
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-30,-40,-40,-50,-50,-40,-40,-30},
        {-20,-30,-30,-40,-40,-30,-30,-20},
        {-10,-20,-20,-20,-20,-20,-20,-10},
        {20, 20,  0,  0,  0,  0, 20, 20},
        {20, 30, 10,  0,  0, 10, 30, 20 },
    };
    const int rookt[8][8] = {
      {0,  0,  0,  0,  0,  0,  0,  0},
      {5, 10, 10, 10, 10, 10, 10,  5},
     {-5,  0,  0,  0,  0,  0,  0, -5},
     {-5,  0,  0,  0,  0,  0,  0, -5},
     {-5,  0,  0,  0,  0,  0,  0, -5},
     {-5,  0,  0,  0,  0,  0,  0, -5},
     {-5,  0,  0,  0,  0,  0,  0, -5},
      {0,  0,  0,  5,  5,  0,  0,  0}
    };
    int score = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!board[i][j]) continue;
            if (board[i][j] == 1) {
                score -= pawnt[i][j];
                score -= pawn;
                if (board[i - 1][j] == 1) // double stacked pawn
                    score -= 20;
            }
            else if (board[i][j] == 2) {
                score -= bishopt[i][j];
                score -= bishop;
            }
            else if (board[i][j] == 3) {
                score -= knightt[i][i];
                score -= knight;
            }
            else if (board[i][j] == 5) {
                score -= rookt[i][j];
                score -= rook;
            }
            else if (board[i][j] == 6) {
                score -= queent[i][j];
                score -= queen;
            }
            else if (board[i][j] == 10) {
                score -= kingt[i][j];
                score -= king;
            }
            if (board[i][j] == -1) {
                score += pawnt[7 - i][7 - j];
                score += pawn;
            }
            else if (board[i][j] == -2) {
                score += bishopt[7 - i][7 - j];
                score += bishop;
            }
            else if (board[i][j] == -3) {
                score += knightt[7 - i][7 - j];
                score += knight;
            }
            else if (board[i][j] == -5) {
                score += rookt[7 - i][7 - j];
                score += rook;
            }
            else if (board[i][j] == -6) {
                score += queent[7 - i][7 - j];
                score += queen;
            }
            else if (board[i][j] == -10) {
                score += kingt[7 - i][7 - j];
                score += king;
            }

        }
    }

    return score;
}

int Chess::miniMax(int depth, bool ismax, int alpha, int beta, int board[][8])
{
    if (depth == 0) {
        return evaluation(board);
    }
    int maxeval = -999999;
    int mineval = 999999;
    container possiblemoves;
    int original;
    int eval;
    if (ismax == true) {
        possiblemoves = getallmoves(false, board);
        //return the legal moves
        if (possiblemoves.size() == 0 && check(false, board) == false) {
            return 999999;
        }
        if (possiblemoves.size() == 0 && check(false, board) == true) {
            return -999999;
        }
        for (string i : possiblemoves) {
            original = perform(i, board);
            eval = miniMax(depth - 1, false, alpha, beta, board);
            undomove(original, i, board);
            if (eval > maxeval)
                maxeval = eval;
            if (alpha < maxeval)
                alpha = maxeval;
            if (beta <= alpha)
                break;
        }
        return maxeval;
    }
    else {
        possiblemoves = getallmoves(true, board);
        if (possiblemoves.size() == 0 && check(true, board) == false) {
            return -99999999;
        }
        if (possiblemoves.size() == 0 && check(true, board) == true) {
            return 99999999;
        }
        else if (possiblemoves.size() == 0 && check(true, board) == false) {
            return -99999999;
        }
        for (string i : possiblemoves) {
            original = perform(i, board);
            eval = miniMax(depth - 1, true, alpha, beta, board);
            undomove(original, i, board);
            if (eval < mineval)
                mineval = eval;
            if (beta > mineval)
                beta = mineval;
            if (beta <= alpha)
                break;
        }
        return mineval;
    }
    return 1;
}

string Chess::miniMaxroot(int depth, bool turn, int board[][8])
{
    cout << "what could be the best move?" << endl;
    string bestmove;
    int maxeval = -9999999;
    container allmoves = getallmoves(turn,board);
    cout << "number of legal moves " << allmoves.size() << endl;
    int original;
    int eval;
    cout << "Computer view" << endl;
    for (int v = 0; v < 8; v++) {
        for (int w = 0; w < 8; w++) {
            cout << board[v][w] << " ";
        }
        cout << endl;
    }
    for (string i : allmoves) {
        //original = perform(i);
        original = board[i[2] - 48][i[3] - 48];
        board[i[2] - 48][i[3] - 48] = board[i[0] - 48][i[1] - 48];
        board[i[0] - 48][i[1] - 48] = 0;
        //cout << "Move: " << i << endl;
        eval = miniMax(depth - 1, true, -99999999, 99999999, board);
        //cout << "Move: " << i << ' ' << "Points: " << eval << '\n';
        undomove(original, i,board);
        if (eval > maxeval) {
            maxeval = eval;
            bestmove = i;
        }
    }
    cout << "Bestmove: " << bestmove << endl;
    return bestmove;
}

void Chess::undomove(int original, string Move, int board[][8])
{
    board[Move[0] - 48][Move[1] - 48] = board[Move[2] - 48][Move[3] - 48];// -48 is to convert char to int
    int i_1 = Move[0] - 48;
    int j_1 = Move[1] - 48;
    int i_2 = Move[2] - 48;
    int j_2 = Move[3] - 48;
    player_board[i_1 * 8 + j_1] = player_board[i_2 * 8 + j_2];
    board[Move[2] - 48][Move[3] - 48] = original; // -48 to convert char to int
    player_board[i_2 * 8 + j_2] = original;
}

