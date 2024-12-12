#pragma once
// Functions and definations of Binary Tree Builder by pre-order and in-
// order string and its visualizer.
// Marjoram, Lukaß Zhang, 2023/12/19

#ifndef _BT_BUILDER_HPP_
#define _BT_BUILDER_HPP_

#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include "drawer.hpp"
#include "binary_tree.hpp"

extern char wait_key();

_NAMESPACE_DSD_BEGIN

constexpr unsigned int TEXTS_Y = 550;

using bt = binary_tree<char>;

struct built_char {
	char c = '\0';
	string s;
};

inline bt bt_build(const built_char* _Pre_Str, const built_char* _In_Str, int _Len, int _Level, const node_position& _Pos, const node_position* _Parent) {
	if (_Len <= 0) {
		return nullptr;
	}
	bt tree = new bt_node<char>{ _Pre_Str->c, _Level, _Pos };
	printf("*      %10c%18d                *\n", tree->data, tree->level);
	dsd::circle circle(tree->data, tree->pos);

	int rootpos = -1;
	for (int i = 0; i < _Len; i++) {
		if (_In_Str[i].c == _Pre_Str->c) {
			rootpos = i;
			break;
		}
	}

	if (_Parent != nullptr) {
		dsd::line(tree->pos, *_Parent).emphasize();
	}
	circle.draw(RED);
	_Pre_Str->s.draw(RED);
	_In_Str[rootpos].s.draw(RED);
	circle.wait();
	circle.draw(BLACK);
	_Pre_Str->s.draw(GRAY);
	_In_Str[rootpos].s.draw(GRAY);
	circle.wait();

	int leftcount = rootpos;
	tree->lchild = bt_build(_Pre_Str + 1, _In_Str, leftcount, _Level + 1, _Pos.left_child(), &_Pos);
	tree->rchild = bt_build(_Pre_Str + 1 + leftcount, _In_Str + leftcount + 1, _Len - 1 - leftcount, _Level + 1, _Pos.right_child(), &_Pos);
	return tree;
}

inline void bt_build_failure() {
	split();
	output("前序与中序遍历字符串非法或不匹配。");
	printf("* 按任意键重开...\n< ");
	wait_key();
	ege::closegraph();
}

inline void bt_build_page() {
	ege::initgraph(DISPLAY_W, DISPLAY_H);
	ege::setbkcolor(WHITE);
	clear();
	title_display("Data Structure Display - 前序＆中序构造二叉树");
	ege_title("前序＆中序构造二叉树");
	char pre_s[128]{ 0 }, in_s[128]{ 0 };
	title_display("请输入字符串");
	split();
	input("前序遍历字符串 = ");
	std::cin >> pre_s;
	input("中序遍历字符串 = ");
	std::cin >> in_s;

	size_t pre_len = std::strlen(pre_s);
	size_t in_len = std::strlen(in_s);
	std::map<char, int> pre_map, in_map;
	for (int i = 0; i < pre_len; i++) {
		++pre_map[pre_s[i]];
	}
	for (int i = 0; i < in_len; i++) {
		++in_map[in_s[i]];
	}
	if (!(pre_len && in_len) || pre_map != in_map) {
		bt_build_failure();
		bt_build_page();
		return;
	}

	int ps_width = ege::textwidth("前序：");
	float char_width = ege::textwidth(' ');
	float char_height = ege::textheight(' ');
	float start_x = center_position(0, DISPLAY_W, ps_width + char_width * pre_len);
	string({ start_x, TEXTS_Y }, "前序：", "等线").draw();
	string({ start_x, TEXTS_Y + char_height }, "中序：", "等线").draw();
	built_char* pre_ss = new built_char[pre_len];
	built_char* in_ss = new built_char[in_len];
	for (int i = 0; i < pre_len; i++) {
		pre_ss[i] = { pre_s[i], { { start_x + ps_width + char_width * i, TEXTS_Y }, std::string(1, pre_s[i]), "Consolas"}};
		in_ss[i] = { in_s[i], { { start_x + ps_width + char_width * i, TEXTS_Y + char_height }, std::string(1, in_s[i]), "Consolas"}};
		pre_ss[i].s.draw();
		in_ss[i].s.draw();
	}

	bt tree = nullptr;
	dsd::title_display("构造过程");
	dsd::split();
	printf("*              字符              层次              *\n");
	tree = bt_build(pre_ss, in_ss, pre_len, 1, node_position{}, nullptr);
	split();
	
	printf("* 按任意键以返回...\n< ");
	wait_key();
	ege::closegraph();
	bt_destroy(tree);
	delete[] pre_ss;
	delete[] in_ss;
}

_NAMESPACE_DSD_END

#endif // !_BT_BUILDER_HPP_