#ifndef Menu_H
#define Menu_H

#include <iostream>
#include "Game.h"
#include "Bot.h"
#include <conio.h>

using namespace std;

#pragma once
class Menu
{
    public:
        Game game;
        Bot bot;
        int trybGry;

        Menu(const Game& game):game(game)
        {
            this->game = game;
        }

        void runGame();
        void printGame();
        void printBoards();
        void printChoiceMenu();
        bool takeAction(Board &board, string choose);
        void mainMenu();
        void firstScreen();
        void printInstruction();
        void printMainTitle();
};

#endif