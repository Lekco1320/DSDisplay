#pragma once
// Functions of About page.
// Lukaß Zhang, 2023/12/19

#ifndef _ABOUT_HPP_
#define _ABOUT_HPP_

#include "drawer.hpp"

extern char wait_key();

_NAMESPACE_DSD_BEGIN

inline void about_page() {
	std::system("cls");
	title_display("Data Structure Display - 关于");
	split();
	center_display(R"(_|        _|      _|  _|      _|)");
	center_display(R"(_|        _|_|  _|_|  _|_|  _|_|)");
	center_display(R"(_|        _|  _|  _|  _|  _|  _|)");
	center_display(R"(_|        _|      _|  _|      _|)");
	center_display(R"(_|_|_|_|  _|      _|  _|      _|)");
	split();
	left_display(" 版本：1.0.1.359");
	left_display(" 作者：Lukaß Zhang, Marjoram, Maoner");
	left_display(" 邮箱：Lekco_1320@qq.com");
	left_display(" 仓库：http://www.github.com/Lekco1320/DSDisplay");
	split();
	printf("* 按任意键以返回...\n< ");
	wait_key();
}

_NAMESPACE_DSD_END

#endif // !_ABOUT_HPP_