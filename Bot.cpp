#include "Bot.h"
#include <iostream>


void Bot::takeShot(Board& board)
{
    //easy difficulty
    if(difficulty == 0)
    {
        randomShot(board);
    }
    //world champion difficulty
    else
    {
        //this_thread::sleep_for(std::chrono::milliseconds(1200));
        cout<<"Computer turn... ";
        this_thread::sleep_for(std::chrono::milliseconds(1200));

        if(board.bombCounter > 0)
        {

            int maksymalne=0;
            int buforX;
            int buforY;
            //tu szuka
            for(int i=1;i<=9;i++)
            {
                for(int j=1;j<=9;j++)
                {
                    int licznik =0;

                    for(int a = i-1;a<=i+1;a++)
                    {
                        for(int b = j-1;b<=j+1;b++)
                        {
                            if(board.table[a][b] == 0 || board.table[a][b] == 1){licznik ++;}
                        }
                    }
                    if(maksymalne < licznik)
                    {
                        maksymalne = licznik;
                        buforX = i;
                        buforY = j;
                    }
                    if(maksymalne == 9 ) break;
                }
                if(maksymalne == 9 ) break;
            }
            //tu strzela
            cout<<"Using napalm at "<<buforX<<" "<<buforY<<endl;
            for(int i=buforX-1;i<=buforX+1;i++)
            {
                for(int j=buforY-1;j<=buforY+1;j++)
                {
                    if(i>=0 && i<10 && j>=0 && j<10)
                    {
                        if(board.table[i][j] == 1)
                        {
                            board.shoot(i,j);
                        }
                        else if(board.table[i][j] == 0)
                        {
                            board.table[i][j] = 3;
                        }

                    }
                }
            }
            board.bombCounter --;

            return;
        }

        if(board.missleCounter > 0)
        {
            int maksymalne = 0;
            int buforX;
            int buforY;
            int licznik=0;
            int i,j;

            for(i=0;i<10;i++)
            {
                for(j=0;j<10;j++)
                {
                    licznik=0;
                    for(int x2 = 0;x2<10;x2++)
                    {
                        if(board.table[x2][j] == 1 || board.table[x2][j] == 0)
                        {
                            licznik++;
                        }
                    }

                    for(int y2 = 0;y2<10;y2++)
                    {
                        if(board.table[i][y2] == 1 || board.table[i][y2] == 0)
                        {
                            licznik++;
                        }
                    }
                    if(licznik > maksymalne)
                    {
                        maksymalne = licznik;
                        buforX = i;
                        buforY = j;
                        if(maksymalne == 19) break;
                    }
                }
            }
            cout<<"Shooting missle "<<buforX<<" "<<buforY<<endl;
            board.useMissle(buforX,buforY);
            return;
        }

        bool canShotFurther = false;
        int x = ruchy[nrRuchu][0];
        int y = ruchy[nrRuchu][1];
        canShotFurther = true;
        while(canShotFurther)//drugi strzał i dalej
        {
            if(this->nrRuchu<50)
            {
                int x = ruchy[nrRuchu][0];
                int y = ruchy[nrRuchu][1];
                if(board.table[x][y] != 0 && board.table[x][y] != 1)
                {
                    this->nrRuchu++;
                    canShotFurther = true;
                }
                else
                {
                    canShotFurther = board.shoot(x, y);
                    this->nrRuchu++;
                }
                //counter++;
            }
            else
            {
                canShotFurther = true;
                while(canShotFurther)
                {
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 10; j++) {
                            if(board.table[x][y] != 0 && board.table[x][y] != 1)
                            {
                                canShotFurther = board.shoot(i, j);
                            }
                        }
                    }
                }
            }
        }
        //cout<<"Computer missed."<<endl;
    }

}

void Bot::fillMoveTable()
{
    /*
    int counter = 0;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(counter%2==0)
            {
                ruchy[nrRuchu][0]=i;
                ruchy[nrRuchu][1]=j;
                //cout<<i<<" "<<j<<endl;
                nrRuchu++;
            }
            counter++;
        }
        counter+=1;
    }
    nrRuchu = 0;
     */
}

void Bot::randomShot(Board& board)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int randomX, randomY;
    randomX = rand() % 10;
    randomY = rand() % 10;

    for (;board.shoot(randomX, randomY);)
    {
        randomX = rand() % 10;
        randomY = rand() % 10;
    }
}


