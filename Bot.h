#ifndef BOT_H
#define BOT_H


#include <iostream>
#include <cstdlib> // Dla funkcji rand()
#include <ctime>   // Dla funkcji time()
#include <thread>  // Dla std::this_thread::sleep_for
#include <chrono>
#include <vector>
#include "Board.h"
using namespace std;
#pragma once

class Bot
{
    public:
        Bot()
        {
            fillMoveTable();
        }
            int ruchy[50][2]={
                    {3,0},{2,1},{1,0},{1,2},{0,1},{0,3},
                    {0,5},{1,6},{0,7},{2,7},{1,8},{0,9},
                    {3,8},{2,9},{4,9},{5,0},{6,1},{7,0},
                    {7,2},{8,1},{9,0},{9,2},{8,3},{9,4},
                    {9,6},{8,7},{9,8},{7,8},{8,9},{6,9},
                    {5,8},{6,7},{7,6},{7,4},{8,5},{6,5},
                    {5,6},{4,7},{3,6},{2,5},{1,4},{3,4},
                    {2,3},{4,5},{5,4},{6,3},{4,3},{5,2},
                    {3,2},{4,1}
        };
        int nrRuchu=0;
        int difficulty=0;
        void takeShot(Board& board);
    private:
        void randomShot(Board &board);
        void fillMoveTable();
};

#endif