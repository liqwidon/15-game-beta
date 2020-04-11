#ifndef CORE_H
#define CORE_H

#include "../../Graph_lib/Graph.h"
#include "../../Graph_lib/Simple_window.h"
#include <time.h>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;
using namespace std;
using namespace Graph_lib;

struct Board
{
    static constexpr int board_size = 4;
    static_assert (board_size == 4, "wrong const value: board_size");
    int & operator() (int i, int j)
    {
        if(i < 0 || i >=  board_size || j < 0 || j >= board_size ) throw ("array size error");
        return board[size_t(board_size * i) + size_t(j)];
    }
    int operator() (int i, int j) const
    {
        if(i < 0 || i >=  board_size || j < 0 || j >= board_size ) throw ("array size error");
        return board[size_t(board_size * i)  + size_t(j)];
    }

//    int& operator() (int i)
//    {
//        if (i >= board_size*board_size || i < 0) throw runtime_error("Board: Invalid index");
//        return board[i];
//    }
//    int operator() (int i) const
//    {
//        if (i >= board_size*board_size || i < 0) throw runtime_error("Board: Invalid index");
//        return board[i];
//    }

private:
     array<int, board_size * board_size> board; //board i, j shows ...
};

class Game15Core
{
    int conf[16]; //conf[i] shows where i number is located / нельзя заменить на просто массив board?! нельзя, нет нужного оператора
    int counter = 0; //moves counter;

    Board board;

    void set_random(); // новая генерация работает неплохо

public:
    int operator[](int i) const
    {
        return conf[i];
    }

    Game15Core(); //constructor

    void restart();
    bool is_Solved(); // check if board is completed
    bool is_Solvable() const;
    int  get_Number(int i, int j) const; //returns number from 0 to 15

    int  get_count () const { return counter; }

    //movements of '0'
    void up();
    void down();
    void left();
    void right();
};


#endif // CORE_H
