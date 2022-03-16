#include "Color16_Screen.h"

void Color16_Screen::fill(int x1, int y1, int x2, int y2, Color16 color)
{
    addr_set(x1, y1, x2, y2);
    for (int i = y1; i <= y2; i++)
        for (int j = x1; j <= x2; j++)
            write_data(color);
}

void Color16_Screen::clear(Color16 color)
{
    fill(0, 0, width - 1, height - 1, color);
}

void Color16_Screen::draw_point_big(int x, int y, Color16 color)
{
    fill(x - 1, y - 1, x + 1, y + 1, color);
}

void Color16_Screen::draw_point(int x, int y, Color16 color)
{
    addr_set(x, y, x, y);
    write_data(color);
}

#define max(a, b) (((a) > (b)) ? (a) : (b))

class LinePainter
{
public:
    LinePainter(Color16_Screen &target_screen, int x1, int y1, int x2, int y2, Color16 color1)
        : screen(target_screen), x(x1), y(y1), xerr(0), yerr(0), deltax(x2 - x1), deltay(y2 - y1), color(color1)
    {
        prepare();
    }

    void draw_line();

private:
    void draw_step();
    void prepare();

    Color16_Screen &screen;
    int deltax;
    int deltay;
    int distance;
    int incx;
    int incy;
    int x;
    int y;
    int xerr;
    int yerr;
    Color16 color;
};

void LinePainter::prepare()
{
    if (deltax < 0)
    {
        incx = -1;
        deltax = -deltax;
    }
    else
    {
        incx = 1;
    }
    if (deltay < 0)
    {
        incy = -1;
        deltay = -deltay;
    }
    else
    {
        incy = 1;
    }
    distance = max(deltax, deltay);
}

void LinePainter::draw_step()
{
    screen.draw_point(x, y, color);
    xerr += deltax;
    if (xerr >= distance)
    {
        xerr -= distance;
        x += incx;
    }
    yerr += deltay;
    if (yerr >= distance)
    {
        yerr -= distance;
        y += incy;
    }
}

void LinePainter::draw_line()
{
    for (int i = 0; i <= distance; i++)
        draw_step();
}

void Color16_Screen::draw_line(int x1, int y1, int x2, int y2, Color16 color)
{
    LinePainter p(*this, x1, y1, x2, y2, color);
    p.draw_line();
}

void Color16_Screen::draw_rectangle(int x1, int y1, int x2, int y2, Color16 color)
{
    draw_line(x1, y1, x2, y1, color);
    draw_line(x2, y2, x1, y2, color);

    draw_line(x1, y2, x1, y1, color);
    draw_line(x2, y1, x2, y2, color);
}

void Color16_Screen::draw_point_x(int x, int y, int a, int b, Color16 color)
{
    draw_point(x - a, y + b, color);
    draw_point(x + a, y - b, color);

    draw_point(x - a, y - b, color);
    draw_point(x + a, y + b, color);
}

void Color16_Screen::draw_circle(int x, int y, int r, Color16 color)
{
    int a = 0, b = r;
    while (a <= b)
    {
        draw_point_x(x, y, a, b, color);
        draw_point_x(x, y, b, a, color);
        a++;
        if ((a * a + b * b) > (r * r))
            b--;
    }
}