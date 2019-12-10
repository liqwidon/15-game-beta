//implementation of all the windows
#include "game15_windows.h"

////////////////////////////////////////////////////////////////////////////////

StartWindow::StartWindow (Wrapper* wrapper, Point xy, const std::string& title)
    : Window        { xy, GameGUI::width, GameGUI::height, title }
    , next_button   { Graph_lib::Point {x_max() / 2 - 50, y_max() / 2 - 50}, 100, 100, "->play", cb_next }
    , wrapper       { wrapper }
    , background    { Point { 0, 0 }, x_max(), y_max() }
    , but           { Point { 215, 180 }, 100, 100 }
    , label         { Point { 5, 15 },    "</twoalex>" }
    , greetings     { Point { 45, 100 },  "Hello, stranger! This is 15 game, simple and interesting" }
    , invite_to_play{ Point { 150, 160 }, "Press button, to start your adventure" }
{
    size_range(GameGUI::width, GameGUI::height, GameGUI::width, GameGUI::height);
    attach(next_button);
    attach(background);
    attach(but);

    background.set_fill_color(FL_CYAN - 9);
    background.set_color(FL_CYAN - 9);
    but.set_fill_color(FL_CYAN - 10);

    greetings.set_font(9);
    greetings.set_font_size(20);

    attach(label);
    attach(invite_to_play);
    attach(greetings);
}

/////////////////////////////////////////////////////////////////////////////////

PlayWindow::PlayWindow (Wrapper* wrapper, Point xy, const std::string& title)
    : Window         { xy, GameGUI::width, GameGUI::height, title }
    , wrapper        { wrapper }
    , quit_button    { Point { x_max() - 70, 0 }, 70, 20, "Quit", cb_quit }
    , restart_button { Point { x_max() - 70, 20 }, 70, 20, "Restart", cb_restart }
    , quit_but       { Point { x_max() - 70, 0 }, 70, 20 }
    , restart_but    { Point { x_max() - 70, 20 }, 70, 20 }
    , goto_end       { Point { x_max()- 70, y_max() - 20 }, 70, 20, "end", cb_next }
    , quit_txt       { Point { x_max() - 60, 17 }, "Quit" }
    , all            { Point { 0, 0}, GameGUI::width, GameGUI::height }
    , restart_txt    { Point { x_max() - 60, 37 }, "Restart" }
    , boarder        { }
    , line1          { Point { GameGUI::margin + GameGUI::button_size, GameGUI::margin },
                       Point { GameGUI::margin + GameGUI::button_size, GameGUI::margin + 4 * GameGUI::button_size } }
    , line2          { Point { GameGUI::margin + 2 * GameGUI::button_size, GameGUI::margin },
                       Point { GameGUI::margin + 2 * GameGUI::button_size, GameGUI::margin + 4 * GameGUI::button_size } }
    , line3          { Point { GameGUI::margin, GameGUI::margin + GameGUI::button_size },
                       Point { GameGUI::margin + GameGUI::button_size*4, GameGUI::margin + GameGUI::button_size } }
    , line4          { Point { GameGUI::margin, GameGUI::margin + 2 * GameGUI::button_size },
                       Point { GameGUI::margin + GameGUI::button_size*4, GameGUI::margin + 2 * GameGUI::button_size } }
    , line5          { Point { GameGUI::margin + 3 * GameGUI::button_size, GameGUI::margin },
                       Point { GameGUI::margin + 3 * GameGUI::button_size, GameGUI::margin + 4 * GameGUI::button_size } }
    , line6          { Point { GameGUI::margin, GameGUI::margin + 3 * GameGUI::button_size },
                       Point { GameGUI::margin + 4 * GameGUI::button_size, GameGUI::margin + 3 * GameGUI::button_size } }
{
    size_range (GameGUI::width, GameGUI::height, GameGUI::width, GameGUI::height);

    all.set_fill_color(FL_CYAN - 9);
    attach(all);

    for (int i = 0; i < GameGUI::N; ++i)
        for (int j = 0; j < GameGUI::N; ++j)
        {
            img.push_back(new Image(Point{GameGUI::margin + j*GameGUI::button_size, GameGUI::margin + (GameGUI::N - 1 - i)*GameGUI::button_size}, "pink.jpg"));
            img[img.size()-1].set_mask(Point{ 100, 200 }, 100, 100);
            attach(img[img.size()-1]);
        }
    for (int i = 0; i < GameGUI::N; ++i)
        for (int j = 0; j < GameGUI::N; ++j)
        {
            buttons.push_back (new Button(Point{GameGUI::margin + j*GameGUI::button_size, GameGUI::margin + (GameGUI::N - 1 - i)*GameGUI::button_size}, 100, 100, "", cb_clicked));
            attach(buttons[buttons.size() - 1]);
        }

    boarder.add(Point { GameGUI::margin, GameGUI::margin });
    boarder.add(Point { GameGUI::margin + 4 * GameGUI::button_size, GameGUI::margin });
    boarder.add(Point { GameGUI::margin + 4 * GameGUI::button_size, GameGUI::margin + 4 * GameGUI::button_size });
    boarder.add(Point { GameGUI::margin, GameGUI::margin + 4 * GameGUI::button_size });
    boarder.set_color(FL_DARK_MAGENTA);
    line1.set_color(FL_DARK_MAGENTA);
    line2.set_color(FL_DARK_MAGENTA);
    line3.set_color(FL_DARK_MAGENTA);
    line4.set_color(FL_DARK_MAGENTA);
    line5.set_color(FL_DARK_MAGENTA);
    line6.set_color(FL_DARK_MAGENTA);
    quit_txt.set_font_size(16);
    restart_txt.set_font_size(16);

    attach(restart_button);
    attach(quit_button);
    attach(quit_but);
    attach(restart_but);
    attach(quit_txt);
    attach(restart_txt);
    attach(goto_end);
    attach(boarder);
    attach(line1);
    attach(line2);
    attach(line3);
    attach(line4);
    attach(line5);
    attach(line6);

//            core.auto_Win(); //for test EndWindow

}

void PlayWindow::clicked(Address widget)
{
    Fl_Widget & w = reference_to<Fl_Widget> (widget);

    if(core[0] - 4 == at(Point { w.x(), w.y() }))
    {
        core.up();
    }
    if(core[0] + 4 == at(Point { w.x(), w.y() }))
    {
        core.down();
    }
    if(core[0] - 1 == at(Point { w.x(), w.y() }))
    {
        core.left();
    }
    if(core[0] + 1 == at(Point { w.x(), w.y() }))
    {
        core.right();
    }
    if(core.is_Solved())
    {
        next_window();
    }

    Fl::redraw();
}

int PlayWindow::at (Point p)
{
    int i = (p.y - GameGUI::margin) / GameGUI::button_size;
    int j = (p.x - GameGUI::margin) / GameGUI::button_size;
    return i*GameGUI::N + j;
}

void PlayWindow::draw()
{
    Window::draw();
    string str = core.create_Line();
    int k = 0;
    string str_buffer;
    for (int i = 0; i < GameGUI::N; ++i)
        for (int j = 0; j < GameGUI::N; ++j)
        {
            str_buffer = "";
            if (str[0] != ' ' && str[1] != ' ' && k == 0)
            {
                str_buffer += str[0];
                str_buffer += str[1];
                k += 2;
            }
            else if (str[0] != ' ' && str[1] == ' ' && k == 0 )
            {
                str_buffer += str[0];
                k++;
            }
            else if (str[k] == ' ' && ((str[k+1] != ' ') && str[k+2] != ' '))
            {
                str_buffer += str[k+1];
                str_buffer += str[k+2];
                k += 3;
            }
            else
            {
                str_buffer += str[k+1];
                k += 2;
            }
            if(str_buffer != "0")
            fl_draw (str_buffer.c_str(), GameGUI::margin + j*GameGUI::button_size + 45, GameGUI::margin + i*GameGUI::button_size + 50);
        }
}

////////////////////////////////////////////////////////////////////////////

EndWindow::EndWindow (Wrapper* wrapper, Point xy, const std::string& title)
    : Window           { xy, GameGUI::width, GameGUI::height, title }
    , wrapper          { wrapper }
    , next_button      { Graph_lib::Point{ x_max() / 2 + x_max() / 4 - 50, y_max() / 2 - 50 }
                       , 100, 100, "quit", cb_quit }
    , restart_button   { Graph_lib::Point{ x_max() / 2 - x_max() / 4 - 50, y_max() / 2 - 50 }
                       , 100, 100, "restart", cb_restart }
    , background       { Point { 0, 0 }, x_max(), y_max() }
    , restart_rectangle{ Point { x_max() / 2 - x_max() / 4 - 48, y_max() / 2 - 50}, 100, 100 }
    , quit_rectangle   { Point { x_max() / 2 + x_max() / 4 - 52, y_max() / 2 - 50}, 100, 100 }
    , winner           { Point { 185, 130 }, "You are the winner" }
    , label            { Point { 0, 15 },    "thx for using </twoalex> products" }
    , quit_txt         { Point { 355, 170 }, "Press to quit" }
    , restart_txt      { Point { 90, 170 },  "Press to restart" }
{
    size_range(GameGUI::width, GameGUI::height, GameGUI::width, GameGUI::height);
    background.set_fill_color(FL_CYAN - 9);
    quit_rectangle.set_fill_color(FL_CYAN - 10);
    restart_rectangle.set_fill_color(FL_CYAN - 10);
    winner.set_font_size(20);
    label.set_font_size(14);
    quit_txt.set_font_size(14);
    restart_txt.set_font_size(14);

    attach(next_button);
    attach(restart_button);

    attach(background);
    attach(quit_rectangle);
    attach(restart_rectangle);
    attach(winner);
    attach(label);
    attach(quit_txt);
    attach(restart_txt);
}

////////////////////////////////////////////////////////////////////////////

GameGUI::GameGUI (Point xy, const std::string& title)
    :lt{xy}, name{title}
{
    cur_win = new StartWindow {this, lt, name};
}

void GameGUI::restart()
{
    delete cur_win;
    cur_win = new PlayWindow  {this, lt, name};
}

void GameGUI::play()
{
    delete cur_win;
    cur_win = new PlayWindow  {this, lt, name};
}

void GameGUI::end()
{
    delete cur_win;
    cur_win = new EndWindow   {this, lt, name};
}
