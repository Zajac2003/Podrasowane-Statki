#ifndef BOARD_H
#define BOARD_H


#include <iostream>
#include <cstdlib> // Dla funkcji rand()
#include <ctime>   // Dla funkcji time()
#include <thread>  // Dla std::this_thread::sleep_for
#include <chrono>
#include <conio.h>
#include <unistd.h>
using namespace std;
#pragma once
//what a field number means
//0 - empty (no ship part)
//1 - alive ship part
//2 - dead ship part
//3 - field with missed shot
//4 - completely dead ship
//5 - auto-filled nothing
//6 - unopened treasure
//7 - opened treasure


class Board
{
    public:
        int** table;
        int width, height;
        int aliveFields = 0;
        int bombCounter = 1;
        int missleCounter = 1;
        int treasureCounter = 0;
        int quadraCounter = 1;
        int tripleCounter = 2;
        int doubleCounter = 3;
        int singleCounter = 4;
        //-
        Board(int width, int height);

        int coordX(string ciag);

        int coordY(string ciag);

        int zamienNaKoord(char znak);

        //checked
        bool shoot(int x, int y);

        void putTreasure();

        void useTreasure(int x, int y)
        {
            treasureCounter--;
            cout<<"The treasure don't do anything rghtnw :C sry"<<endl;
        }

        //checked
        void printBoard(int mode) const;

        int handleCoordInput(string ciag, char ktoryKoord);

        //mostly checked
        bool areCoordinatesValid(int x, int y) const;

        void useBomb(int x, int y);

        void useMissle(int x, int y);

        bool placeShip(int x, int y, int orientation,string type);

        void shipCreator();

        bool canPartBePlacedProperly(int x, int y) const;

        //checked
        void fillBoardWithEmpties() const;

        void fillWithRandomShips();
private:
        bool canShipBePlacedProperly(int x, int y, int shipType, int orientation) const;

        bool placePart(int x, int y) const;

        bool placeShipSingle(int x, int y, int orientation) const;

        bool placeShipDouble(int x, int y, int orientation) const;

        bool placeShipTriple(int x, int y, int orientation) const;

        bool placeShipQuadra(int x, int y, int orientation) const;
};

#endif
