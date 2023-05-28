#pragma once
#include <string>
#include <vector>
#include<iostream>
#include "Boards.h"

using namespace std;

typedef vector<string> container;

//ChessBoard player;
class Chess
{
public:
    container pseudomoves;
    container legal_moves;
    
    int perform(string Move, int board[][8]);
    string push(int row, int col, int desrow, int descol, int board[][8]);
    container getallmoves(bool turn, int board[][8]);
    string computer_move(unsigned short int depth,int board[][8]);
    bool checkmate(bool turn, int board[][8]);

    bool check(bool turn, int board[][8]);
    bool checkmatewhite = false;
    bool checkmateblack = false;
private:
    void getdiagonalmoves(bool turn, int row, int col, int board[][8]);
    void getstraigtmoves(bool turn, int row, int col, int board[][8]);
    void getknightmoves(bool turn, int row, int col, int board[][8]);
    void getpawnmoves(bool turn, int row, int col, int board[][8]);
    void getkingmoves(bool turn, int row, int col, int board[][8]);
    int evaluation(int board[][8]);
    int miniMax(int depth, bool ismax, int alpha, int beta, int board[][8]);
    string miniMaxroot(int depth, bool turn, int board[][8]);
    void undomove(int original, string Move, int board[][8]);
};

