/*
Programm Game15 using fltk
Contains 3 windows with unique designe from </twoalex>
The implementation is described in other files via comments
Thanks for using </twoalex> products
*/
#include <iostream>
#include "game15_windows.h"


//#include <chrono>
//#include <thread>


using namespace std;

//    using namespace std::this_thread;
//    using namespace std::chrono;
int main()
{
    GameGUI test(Point {420, 200}, "Game 15 close beta");

//    sleep_for(seconds(2));
//    GameGUI test2(Point {100, 100}, "Game 15 close beta");

    return gui_main();
}
