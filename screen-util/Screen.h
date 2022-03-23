#ifndef __SCREEN_H
#define __SCREEN_H

template <typename ColorType>
class Screen
{
public:
    Screen(int _width, int _height) : width(_width), height(_height) {}

    // the basic drawing functions
    virtual void draw_point(int x, int y, ColorType color) {}

    // the default `fill` is based on `draw_point`, which may be inefficient,
    // override this method when there are more efficient way.
    virtual void fill(int x1, int y1, int x2, int y2, ColorType color);

    void clear(ColorType color);

    void draw_point_big(int x, int y, ColorType color);
    void draw_line(int x1, int y1, int x2, int y2, ColorType color);
    void draw_rectangle(int x1, int y1, int x2, int y2, ColorType color);

    // helper for drawing circle
    void draw_point_x(int x, int y, int a, int b, ColorType color);
    void draw_circle(int x, int y, int r, ColorType color);

protected:
    int width;
    int height;
};

template <typename ColorType>
void Screen<ColorType>::fill(int x1, int y1, int x2, int y2, ColorType color)
{
    for (int i = x1; i < x2; i++)
    {
        for (int j = y1; j < y2; j++)
        {
            draw_point(i, j, color);
        }
    }
}

template <typename ColorType>
void Screen<ColorType>::clear(ColorType color)
{
    fill(0, 0, width, height, color);
}

template <typename ColorType>
void Screen<ColorType>::draw_point_big(int x, int y, ColorType color)
{
    fill(x - 1, y - 1, x + 2, y + 2, color);
}

template <typename T>
static inline T abs(T v)
{
    return v < 0 ? -v : v;
}

template <typename T>
static inline T max(T a, T b)
{
    return a > b ? a : b;
}

template <typename T>
static inline T unit_value(T v)
{
    return v < 0 ? -1 : 1;
}

template <typename ColorType>
class LinePainter
{
public:
    LinePainter(Screen<ColorType> &target_screen, int x1, int y1, int x2, int y2, ColorType color1)
        : screen(target_screen), x(x1), y(y1), delta_x(x2 - x1), delta_y(y2 - y1), color(color1)
    {
        step_x = unit_value(delta_x);
        step_y = unit_value(delta_y);
        delta_x = abs(delta_x);
        delta_y = abs(delta_y);
        distance = max(delta_x, delta_y);
    }

    void draw_line();

private:
    void draw_step();

    Screen<ColorType> &screen;
    int delta_x;
    int delta_y;
    int distance;
    int step_x;
    int step_y;
    int x;
    int y;
    int acc_x = 0;
    int acc_y = 0;
    ColorType color;
};

template <typename ColorType>
void LinePainter<ColorType>::draw_step()
{
    screen.draw_point(x, y, color);
    acc_x += delta_x;
    if (acc_x >= distance)
    {
        acc_x -= distance;
        x += step_x;
    }
    acc_y += delta_y;
    if (acc_y >= distance)
    {
        acc_y -= distance;
        y += step_y;
    }
}

template <typename ColorType>
void LinePainter<ColorType>::draw_line()
{
    for (int i = 0; i <= distance; i++)
    {
        draw_step();
    }
}

template <typename ColorType>
void Screen<ColorType>::draw_line(int x1, int y1, int x2, int y2, ColorType color)
{
    LinePainter<ColorType> p(*this, x1, y1, x2, y2, color);
    p.draw_line();
}

template <typename ColorType>
void Screen<ColorType>::draw_rectangle(int x1, int y1, int x2, int y2, ColorType color)
{
    draw_line(x1, y1, x2, y1, color);
    draw_line(x2, y2, x1, y2, color);

    draw_line(x1, y2, x1, y1, color);
    draw_line(x2, y1, x2, y2, color);
}

template <typename ColorType>
void Screen<ColorType>::draw_point_x(int x, int y, int a, int b, ColorType color)
{
    draw_point(x - a, y + b, color);
    draw_point(x + a, y - b, color);

    draw_point(x - a, y - b, color);
    draw_point(x + a, y + b, color);
}

template <typename ColorType>
void Screen<ColorType>::draw_circle(int x, int y, int r, ColorType color)
{
    int px = r;
    int py = 0;
    int r_square = r * r;
    while (py <= px)
    {
        draw_point_x(x, y, py, px, color);
        draw_point_x(x, y, px, py, color);
        py++;
        if ((py * py + px * px) > r_square)
        {
            px--;
        }
    }
}

#endif
