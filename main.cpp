/*
Programm Game15 using fltk
Contains 3 windows with unique designe from </twoalex>
The implementation is described in other files via comments
Thanks for using </twoalex> products
*/

/*
   по сравнению с прошлой версией добавился счетчик ходов, изменился класс с игровым полем(сильно),
   поменялась структура рисования окон, избавились от магических констант и непонятных штук
*/

#include "game15_windows.h"

int main()
{
    GameGUI test(Point {420, 200}, "Game 15 close beta");
    return gui_main();
}

