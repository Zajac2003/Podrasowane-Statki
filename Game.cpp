#include "Game.h"


bool Game::isGameWon()
{
    //bruh
    return bool(board1.aliveFields == 0 || board2.aliveFields == 0);
}

void Game::printWinner()
{
    if (this->isGameWon())
    {
        if (board1.aliveFields == 0)
        {
            cout << "You have lost!" << endl;
        }
        else if (board2.aliveFields == 0)
        {
            cout << "You have won!" << endl;
        }
        else
        {
            cout<<"Win error> nobodydb dsajbdisa" << endl;
        }

    }
    else
    {
        cout << "Nobody won yet!" << endl;
    }
}