#include "cell.h"

Cell::Cell (Point xy, Callback cb)
    : Button{ xy, size, size, "", cb }
{}

void Cell::attach (Graph_lib::Window & win)
{
    Button::attach(win);
}

void Cell ::attach_figure (Figure& f)
{
    if (fig)
        throw std::runtime_error("Already has a figure");
    fig = &f;
    f.attach (*this);
}

Figure& Cell :: detach_figure ()
{
    if (fig)
    {
        Figure* buf = fig;
        fig = nullptr;
        buf -> detach();

        return *buf;
    }
    throw std::runtime_error("error");
}

Number::Number (Graph_lib :: Window& win, int num)
    : Text{Point{0, 0}, ""}
    , number{num}
{
    stringstream ss;
    ss << number;
    set_label(ss.str());
    win.attach (*this);
}

void Number :: attach (const Cell& c)
{
    if (is_attached()) throw std :: runtime_error ("error");
    cell = &c;
    set_point(0, Point{c.center().x, c.center().y});
}





