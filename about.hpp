/**********************************************************************
* Functions of About page.
* 
* Yuhao Zhang. 12/19/2023
**********************************************************************/

#pragma once
#ifndef _ABOUT_HPP_
#define _ABOUT_HPP_

#include "drawer.hpp"

extern char wait_key();

_NAMESPACE_DSD_BEGIN

inline void about_page() {
	std::system("cls");
	title_display("Data Structure Display - 关于");
	split();
	center_display(R"(   )HHGy8QQ26H>    yKv            sKQ3>    HA2))");
	center_display(R"(   {'_v'v1vQQ8"   vQg             HG6Q!   QQQQA)");
	center_display(R"(         "yQ)     2Q1            rHQ'g8  HQrQQ')");
	center_display(R"(        wGK"     ,%Qw            rQH d% GQ AQd )");
	center_display(R"(      >6Q1       {8%             2Qs 3QGQ' KHs )");
	center_display(R"(     K8%r        38m            ~QG' >6y_ 'QG" )");
	center_display(R"(   u8Qm         `g8!            yQ2       {%f  )");
	center_display(R"( ')Qu           sQd             H8"       6G>  )");
	center_display(R"(AQQH{_vr'>''    HQG1!v!{"!!1>  >QG_      "QQ`  )");
	center_display(R"(rH2g%HG%dKyG   `%HH)yQQyyHG),  fQd       >Hv   )");
	split();
	left_display(" 版本：1.0.0.0");
	left_display(" 作者：张宇浩，刘梽灿，毛安锋");
	left_display(" 邮箱：Lekco_1320@qq.com");
	left_display(" 仓库：http://www.github.com/Lekco1320/DSDisplay");
	split();
	printf("* 按任意键以返回...\n< ");
	wait_key();
}

_NAMESPACE_DSD_END

#endif // !_ABOUT_HPP_