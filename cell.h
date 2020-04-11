#ifndef CELL_H
#define CELL_H
#include "../../Graph_lib/Simple_window.h"
#include "../../Graph_lib/Graph.h"
#include <sstream>
using namespace std;
using namespace Graph_lib;

struct Figure;

struct Cell : Graph_lib::Button
{

    Cell (Point xy, Graph_lib::Callback cb);
    void attach (Graph_lib::Window & win) override;
    Point center () const { return Point { loc.x + width / 2, loc.y + height / 2}; }
    void attach_figure (Figure& f);
    Figure& detach_figure ();
    const Figure& figure () const { return * fig; }
    bool has_figure () const { return fig != nullptr; }

    static constexpr int size = 100;

private:
    Figure* fig{nullptr};
};

struct Figure
{
    virtual ~Figure () = default;
    virtual void attach (const Cell & c) = 0;
    void detach () {cell = nullptr;}
    bool is_attached () const { return cell !=nullptr; }
protected:
    const Cell* cell { nullptr };
};

struct Number : public Figure, public Text
{
    Number (Graph_lib::Window & win, int num);
    void attach (const Cell & c) override;
    const int number;
};

#endif // CELL_H
