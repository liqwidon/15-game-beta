//file with windows for game15
//Wrapper -> GameGUI
//Window -> StartWindow
//Window -> PlayWindow
//Window -> EndWindow

#ifndef GAME15_WINDOW_H
#define GAME15_WINDOW_H
#include "core.h"

////////////////////////////////////////////////////////////////////

class Wrapper
{
public:
    virtual ~Wrapper () = default;
    virtual void restart() = 0;
    virtual void play() = 0;
    virtual void end() = 0;
};

class StartWindow : public Graph_lib::Window
{
public:
    StartWindow (Wrapper* wrapper, Point xy, const std::string& title);

    Graph_lib::Button next_button;

private:
    Wrapper* wrapper;
    Graph_lib::Rectangle background;
    Graph_lib::Rectangle but;
    Text label;
    Text greetings;
    Text invite_to_play;

    static void cb_next(Graph_lib::Address, Graph_lib::Address addr)
    {
        static_cast<StartWindow*>(addr)->next_window();
    }

    void next_window(){ wrapper->play(); }
};

///////////////////////////////////////////////////////////////////

class PlayWindow : public Graph_lib::Window
{
public:
    PlayWindow (Wrapper* wrapper, Point xy, const std::string& title);

private:
    Wrapper*   wrapper;
    Game15Core core;
    Button     quit_button;
    Button     restart_button;
    Button     goto_end;
    Text       quit_txt;
    Text       restart_txt;
    Graph_lib::Rectangle  quit_but;
    Graph_lib::Rectangle  restart_but;

    Vector_ref<Button>           buttons;
    Vector_ref<Graph_lib::Image> img;
    Graph_lib::Rectangle         all;
    Closed_polyline              boarder;
    Line line1, line2, line3, line4, line5, line6;

    int at (Point p);
    static void cb_next (Address widget, Address win)
    {
        Graph_lib::reference_to <PlayWindow> (win).next_window();
    }

    static void cb_clicked (Address widget, Address win)
    {
        Graph_lib::reference_to <PlayWindow> (win).clicked(widget);
    }

    static void cb_quit (Address widget, Address win)
    {
        Graph_lib::reference_to <PlayWindow> (win).quit();
    }

    static void cb_restart (Address widget, Address win)
    {
        Graph_lib::reference_to <PlayWindow> (win).restart();
    }

    void clicked (Address widget);
    void quit()        { hide(); }
    void next_window() { wrapper->end(); }
    void restart()     { wrapper->restart();}

protected:
    void draw() override;
};

/////////////////////////////////////////////////////////////////////

class EndWindow : public Graph_lib::Window
{
public:
    EndWindow (Wrapper* wrapper, Point xy, const std::string& title);

private:
    Wrapper* wrapper;
    Graph_lib::Button    next_button;
    Graph_lib::Button    restart_button;
    Graph_lib::Rectangle background;
    Graph_lib::Rectangle restart_rectangle;
    Graph_lib::Rectangle quit_rectangle;
    Graph_lib::Text      winner;
    Graph_lib::Text      label;
    Graph_lib::Text      quit_txt;
    Graph_lib::Text      restart_txt;

    static void cb_quit (Graph_lib::Address, Graph_lib::Address addr)
    {
        static_cast<EndWindow*>(addr)->quit();
    }

    static void cb_restart (Graph_lib::Address, Graph_lib::Address addr)
    {
        static_cast<EndWindow*>(addr)->restart();
    }

    void quit() { hide(); }
    void restart() { wrapper->restart(); }
};

//////////////////////////////////////////////////////////////////////

class GameGUI : public Wrapper
{
    Point lt;
    std::string name;

public:
    GameGUI (Point xy, const std::string& title);

    static constexpr int button_size = 100;
    static constexpr int N = 4;
    static constexpr int margin = 30;
    static constexpr int width  = N*button_size + 2*margin + 70;
    static constexpr int height = N*button_size + 2*margin;

    void restart() override;
    void play() override;
    void end() override;

protected:
    Graph_lib::Window* cur_win;
};


#endif // GAME15_WINDOW_H
