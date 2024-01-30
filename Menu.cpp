#include "Menu.h"

void Menu::printGame()
{
    printBoards();
    printChoiceMenu();
}

void Menu::runGame()
{
    firstScreen();
    mainMenu();

    //printBoards();
    game.board1.shipCreator();
    game.board2.fillWithRandomShips();
    //game.board1.useBomb(0,0);
    while (!game.isGameWon())
    {
        //jedna tura
        //game.board2.printBoard(0);
        if(trybGry == 0)
        {
            printGame();
            if(game.isGameWon()) break;
            //game.board1.printBoard(1);
            bot.takeShot(game.board1);
        }
        else
        {
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            cout<<"Player 1 turn!"<<endl;
            game.board1.printBoard(0);
        }
    }

    game.printWinner();
}

void Menu::printBoards()
{
    cout << "  A B C D E F G H I J           A B C D E F G H I J" << endl;
    cout << ' ' << char(218) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(191);
    cout << "         " << char(218) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(194) << char(196) << char(191) << endl;

    for (int x = 0;x < game.board1.height;x++)
    {
        this_thread::sleep_for(std::chrono::milliseconds(100));
        for (int y = 0;y < game.board1.width;y++)
        {

            if (y == 0) { cout << x << char(179); }

            if (game.board1.table[x][y] == 0)//empty field
            {
                cout << "" << char(176) << "" << char(179);
            }
            else if (game.board1.table[x][y] == 1)//field with alive ship
            {
                cout << "" << char(254) << "" << char(179);
            }
            else if (game.board1.table[x][y] == 2 || game.board1.table[x][y] == 4)//field with dead ship
            {
                cout << "" << "X" << "" << char(179);
            }
            else if (game.board1.table[x][y] == 3 or game.board1.table[x][y] == 5 or game.board1.table[x][y] == 7)//field with missed shot
            {
                cout << char(250) << char(179);
            }
            else if (game.board1.table[x][y] == 6)//field with missed shot
            {
                cout << "?" << char(179);
            }


        }
        cout << "        ";
        //cout <<" " << char(195) << char(196) << char(197) << char(196) << char(197) << char(196) << char(197) << char(196) << char(197) << char(196) << char(197) << char(196) << char(197) << char(196) << char(197) << char(196) << char(197) << char(196) << char(197) << char(196) << char(197)<<"       ";
        for (int y2 = 0;y2 < game.board1.width;y2++)
        {
            if (y2 == 0) { cout << x << char(179); }

            if (game.board2.table[x][y2] == 0 || game.board2.table[x][y2] == 1 or game.board2.table[x][y2] == 6)//empties
            {
                cout << "" << char(176) << "" << char(179);
            }
            else if (game.board2.table[x][y2] == 2 || game.board2.table[x][y2] == 4)//field with dead ship
            {
                cout << "" << 'X' << "" << char(179);
            }
            else if (game.board2.table[x][y2] == 3 || game.board2.table[x][y2] == 5 or game.board2.table[x][y2] == 7)//field with missed shot
            {
                cout << char(250) << char(179);
            }

        }
        cout << endl;
    }
    cout << ' ' << char(192) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(217);
    cout << "         " << char(192) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(193) << char(196) << char(217);


    cout<<endl<<"     Gracz: "<<game.board1.aliveFields<<"HP                 Przeciwnik: "<<game.board2.aliveFields<<"HP"<<endl;
    cout<<"    4:"<<game.board1.quadraCounter<<" 3:"<<game.board1.tripleCounter<<" 2:"<<game.board1.doubleCounter<<" 1:"<<game.board1.singleCounter;
    cout<<"               4:"<<game.board2.quadraCounter<<" 3:"<<game.board2.tripleCounter<<" 2:"<<game.board2.doubleCounter<<" 1:"<<game.board2.singleCounter;
    cout << endl;
    this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Menu::printChoiceMenu()
{
    string choose = "-1";
    while((choose != "1" && choose != "2" && choose != "3"&& choose != "4") ||( game.board2.bombCounter==0 && choose == "2")||( game.board2.missleCounter ==0 && choose == "3"))
    {
        cout<<"Your shoot!"<<endl;
        cout << "1. Shoot" << endl;

        if (game.board2.bombCounter != 0) {
            cout << "2. Use bomb (" << game.board2.bombCounter << ")" << endl;
        } else {
            cout << "2. (No bomb available)" << endl;
        }

        if (game.board2.missleCounter != 0) {
            cout << "3. Use a missle (" << game.board2.missleCounter << ")" << endl;
        } else {
            cout << "3. (No missle available)" << endl;
        }
        if (game.board2.treasureCounter != 0) {
            cout << "4. Use a mythical weapon! (" << game.board2.treasureCounter << ")" << endl;
        }

        cin >> choose;
    }

    takeAction(game.board2, choose);
}

bool Menu::takeAction(Board &board, string choose)
{
    if (choose.length() == 0)
    {
        cout<<"Invalid input! string empty" << endl;
        return false;
    }
    else if (choose == "1")//do shoot
    {
        string koordynaty;
        cout<<"Input coords:" << endl;

        cin >> koordynaty;
        int x = board.handleCoordInput(koordynaty, 'x');
        int y = board.handleCoordInput(koordynaty, 'y');
        //cout<<"Koordynaty!!: "<<x<<" "<<y<<endl;
        while (board.shoot(x, y))
        {

            cout << "You have another shot!" << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            printBoards();
            cout<<"Input coords:" << endl;

            cin >> koordynaty;
            x = board.handleCoordInput(koordynaty, 'x');
            y = board.handleCoordInput(koordynaty, 'y');
        }
        //cout << "You have missed." << endl;
        return false;
    }
    else if(choose == "2" && game.board2.bombCounter>0)
    {
        string koordynaty;
        cout<<"Input coords:" << endl;

        cin >> koordynaty;
        int x = board.handleCoordInput(koordynaty, 'x');
        int y = board.handleCoordInput(koordynaty, 'y');
        cout<<"Shooting bomb at "<<x<<char(y+65)<<endl;
        game.board2.useBomb(x,y);
    }
    else if(choose == "3" && game.board2.missleCounter>0)
    {
        string koordynaty;
        cout<<"Input coords:" << endl;

        cin >> koordynaty;
        int x = board.handleCoordInput(koordynaty, 'x');
        int y = board.handleCoordInput(koordynaty, 'y');
        cout<<"Shooting missle at "<<x<<" "<<char(y+65)<<endl;
        game.board2.useMissle(x,y);
    }
    else if(choose == "4" && game.board2.treasureCounter>0)
    {
        string koordynaty;
        cout<<"Input coords:" << endl;

        cin >> koordynaty;
        int x = board.handleCoordInput(koordynaty, 'x');
        int y = board.handleCoordInput(koordynaty, 'y');
        cout<<"Using mythical weapon at "<<x<<char(y+65)<<endl;
        game.board2.useTreasure(x,y);
    }


    return true;
}

void Menu::mainMenu()
{
    string choice = "";

    while (choice != "1" && choice != "3")
    {
        cout << "1 Play with bot" << endl;
        cout << "2 Instruction" << endl;
        //cout << "3 Play with friend" << endl;

        cin>>choice;

        if(choice == "2")
        {
            printInstruction();
        }
    }

    if(choice == "1")
    {
        cout << "Choose bot difficulty: " << endl;
        cout << "1. Easy" << endl;
        cout << "2. World class champion" << endl;
        cin >> choice;
    }
    bot.difficulty = choice == "1" ? 0 : 1;
}

void Menu::firstScreen()
{
    printMainTitle();
}

void Menu::printInstruction()
{
    cout << "ZASADY GRY:" << std::endl;
    cout <<"Gra rozgrywa sie na dwoch planszach 10x10 przeciwnika i gracza. "<< endl;
    cout<< "Gra przebiega naprzemiennie: najpierw gracz oddaje strzal, jesli uda sie mu trafic, moze kontynuowac strzelanie do momentu, az chybi (z wyjatkiem uzywania bomb i rakiet. w takim wypadku nawet po trafieniu statku nie przysluguje dodatkowy ruch)."<< endl;
    cout<< "Po jego turze nastepuje kolej bota."<< endl;
    cout<< "Zatopienie statku ma miejsce, kiedy wszystkie kratki symbolizujace ten okret zostana trafione przez drugiego gracza."<< endl;
    cout<<endl;
    cout << "To continue, click any button" <<endl;

    string c;
    cin>>c;

}

void Menu::printMainTitle()
{
    cout<<"              ####     ####    ####    ####    ########          ####  " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout<<"            ####       ####    ####    ####    ####    ###     ####    " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout<<"          ####         ####    ####    ####    ####    ###   ####      " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout<<"            ####       ############    ####    ####    ###     ####    " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout<<"               ####    ############    ####    ########           #### " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout<<"              ####     ####    ####    ####    ####              ####  " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout<<"            ####       ####    ####    ####    ####            ####    " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout<<"          ####         ####    ####    ####    ####          ####      " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << endl;cout << endl;
    cout << "        #########    ############    ####        ####    ############" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << "        ####         ############    ####        ####    ############" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << "        ####         ####    ####    #######  #######    ####        " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << "        ####         ####    ####    ####  ####  ####    ############" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << "        #### ####    ############    ####        ####    ############" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << "        ####   ##    ####    ####    ####        ####    ####        " << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << "        #########    ####    ####    ####        ####    ############" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << "        #########    ####    ####    ####        ####    ############" << endl;

    this_thread::sleep_for(std::chrono::milliseconds(650));
    cout<<"                     <Press any Key to continue>"<<endl;
    char znak;
    znak = _getch();
    //
}
