#pragma once
// Definations of drawer classes and helper functions for format output
// and drawing.
// Lukaß Zhang, 2023/12/19

#ifndef _DRAWER_HPP_
#define _DRAWER_HPP_

#include "DSDisplay.h"
#include <string>
#include <cmath>
#include <iostream>
#include <graphics.h>

_NAMESPACE_DSD_BEGIN

const double START_ANGLE = PI / 3;
constexpr unsigned int BOXS_Y = 550;
constexpr unsigned int DISPLAY_W = 800;
constexpr unsigned int DISPLAY_H = 620;
constexpr unsigned int DELTA = 10;
constexpr unsigned int RADIUS = 17;
constexpr unsigned int BOX_L = 25;
constexpr unsigned int HEIGHT = 50 + RADIUS * 2;
constexpr unsigned int START_X = 400;
constexpr unsigned int START_Y = 80;
constexpr unsigned int SPLITER = 52;

using point = ege::ege_point;
using rectangle = ege::ege_rect;
using color = ege::color_t;

enum COLORS {
	RED   = EGERGB(0xff, 0x00, 0x00),
	BLACK = EGERGB(0x00, 0x00, 0x00),
	GRAY  = EGERGB(0x50, 0x50, 0x50)
};

inline void split() {
	for (int i = 0; i < SPLITER; i++) {
		putchar('*');
	}
	putchar('\n');
}

inline void left_display(const char* _Str) {
	putchar('*');
	std::cout << _Str;
	size_t append = SPLITER - 2 - strlen(_Str);
	for (int i = 0; i < append; i++) {
		putchar(' ');
	}
	putchar('*');
	putchar('\n');
}

inline void center_display(const char* _Str) {
	size_t minus = SPLITER - 2 - strlen(_Str);
	size_t left = minus / 2;
	size_t right = minus / 2 + minus % 2;
	putchar('*');
	for (int i = 0; i < left; i++) {
		putchar(' ');
	}
	std::cout << _Str;
	for (int i = 0; i < right; i++) {
		putchar(' ');
	}
	putchar('*');
	putchar('\n');
}

inline void title_display(const char* _Str) {
	split();
	center_display(_Str);
}

inline void option(char _Key, const char* _Ps) {
	char ps[64]{ '\0' };
	sprintf_s(ps, 64, " %c | %s", _Key, _Ps);
	left_display(ps);
}

inline void output(const char* _Str) {
	printf("> %s\n", _Str);
}

inline void input(const char* _Str) {
	printf("< %s", _Str);
}

inline void ege_title(const char* _Str) {
	ege::setcolor(BLACK);
	ege::setfont(-24, 0, "黑体");
	ege::outtextxy((DISPLAY_W - ege::textwidth(_Str)) / 2, 20, _Str);
	ege::setfont(-18, 0, "Consolas");
	ege::delay_ms(0);
}

inline float center_position(int _Offset, int _All_Px_Len, int _Text_Px_Len) {
	return _Offset + (_All_Px_Len - _Text_Px_Len) / 2.0;
}

inline void clear() {
	std::system("cls");
	ege::cleardevice();
}

class draw_element {
public:
	virtual void draw(color _Color) const = 0;

	virtual void wait(long _Ms = 500) const = 0;

	void emphasize() const {
		draw(RED);
		wait();
		draw(BLACK);
		wait();
	}
};

class box
	: public draw_element {
public:
	rectangle rect;
	std::string tip;

	box()
		: rect{ 0, 0, BOX_L, BOX_L } {
	}

	box(const std::string& _Tip, point _Pos)
		: rect { _Pos.x, _Pos.y, BOX_L, BOX_L }
		, tip(_Tip) {
	}

	void draw(color _Color = BLACK) const {
		ege::setcolor(_Color);
		ege::setfillcolor(WHITE);
		ege::ege_fillrect(rect.x, rect.y, rect.w, rect.h);
		ege::outtextxy(center_position(rect.x, rect.w, ege::textwidth(tip.c_str())),
					   center_position(rect.y, rect.h, ege::textheight(tip.c_str())), tip.c_str());
		ege::rectangle(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
		ege::delay_ms(0);
	}

	virtual void wait(long _Ms = 750) const {
		ege::delay(_Ms);
	}
};

struct node_position {
	point left;
	point right;
	point pos;
	double angle;

	node_position()
		: left{ START_X - tanf(START_ANGLE) * HEIGHT, START_Y + HEIGHT }
		, right{ START_X + tanf(START_ANGLE) * HEIGHT, START_Y + HEIGHT }
		, pos{ START_X, START_Y }
		, angle(START_ANGLE) {
	}

	node_position(point _Point, double _Angle)
		: left{ _Point.x - tanf(_Angle) * HEIGHT, _Point.y + HEIGHT }
		, right{ _Point.x + tanf(_Angle) * HEIGHT, _Point.y + HEIGHT }
		, pos(_Point)
		, angle(_Angle) {
		if (left.x > right.x) {
			std::swap(left, right);
		}
	}

	node_position left_child() const {
		double ang = max(-0.284976, atan(tan(angle) - 2.1 * ((double)DELTA + RADIUS) / HEIGHT));
		return { left, ang };
	}

	node_position right_child() const {
		double ang = max(-0.284976, atan(tan(angle) - 2.1 * ((double)DELTA + RADIUS) / HEIGHT));
		return { right, ang };
	}
};

class circle
	: public draw_element {
public:
	point position;
	std::string tip;
	std::string ps;

	circle(const char& _Tip, const node_position& _Pos, const std::string& _Ps = "")
		: position(_Pos.pos)
		, tip(std::string(1, _Tip))
		, ps(_Ps) {
	}

	circle(const std::string& _Tip, const node_position& _Pos, const std::string& _Ps = "")
		: position(_Pos.pos)
		, tip(_Tip)
		, ps(_Ps) {
	}

	void draw(color _Color = BLACK) const {
		ege::setcolor(_Color);
		ege::setbkmode(TRANSPARENT);
		ege::outtextxy(center_position(position.x - RADIUS, 2 * RADIUS, ege::textwidth(ps.c_str())),
			           position.y + RADIUS, ps.c_str());
		ege::setcolor(_Color);
		ege::circle(position.x, position.y, RADIUS);
		ege::setbkmode(TRANSPARENT);
		ege::outtextxy(center_position(position.x - RADIUS, 2 * RADIUS, ege::textwidth(tip.c_str())),
				       center_position(position.y - RADIUS, 2 * RADIUS, ege::textheight(tip.c_str())), tip.c_str());
		ege::delay_ms(0);
	}

	virtual void wait(long _Ms = 750) const {
		ege::delay(_Ms);
	}
};

class line
	: public draw_element {
public:
	point p1;
	point p2;
	std::string ps;
	bool left;

	line(const node_position& _P1, const node_position& _P2, const std::string& _Ps = "", bool _Left = true)
		: p1(_P1.pos)
		, p2(_P2.pos)
		, ps(_Ps)
		, left(_Left) {
		if (p1.x > p2.x) {
			std::swap(p1, p2);
		}
	}

	void draw(color _Color = BLACK) const {
		point direct{ cos(atan((p2.y - p1.y) / (p2.x - p1.x))), sin(atan((p2.y - p1.y) / (p2.x - p1.x))) };
		point start{ p1.x + direct.x * RADIUS, p1.y + direct.y * RADIUS };
		point end{ p2.x - direct.x * RADIUS, p2.y - direct.y * RADIUS };
		point pspos{ (p1.x + p2.x) / 2 + (left ? -1.2 : 0.6) * ege::textwidth(ps.c_str()), (p1.y + p2.y - ege::textheight(ps.c_str())) / 2 };
		ege::setcolor(GRAY);
		ege::outtextxy(pspos.x, pspos.y, ps.c_str());
		ege::setcolor(_Color);
		ege::line(start.x, start.y, end.x, end.y);
		ege::delay_ms(0);
	}

	virtual void wait(long _Ms = 300) const {
		ege::delay(_Ms);
	}
};

class string
	: public draw_element {
public:
	point position;
	std::string data;
	std::string font;

	string()
		: position{0, 0} {
	}

	string(point _Pos, const std::string& _Data, const std::string& _Font)
		: position(_Pos)
		, data(_Data)
		, font(_Font) {
	}

	void draw(color _Color = BLACK) const {
		if (font.size()) {
			ege::setfont(-18, 0, font.c_str());
		}
		ege::setcolor(_Color);
		ege::outtextxy(position.x, position.y, data.c_str());
		ege::delay_ms(0);
	}

	virtual void wait(long _Ms = 500) const {
		ege::delay(_Ms);
	}
};

_NAMESPACE_DSD_END

#endif // !_DRAWER_HPP_