/*
Programm Game15 using fltk
Contains 3 windows with unique designe from </twoalex>
The implementation is described in other files via comments
*/
#include <iostream>
#include "game15_windows.h"

int main()
{
    GameGUI test(Point {420, 200}, "Game 15 close beta");
    return gui_main();
}
