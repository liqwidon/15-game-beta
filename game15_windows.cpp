//implementation of all the windows
#include "game15_windows.h"

////////////////////////////////////////////////////////////////////////////////

StartWindow::StartWindow (Wrapper* wrapper, Point xy, const std::string& title)
    : Window        { xy, GameGUI::width, GameGUI::height, title }
    , next_button   { Graph_lib::Point {x_max() / 2 - 50, y_max() / 2 - 50}, 100, 100, "->play", cb_next }
    , wrapper       { wrapper }
    , background    { Point { 0, 0 }, x_max(), y_max() }
    , button        { Point { 215, 180 }, 100, 100 }
    , label         { Point { 5, 15 },    "</twoalex>" }
    , greetings     { Point { 45, 100 },  "Hello, stranger! This is 15 game, simple and interesting" }
    , invite_to_play{ Point { 150, 160 }, "Press button, to start your adventure" }
{
    size_range(GameGUI::width, GameGUI::height, GameGUI::width, GameGUI::height);
    attach(next_button);
    attach(background);
    attach(button);

    background.set_fill_color(FL_CYAN - 9);
    background.set_color(FL_CYAN - 9);
    button.set_fill_color(FL_CYAN - 10);

    greetings.set_font(9);
    greetings.set_font_size(20);

    attach(label);
    attach(invite_to_play);
    attach(greetings);
}

/////////////////////////////////////////////////////////////////////////////////

PlayWindow::PlayWindow (Wrapper* wrapper, Point xy, const std::string& title)
    : Window          { xy, GameGUI::width, GameGUI::height, title }
    , int_count       { 0 }
    , wrapper         { wrapper }
    , quit_button     { Point { x_max() - 70, 0 }, 70, 20, "Quit", cb_quit }
    , restart_button  { Point { x_max() - 70, 20 }, 70, 20, "Restart", cb_restart }
    , goto_end_button { Point { x_max()- 70, y_max() - 20 }, 70, 20, "end", cb_next }
    , quit_txt        { Point { x_max() - 60, 17 }, "Quit" }
    , restart_txt     { Point { x_max() - 60, 37 }, "Restart" }
    , quit_but        { Point { x_max() - 70, 0 }, 70, 20 }
    , restart_but     { Point { x_max() - 70, 20 }, 70, 20 }
    , background      { Point { 0, 0}, GameGUI::width, GameGUI::height }
    , boarder         { }
    , board_lines     { }
    , count_label     { Point {  GameGUI::margin + 4 * GameGUI::button_size + 5, 150  }, "Counter: " }
    , count           { Point {  GameGUI::margin + 4 * GameGUI::button_size + 65, 150 }, "0" }
{
    size_range (GameGUI::width, GameGUI::height, GameGUI::width, GameGUI::height);

    background.set_fill_color(FL_CYAN - 9);
    attach(background);

    for (int i = 0; i < GameGUI::N; ++i)
        for (int j = 0; j < GameGUI::N; ++j)
        {
            img.push_back(new Image(Point{GameGUI::margin + j*GameGUI::button_size,
                                          GameGUI::margin + (GameGUI::N - 1 - i)*GameGUI::button_size}, "pink.jpg"));
            img[img.size()-1].set_mask(Point{ 100, 200 }, 100, 100);
            attach(img[img.size()-1]);
        }
    for (int i = 0; i < GameGUI::N; ++i)
        for (int j = 0; j < GameGUI::N; ++j)
        {
            cells.push_back(new Cell{ Point{GameGUI::margin + j*Cell::size,
                                            GameGUI::margin + (GameGUI::N-1 - i)*Cell::size}, cb_clicked});
            attach(cells[cells.size()-1]);
        }

    for (int i = 0; i < Board::board_size * Board::board_size; ++i)
        figures.push_back(new Number{*this, i});

    boarder.add(Point { GameGUI::margin, GameGUI::margin });
    boarder.add(Point { GameGUI::margin + 4 * GameGUI::button_size, GameGUI::margin });
    boarder.add(Point { GameGUI::margin + 4 * GameGUI::button_size, GameGUI::margin + 4 * GameGUI::button_size });
    boarder.add(Point { GameGUI::margin, GameGUI::margin + 4 * GameGUI::button_size });
    boarder.set_color(FL_DARK_MAGENTA);

    board_lines.add(Point { GameGUI::margin + GameGUI::button_size, GameGUI::margin },
                    Point { GameGUI::margin + GameGUI::button_size, GameGUI::margin + 4 * GameGUI::button_size });
    board_lines.add(Point { GameGUI::margin + 2 * GameGUI::button_size, GameGUI::margin },
                    Point { GameGUI::margin + 2 * GameGUI::button_size, GameGUI::margin + 4 * GameGUI::button_size });
    board_lines.add(Point { GameGUI::margin, GameGUI::margin + GameGUI::button_size },
                    Point { GameGUI::margin + GameGUI::button_size*4, GameGUI::margin + GameGUI::button_size });
    board_lines.add(Point { GameGUI::margin, GameGUI::margin + 2 * GameGUI::button_size },
                    Point { GameGUI::margin + GameGUI::button_size*4, GameGUI::margin + 2 * GameGUI::button_size });
    board_lines.add(Point { GameGUI::margin + 3 * GameGUI::button_size, GameGUI::margin },
                    Point { GameGUI::margin + 3 * GameGUI::button_size, GameGUI::margin + 4 * GameGUI::button_size });
    board_lines.add(Point { GameGUI::margin, GameGUI::margin + 3 * GameGUI::button_size },
                    Point { GameGUI::margin + 4 * GameGUI::button_size, GameGUI::margin + 3 * GameGUI::button_size });
    board_lines.set_color(FL_DARK_MAGENTA);

    quit_txt.set_font_size(16);
    restart_txt.set_font_size(16);

    attach(restart_button);
    attach(quit_button);
    attach(quit_but);
    attach(restart_but);
    attach(quit_txt);
    attach(restart_txt);
    attach(goto_end_button);
    attach(boarder);
    attach(board_lines);
    attach(count_label);
    attach(count);
    applyChanges();
}

void PlayWindow::clicked(Address widget)
{
    Fl_Widget & w = reference_to<Fl_Widget> (widget);

    if (core[0] - 4 == at(Point { w.x(), w.y() }))
    {
         core.up();
    }
    if (core[0] + 4 == at(Point { w.x(), w.y() }))
    {
         core.down();
    }
    if (core[0] - 1 == at(Point { w.x(), w.y() }))
    {
         core.left();
    }
    if (core[0] + 1 == at(Point { w.x(), w.y() }))
    {
         core.right();
    }

    int_count = core.get_count();

    applyChanges();

    if (core.is_Solved())
    {
        next_window();
        return;
    }

    Fl::redraw();
}

int PlayWindow::at (Point p)
{
    int i = (p.y - GameGUI::margin) / GameGUI::button_size;
    int j = (p.x - GameGUI::margin) / GameGUI::button_size;
    return i*GameGUI::N + j;
}

void PlayWindow::applyChanges()
{
    for (int i = 0; i < Board::board_size*Board::board_size; ++i)
        if (cells[i].has_figure()) cells[i].detach_figure();
    for (int i = 0; i < Board::board_size; ++i)
    {
        for (int j = 0; j < Board::board_size; ++j)
        {
            if (core.get_Number(Board::board_size - i - 1, j) != 0)
            cells[i*Board::board_size + j].attach_figure(figures[core.get_Number(Board::board_size - i - 1, j)]);
        }
    }

    stringstream ss;
    ss << int_count;
    count.set_label(ss.str());
}

////////////////////////////////////////////////////////////////////////////

EndWindow::EndWindow (Wrapper* wrapper, Point xy, const std::string& title, int counter)
    : Window            { xy, GameGUI::width, GameGUI::height, title }
    , wrapper           { wrapper }
    , restart_button    { Graph_lib::Point{ x_max() / 2 - x_max() / 4 - 50, y_max() / 2 - 50 }
                        , 100, 100, "restart", cb_restart }
    , next_button       { Graph_lib::Point{ x_max() / 2 + x_max() / 4 - 50, y_max() / 2 - 50 }
                        , 100, 100, "quit", cb_quit }
    , background        { Point { 0, 0 }, x_max(), y_max() }
    , restart_rectangle { Point { x_max() / 2 - x_max() / 4 - 48, y_max() / 2 - 50}, 100, 100 }
    , quit_rectangle    { Point { x_max() / 2 + x_max() / 4 - 52, y_max() / 2 - 50}, 100, 100 }
    , winner_txt        { Point { 185, 130 }, "You are the winner" }
    , label             { Point { 0, 15 },    "thx for using </twoalex> products" }
    , quit_txt          { Point { 355, 170 }, "Press to quit" }
    , restart_txt       { Point { 90, 170 },  "Press to restart" }
    , count             { Point {225, 350},   "Moves number: "}
    , count_out         { Point {325, 350},   ""}
    , count_moves       { counter }
{
    size_range(GameGUI::width, GameGUI::height, GameGUI::width, GameGUI::height);
    background.set_fill_color(FL_CYAN - 9);
    quit_rectangle.set_fill_color(FL_CYAN - 10);
    restart_rectangle.set_fill_color(FL_CYAN - 10);
    winner_txt.set_font_size(20);
    label.set_font_size(14);
    quit_txt.set_font_size(14);
    restart_txt.set_font_size(14);

    attach(next_button);
    attach(restart_button);

    attach(background);
    attach(quit_rectangle);
    attach(restart_rectangle);
    attach(winner_txt);
    attach(label);
    attach(quit_txt);
    attach(restart_txt);
    attach(count);

    stringstream ss;
    ss << count_moves;
    count_out.set_label(ss.str());
    attach(count_out);
}

////////////////////////////////////////////////////////////////////////////

GameGUI::GameGUI (Point xy, const std::string& title)
    :lt { xy }, name { title }
{
    start_win = new StartWindow {this, lt, name};
    play_win  = new PlayWindow  {this, Point(start_win->x_root(), start_win->y_root()), name};
    play_win->hide();
}

void GameGUI::restart()
{
    play_win->restart();
    play_win->position(end_win->x_root(), end_win->y_root());
    play_win->show();
    end_win->hide();
    delete end_win;
}

void GameGUI::play()
{
    play_win->position(start_win->x_root(), start_win->y_root());
    play_win->show();
    delete start_win;
}

void GameGUI::end(int result)
{
    end_win = new EndWindow {this, Point(play_win->x_root(), play_win->y_root()), name, result};
    end_win->show();
    play_win->hide();
}

void GameGUI::quit_play()
{
    play_win->hide();
    delete play_win;
}

void GameGUI::quit_end()
{
    delete play_win;
    end_win->hide();
    delete end_win;
}


