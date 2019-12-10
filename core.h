#ifndef CORE_H
#define CORE_H

#include "../Graph_lib/Graph.h"
#include "../Graph_lib/Simple_window.h"
#include <time.h>
#include <iostream>

using namespace std;
using namespace Graph_lib;

class Game15Core
{
    int board[4][4];
    char conf[16]; //conf[i] shows where i number is located
public:
    char operator[](int i) const
    {
        return conf[i];
    }
    Game15Core(); //constructor

    bool is_Solved(); // check if board is completed
    void auto_Win();  //for tests
    bool is_Solvable() const;
    int  get_Number(int i, int j) const; //returns number from 0 to 15
    string create_Line() const; //converts board into string

    //movements of '0'
    void up();
    void down();
    void left();
    void right();

};


#endif // CORE_H
