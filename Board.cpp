#include "Board.h"


Board::Board(int width, int height)
{
    this->width = width;
    this->height = height;

    table = new int* [height];
    for (int i = 0; i < height; i++)
    {
        table[i] = new int[width];
    }

    fillBoardWithEmpties();
}

void Board::useBomb(int x, int y)
{
    for(int i=x-1;i<=x+1;i++)
    {
        for(int j=y-1;j<=y+1;j++)
        {
            if(i>=0 && i<10 && j>=0 && j<10)
            {
                //cout<<"Ahtung bomba "<<i<<" "<<j<<endl;
                if(this->table[i][j] == 1 or this->table[i][j] == 6)
                {
                    this->shoot(i,j);
                }
                else if(this->table[i][j] == 0)
                {
                    this->table[i][j] = 3;
                }

            }
        }
    }
    bombCounter --;
}

//checked
bool Board::shoot(int x, int y)
{
    //returns true if player have another shot
    //returns false if player doesn't have another shot
    if (!this->areCoordinatesValid(x,y))
    {
        cout<<"Unvalid field choosen" << endl;

        return true;
    }

    int fieldValue = table[x][y];
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout<<"Shooting "<<x<<char(y+65)<<endl;
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (fieldValue == 0)//no ship part shot
    {
        cout<<"Missed"<< endl;
        table[x][y] = 3;
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        return false;
    }
    else if(fieldValue == 1)//ship taken shot, another shot
    {
        cout<<"Ship shot!"<< endl;
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        table[x][y] = 2;
        aliveFields--;
        if(aliveFields %4 == 0 && aliveFields != 20 && aliveFields != 5)
        {
            bombCounter ++;
            cout<<"Dostajesz bombe! "<<endl;
        }

        if(aliveFields ==7)
        {
            missleCounter ++;
            cout<<"Dostajesz rakiete! "<<endl;
        }

        int sasiedzi[4][2];
        for (int i = 0; i < 4; i++)
        {
            sasiedzi[i][0] = -5;
            sasiedzi[i][1] = -5;
        }

        int licznikSasiadow = 0;
        bool czyDuplikat;
        sasiedzi[0][0] = x;
        sasiedzi[0][1] = y;
        licznikSasiadow++;

        for(int n=0;n<4;n++)
        {
            if(sasiedzi[n][0] == -5) break;

            x = sasiedzi[n][0];
            y = sasiedzi[n][1];
            //"Bazowe X: "<<x<<" y: "<<y<<endl;

            int i, j;
            i = x - 1 < 0 ? 0 : x - 1;
            j = y - 1 < 0 ? 0 : y - 1;

            int i2, j2;
            i2 = x + 1 > 9 ? 9 : x + 1;
            j2 = y + 1 > 9 ? 9 : y + 1;

            for (;i<=i2;i++)
            {
                for (;j<=j2;j++)
                {
                    if(table[i][j] == 1 || table[i][j] == 2)
                    {
                        czyDuplikat = false;
                        for(auto & p : sasiedzi)
                        {
                            if(p[0] == i && p[1] == j) czyDuplikat = true;
                        }
                        if(!czyDuplikat)
                        {
                            //cout<<"Znajeziono somsiada!:"<< "Wspolrzedne: " << i << " " << j << endl;
                            sasiedzi[licznikSasiadow][0] = i;
                            sasiedzi[licznikSasiadow][1] = j;
                            licznikSasiadow++;
                        }

                    }
                }
                j = y - 1 < 0 ? 0 : y - 1;
            }
        }

        bool isEverythingDead = true;
        for(int p=0;p<4;p++)
        {
            if(sasiedzi[p][0] == -5) break;

            int newX = sasiedzi[p][0];
            int newY = sasiedzi[p][1];
            if(table[newX][newY] == 1) isEverythingDead=false;
        }
        //cout<<"Czy wszystko martwe?: "<<isEverythingDead<<endl;

        if(isEverythingDead)
        {
            if(licznikSasiadow == 4) quadraCounter--;
            if(licznikSasiadow == 3) tripleCounter--;
            if(licznikSasiadow == 2) doubleCounter--;
            if(licznikSasiadow == 1) singleCounter--;
            for (int p = 0; p < 4; p++)
            {
                if (sasiedzi[p][0] == -5) break;

                x = sasiedzi[p][0];
                y = sasiedzi[p][1];
                //"Bazowe X: "<<x<<" y: "<<y<<endl;
                table[x][y] = 4;
                int i, j;
                i = x - 1 < 0 ? 0 : x - 1;
                j = y - 1 < 0 ? 0 : y - 1;

                int i2, j2;
                i2 = x + 1 > 9 ? 9 : x + 1;
                j2 = y + 1 > 9 ? 9 : y + 1;

                for (;i<=i2;i++)
                {
                    for (;j<=j2;j++)
                    {
                        if(table[i][j] == 0)
                        {
                            table[i][j] = 5;
                        }
                    }
                    j = y - 1 < 0 ? 0 : y - 1;
                }

            }
        }
        //cout<<"sasiedzi: "<<endl;
        //cout<<sasiedzi[0][0]<<" "<<sasiedzi[0][1]<<endl;
        //cout<<sasiedzi[1][0]<<" "<<sasiedzi[1][1]<<endl;
        //cout<<sasiedzi[2][0]<<" "<<sasiedzi[2][1]<<endl;
        //cout<<sasiedzi[3][0]<<" "<<sasiedzi[3][1]<<endl;

        return true;
    }
    else if(fieldValue == 6)
    {
        cout<<"Secret mythical weapon found!"<<endl;
        treasureCounter ++;
        table[x][y] = 7;

        return true;
    }
    else//bad field choosen
    {
        cout<<"Field cannot be shot, try different"<< endl;

        return true;
    }
}

void Board::printBoard(int mode) const
{
    //0 normal mode
    //1 hidden mode
    if (mode == 0)//normal mode
    {
        cout << " 0 1 2 3 4 5 6 7 8 9" << endl;
        for (int x = 0;x < this->height;x++)
        {
            for (int y = 0;y < this->width;y++)
            {
                if (y == 0) { cout << x; }

                if (table[x][y] == 0)//empty field
                {
                    cout << "" << char(176) << "" << ' ';
                }
                else if (table[x][y] == 1)//field with alive ship
                {
                    cout << "" << char(254) << "" << ' ';
                }
                else if (table[x][y] == 2)//field with dead ship
                {
                    cout << "" << char(254) << "" << ' ';
                }
                else if (table[x][y] == 3)//field with missed shot
                {
                    cout << char(250) << ' ';
                }
                else if (table[x][y] == 4)//field with completely dead ship
                {
                    cout << "X" <<endl;
                    cout << char(250) << ' ';
                }
                else if (table[x][y] == 5)//field with completely dead ship
                {
                    cout << "O" <<endl;
                    cout << char(250) << ' ';
                }
            }
            cout << endl;
        }
    }
    else if (mode == 1)//hidden mode
    {
        for (int x = 0;x < this->height;x++)
        {
            for (int y = 0;y < this->width;y++)
            {
                if (table[x][y] == 0 || table[x][y] == 1)//empties
                {
                    cout << "" << char(176) << "" << ' ';
                }
                else if (table[x][y] == 2)//field with dead ship
                {
                    cout << "" << 'X' << "" << ' ';
                }
                else if (table[x][y] == 3)//field with missed shot
                {
                    cout << char(250) << ' ';
                }
            }
            cout << endl;
        }
    }
}

bool Board::areCoordinatesValid(int x, int y) const
{
    if (x<0 || x>this->height-1 || y<0 || y>this->width-1)
    {
        cout << "COORD UNVALID ERROR" << endl;
        return false;
    }
    return true;
}

bool Board::placeShip(int x, int y, int orientation,string type)
{
    bool haveBeenSuccesfullyPlaced;

    if (type == "single")
    {
        haveBeenSuccesfullyPlaced =  placeShipSingle(x, y, orientation);

        if (haveBeenSuccesfullyPlaced)
        {
            aliveFields++;
        }

        return haveBeenSuccesfullyPlaced;
    }
    else if (type == "double")
    {
        haveBeenSuccesfullyPlaced = placeShipDouble(x, y, orientation);

        if (haveBeenSuccesfullyPlaced)
        {
            aliveFields+=2;
        }

        return haveBeenSuccesfullyPlaced;
    }
    else if (type == "triple")
    {
        haveBeenSuccesfullyPlaced = placeShipTriple(x, y, orientation);

        if (haveBeenSuccesfullyPlaced)
        {
            aliveFields+=3;
        }

        return haveBeenSuccesfullyPlaced;
    }
    else if (type == "quadra")
    {
        haveBeenSuccesfullyPlaced = placeShipQuadra(x, y, orientation);

        if (haveBeenSuccesfullyPlaced)
        {
            aliveFields+=4;
        }

        return haveBeenSuccesfullyPlaced;
    }
    else
    {
        cout<<"Invalid input error" << endl;
        return false;
    }

}

void Board::shipCreator()
{
    string choice;
    do
    {
        cout << "1 Manual ship placement" << endl;
        cout << "2 Random ship placement" << endl;
        cin>>choice;
    } while (choice != "1" && choice != "2");

    if (choice == "1")
    {

        int singleCounter = 4; //1
        int doubleCounter = 3; //2
        int tripleCounter = 2; //3
        int quadripleCounter = 1; //4

        bool placingFinished = false;

        while (!placingFinished)
        {
            printBoard(0);
            cout << "Place your ships." << endl;
            cout << "1. Single (" << singleCounter << " left)" << endl;
            cout << "2. Double (" << doubleCounter << " left)" << endl;
            cout << "3. Triple (" << tripleCounter << " left)" << endl;
            cout << "4. Quadriple (" << quadripleCounter << " left)" << endl;
            cout << "Choose ship:" << endl;

            int x, y, orientation;
            char choose;
            //bool continueCurrentPlacing;
            choose = _getch();

            if (choose == '1' && singleCounter > 0)
            {

                cout << "Write coordinates:" << endl;
                cin >> x >> y;

                cout << "Write position:" << endl;
                cin >> orientation;

                if (canShipBePlacedProperly(x, y, 1, 1))
                {
                    bool actionPerformed = placeShipSingle(x, y, orientation);
                    while (!actionPerformed)
                    {
                        cout << "Cos poszlo nie tak, jeszcze raz:" << endl;

                        cout << "Write coordinates:" << endl;
                        cin >> x >> y;

                        cout << "Write position:" << endl;
                        cin >> orientation;

                        actionPerformed = placeShipSingle(x, y, orientation);
                    }
                    singleCounter--;
                    aliveFields++;
                }

            }
            else if (choose == '2' && doubleCounter > 0)
            {

                cout << "Write coordinates:" << endl;
                cin >> x >> y;

                cout << "Write orientation:" << endl;
                cin >> orientation;

                if (canShipBePlacedProperly(x, y, 2, 1))
                {
                    bool actionPerformed = placeShipDouble(x, y, orientation);
                    while (!actionPerformed)
                    {
                        cout << "Cos poszlo nie tak, jeszcze raz:" << endl;

                        cout << "Write coordinates:" << endl;
                        cin >> x >> y;

                        cout << "Write position:" << endl;
                        cin >> orientation;

                        actionPerformed = placeShipDouble(x, y, orientation);
                    }
                    doubleCounter--;
                    aliveFields += 2;
                }
            }
            else if (choose == '3' && tripleCounter > 0)
            {

                cout << "Write coordinates:" << endl;
                cin >> x >> y;

                cout << "Write orientation:" << endl;
                cin >> orientation;

                if (canShipBePlacedProperly(x, y, 2, 1))
                {
                    bool actionPerformed = placeShipTriple(x, y, orientation);
                    while (!actionPerformed)
                    {
                        cout << "Cos poszlo nie tak, jeszcze raz:" << endl;

                        cout << "Write coordinates:" << endl;
                        cin >> x >> y;

                        cout << "Write position:" << endl;
                        cin >> orientation;

                        actionPerformed = placeShipTriple(x, y, orientation);
                    }
                    tripleCounter--;
                    aliveFields += 3;
                }

            }
            else if (choose == '4' && quadripleCounter > 0)
            {

                cout << "Write coordinates:" << endl;
                cin >> x >> y;

                cout << "Write orientation:" << endl;
                cin >> orientation;

                if (canShipBePlacedProperly(x, y, 2, 1))
                {
                    bool actionPerformed = placeShipQuadra(x, y, orientation);
                    while (!actionPerformed)
                    {
                        cout << "Cos poszlo nie tak, jeszcze raz:" << endl;

                        cout << "Write coordinates:" << endl;
                        cin >> x >> y;

                        cout << "Write position:" << endl;
                        cin >> orientation;

                        actionPerformed = placeShipQuadra(x, y, orientation);
                    }
                    quadripleCounter--;
                    aliveFields += 4;
                }

            }
            system("cls");
            printBoard(0);
            if (singleCounter == 0 && doubleCounter == 0 && tripleCounter == 0 && quadripleCounter == 0)
            {
                placingFinished = true;
            }
        }
        putTreasure();
        cout << "Skonczyles stawiac statki!" << endl;
    }
    else if (choice == "2")
    {
        fillWithRandomShips();
        //system("cls");
    }
}

bool Board::canPartBePlacedProperly(int x, int y) const
{
    int i, j;
    i = x - 1 < 0 ? 0 : x - 1;
    j = y - 1 < 0 ? 0 : y - 1;

    int i2, j2;
    i2 = x + 1 > 9 ? 9 : x + 1;
    j2 = y + 1 > 9 ? 9 : y + 1;

    //cout << i << " chuj " << j << endl;
    //cout << i2 << " chuj " << j2 << endl;

    int sum = 0;

    for (;i<=i2;i++)
    {
        for (;j<=j2;j++)
        {
            //cout << "Wspolrzedne: " << i << " " << j << endl;
            sum += table[i][j];
        }
        j = y - 1 < 0 ? 0 : y - 1;
    }

    //cout << sum << " SUMA" << endl;
    if (sum == 0) { return true; }
    else { return false; }
}

bool Board::placePart(int x, int y) const
{
    if (!this->areCoordinatesValid(x, y))
    {
        cout << "Field is "
                "" << endl;

        return false;
    }

    int fieldValue = this->table[x][y];

    if (fieldValue == 1 || fieldValue == 2)
    {
        cout << "Field taken" << endl;

        return false;
    }
    else
    {
        this->table[x][y] = 1;

        return true;
    }
    cout << "something went wroooong" << endl;
}

bool Board::placeShipSingle(int x, int y, int orientation) const
{
    return placePart(x, y);
}

bool Board::placeShipDouble(int x, int y, int orientation) const
{
    if (orientation == 1)
    {
        if (x<0 || x> this->width - 2)
        {
            return false;
        }
        else if (y<0 || y> this->height)
        {
            return false;
        }


        return placePart(x, y) && placePart(x + 1, y);
    }
    else if (orientation == 2)
    {
        if (x<0 || x> this->width)
        {
            ////cout << "Invalid coords!!!" << endl;
            return false;
        }
        else if (y<0 || y> this->height - 2)
        {
            //cout << "Invalid coords!!!<< endl;
            return false;
        }

        return placePart(x, y) && placePart(x, y + 1);

    }
    else
    {
        cout << "Invalid orientation" << endl;
        return false;
    }
}

bool Board::placeShipTriple(int x, int y, int orientation) const
{
    if (orientation == 1)
    {
        if (x<0 || x> this->width - 3)
        {
            //cout << "Invalid coords!!!" << endl;
            return false;
        }
        else if (y<0 || y> this->height)
        {
            //cout << "Invalid coords!!!" << endl;
            return false;
        }

        return placePart(x, y) && placePart(x + 1, y) && placePart(x + 2, y);
    }
    else if (orientation == 2)
    {
        if (x<0 || x> this->width)
        {
            //cout << "Invalid coords!!!" << endl;
            return false;
        }
        else if (y<0 || y> this->height - 3)
        {
            //cout << "Invalid coords!!!" << endl;
            return false;
        }

        return placePart(x, y) && placePart(x, y + 1) && placePart(x, y + 2);

    }
    else
    {
        cout << "Invalid orientation" << endl;
        return false;
    }
}

bool Board::placeShipQuadra(int x, int y, int orientation) const
{
    if (orientation == 1)
    {
        if (x<0 || x> this->width - 4)
        {
            //cout << "Invalid coords!!!" << endl;
            return false;
        }
        else if (y<0 || y> this->height)
        {
            cout << "Invalid coords!!" << endl;
            return false;
        }

        return placePart(x, y) && placePart(x + 1, y) && placePart(x + 2, y) && placePart(x + 3, y);
    }
    else if (orientation == 2)
    {
        if (x<0 || x> this->width)
        {
            //cout << "Invalid coords!!!" << endl;
            return false;
        }
        else if (y<0 || y> this->height - 4)
        {
            //cout << "Invalid coords!!!" << endl;
            return false;
        }

        return placePart(x, y) && placePart(x, y + 1) && placePart(x, y + 2) && placePart(x, y + 3);

    }
    else
    {
        cout << "Invalid orientation" << endl;
        return false;
    }
}

void Board::fillBoardWithEmpties() const
{
    for (int x = 0;x < this->height;x++)
    {
        for (int y = 0;y < this->width;y++)
        {
            table[x][y] = 0;
        }
    }
}

void Board::fillWithRandomShips()
{


    cout<<"Generating the sea..."<<endl;
    sleep(1);

    int randomX, randomY, randomOrientation;

        fillBoardWithEmpties();
        int singleShipsLeft = 4; //4
        int doubleShipsLeft = 3; //3
        int tripleShipsLeft = 2; //2
        int quadripleShipsLeft = 1;
        srand(static_cast<unsigned int>(time(nullptr)));
        aliveFields = 0;

            for (; aliveFields != 4;) {
                randomX = rand() % 10;
                randomY = rand() % 10;
                randomOrientation = rand() % 2 + 1;
                if (canShipBePlacedProperly(randomX, randomY, 4, randomOrientation)) {
                    placeShip(randomX, randomY, randomOrientation, "quadra");
                    quadripleShipsLeft--;
                }
            }
        //triple
        for (; aliveFields != 10;) {
            randomX = rand() % 10;
            randomY = rand() % 10;
            randomOrientation = rand() % 2 + 1;
            if (canShipBePlacedProperly(randomX, randomY, 3, randomOrientation)) {
                placeShip(randomX, randomY, randomOrientation, "triple");
                tripleShipsLeft--;
            }
        }
        //double ships placing
        for (; aliveFields != 16;) {
            randomX = rand() % 10;
            randomY = rand() % 10;
            randomOrientation = rand() % 2 + 1;
            if (canShipBePlacedProperly(randomX, randomY, 2, randomOrientation)) {
                placeShip(randomX, randomY, randomOrientation, "double");
                doubleShipsLeft--;
            }
        }
        //single ships placing
        for (; aliveFields != 20;) {
            randomX = rand() % 10;
            randomY = rand() % 10;
            randomOrientation = rand() % 2 + 1;
            if (canShipBePlacedProperly(randomX, randomY, 4, randomOrientation)) {
                placeShip(randomX, randomY, randomOrientation, "single");
                singleShipsLeft--;
            }
        }
    putTreasure();
}

bool Board::canShipBePlacedProperly(int x, int y, int shipType, int orientation) const
{
    if(shipType == 1)
    {
        return canPartBePlacedProperly(x, y);
    }
    else if(shipType == 2)
    {
        if (orientation == 1)
        {
            return canPartBePlacedProperly(x, y) && canPartBePlacedProperly(x+1,y);
        }
        else if(orientation == 2)
        {
            return canPartBePlacedProperly(x, y) && canPartBePlacedProperly(x, y+1);
        }

    }
    else if(shipType == 3)
    {
        if (orientation == 1)
        {
            return canPartBePlacedProperly(x, y) && canPartBePlacedProperly(x + 1, y) && canPartBePlacedProperly(x + 2, y);
        }
        else if (orientation == 2)
        {
            return canPartBePlacedProperly(x, y) && canPartBePlacedProperly(x, y + 1) && canPartBePlacedProperly(x, y+2);
        }
    }
    else if(shipType == 4)
    {
        if (orientation == 1)
        {
            return canPartBePlacedProperly(x, y) && canPartBePlacedProperly(x + 1, y) && canPartBePlacedProperly(x + 2, y) && canPartBePlacedProperly(x + 3, y);
        }
        else if (orientation == 2)
        {
            return canPartBePlacedProperly(x, y) && canPartBePlacedProperly(x, y+1) && canPartBePlacedProperly(x, y+2) && canPartBePlacedProperly(x, y+3);
        }
    }

    return false;
}

void Board::useMissle(int x, int y)
{
    for(int x2 = 0;x2<10;x2++)
    {
        if(this->table[x2][y] == 1 or this->table[x2][y] == 6)
        {
            this->shoot(x2,y);
        }
        else if(this->table[x2][y] == 0)
        {
            this->table[x2][y] = 3;
        }
    }

    for(int y2 = 0;y2<10;y2++)
    {
        if(this->table[x][y2] == 1)
        {
            this->shoot(x,y2);
        }
        else if(this->table[x][y2] == 0)
        {
            this->table[x][y2] = 3;
        }
    }
    missleCounter --;
}

void Board::putTreasure()
{
    while(true)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int x = std::rand() % 10;
        int y = std::rand() % 10;


        int i, j;
        i = x - 1 < 0 ? 0 : x - 1;
        j = y - 1 < 0 ? 0 : y - 1;

        int i2, j2;
        i2 = x + 1 > 9 ? 9 : x + 1;
        j2 = y + 1 > 9 ? 9 : y + 1;

        bool czyMoznaStawiac = true;
        for (;i<=i2;i++)
        {
            for (;j<=j2;j++)
            {
                if(table[i][j] == 1)
                {
                    czyMoznaStawiac = false;
                }
            }
            j = y - 1 < 0 ? 0 : y - 1;
        }
        if(czyMoznaStawiac)
        {
            //cout<<"Stawiamy skarb na "<<x<<" "<<y<<endl;
            table[x][y] = 6;
            return;
        }

    }

}

//szuka cyfry
int Board::coordX(string ciag)
{
    for (char znak : ciag)
    {
        if (std::isdigit(znak))
        {
            //std::cout << "Znaleziono cyfrę: " << int(znak)-48 << std::endl;
            return int(znak)-48;
        }
    }

    cout<<"ERRORRRRR"<<endl;
    return 0;
}

//szuka litery
int Board::coordY(string ciag)
{
    for(int i=0;i<ciag.length();i++)
    {
        char znak = ciag[i];
        //cout<<znak<<endl;
        if (std::isalpha(znak))
        {
            //std::cout << "Znaleziono literę: " << znak << std::endl;
            return zamienNaKoord(znak);
        }
    }

    cout<<"ERRORRRRR"<<endl;
    return 0;
}

int Board::zamienNaKoord(char znak)
{
    int cyfra = std::toupper(znak) - 'A';

    //cout<<"Zamieniona litera: "<<cyfra<<endl;
    return cyfra;
}

int Board::handleCoordInput(string ciag, char ktoryKoord)
{
    if(ktoryKoord == 'x')
    {
        return coordX(ciag);
    }

    return coordY(ciag);
}
