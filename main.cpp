//#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Menu.h"

using namespace std;

int main()
{

    Board boardMy(10,10);
    Board boardEnemy(10,10);

    Game game(boardMy, boardEnemy);

    Menu menu(game);

    menu.runGame();

    return 0;
}