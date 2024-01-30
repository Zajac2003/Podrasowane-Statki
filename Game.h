#ifndef Game_H
#define Game_H


#include <iostream>
#include "Board.h"
using namespace std;

#pragma once
class Game
{
    public:

        Board board1;
        Board board2;

        Game(const Board& board1, const Board& board2) : board1(board1), board2(board2)
        {
            this->board1 = board1;
            this->board2 = board2;
        }

        bool isGameWon();
        void printWinner();
};

#endif