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
#define abs(v) ((v) < 0 ? (-(v)) : (v))
#define unit_value(ref_value) ((ref_value) < 0 ? -1 : 1)

class LinePainter
{
public:
	LinePainter(Color16_Screen &target_screen, int x1, int y1, int x2, int y2, Color16 color1)
	    : screen(target_screen), x(x1), y(y1), acc_x(0), acc_y(0), delta_x(x2 - x1), delta_y(y2 - y1), color(color1)
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

	Color16_Screen &screen;
	int delta_x;
	int delta_y;
	int distance;
	int step_x;
	int step_y;
	int x;
	int y;
	int acc_x;
	int acc_y;
	Color16 color;
};

void LinePainter::draw_step()
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
	int px = r;
	int py = 0;
	while (py <= px)
	{
		draw_point_x(x, y, py, px, color);
		draw_point_x(x, y, px, py, color);
		py++;
		if ((py * py + px * px) > (r * r))
		{
			px--;
		}
	}
}
