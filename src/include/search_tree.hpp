#pragma once
// Functions and definations of Search Binary Tree's constructer and
// visualizer.
// Lukaß Zhang, 2023/12/19

#ifndef _SEARCH_TREE_
#define _SEARCH_TREE_

#include "drawer.hpp"
#include "binary_tree.hpp"

extern char wait_key();

_NAMESPACE_DSD_BEGIN

using st = binary_tree<int>;

inline st search_tree_search(st& _Tree, int _Key, const node_position& _Pos, const node_position* _Parent) {
	if (_Tree == nullptr) {
		printf("*           %-14c%-14c%-9s   *\n", '-', '-', "×");
		return nullptr;
	}
	if (_Tree->data > _Key) {
		auto next = _Pos.left_child();
		circle c(std::to_string(_Tree->data), _Tree->pos);
		c.draw(RED);
		c.wait(400);
		c.draw(BLACK);

		if (_Tree->lchild != nullptr) {
			line l(_Tree->pos, next);
			l.draw(RED);
			l.wait(400);
			l.draw(BLACK);
		}
		printf("*           %-14d%-14d%-9s   *\n", _Tree->data, _Tree->level, "↙");
		return search_tree_search(_Tree->lchild, _Key, next, &_Tree->pos);
	}
	if (_Tree->data < _Key) {
		auto next = _Pos.right_child();
		circle c(std::to_string(_Tree->data), _Tree->pos);
		c.draw(RED);
		c.wait(400);
		c.draw(BLACK);

		if (_Tree->rchild != nullptr) {
			line l(_Tree->pos, next);
			l.draw(RED);
			l.wait(400);
			l.draw(BLACK);
		}
		printf("*           %-14d%-14d%-9s   *\n", _Tree->data, _Tree->level, "↘");
		return search_tree_search(_Tree->rchild, _Key, next, &_Tree->pos);
	}
	else {
		circle c(std::to_string(_Tree->data), _Tree->pos);
		c.draw(RED);
		c.wait(400);
		c.draw(BLACK);
		printf("*           %-14d%-14d%-8s   *\n", _Tree->data, _Tree->level, "〇");
		return _Tree;
	}
}

inline bool search_tree_search(st& _Tree) {
	printf("* 按S查询结点，按Q返回主菜单...\n< ");
	char c;
	do {
		c = wait_key();
	} while (c != 'Q' && c != 'S');
	if (c == 'Q') {
		return false;
	}
	printf("查询值 = ");
	int n;
	std::cin >> n;
	std::string s = "查询过程：key = " + std::to_string(n);
	title_display(s.c_str());
	split();
	printf("*          数据          层次          结果        *\n");
	search_tree_search(_Tree, n, node_position{}, nullptr);
	split();
	return true;
}

inline st search_tree_insert(st& _Tree, int _Key, int _Level, const node_position& _Pos, const node_position* _Parent) {
	if (_Tree == nullptr) {
		_Tree = new bt_node<int>{ _Key, _Level, _Pos };
		if (_Parent != nullptr) {
			line(_Pos, *_Parent).emphasize();
		}
		printf("*      %10d%18d                *\n", _Tree->data, _Tree->level);
		circle(std::to_string(_Tree->data), _Tree->pos).emphasize();
	}
	else if (_Tree->data >= _Key) {
		auto next = _Pos.left_child();
		circle c(std::to_string(_Tree->data), _Tree->pos);
		c.draw(RED);
		c.wait(300);
		c.draw(BLACK);

		if (_Tree->lchild != nullptr) {
			line l(_Tree->pos, next);
			l.draw(RED);
			l.wait(300);
			l.draw(BLACK);
		}
		search_tree_insert(_Tree->lchild, _Key, _Level + 1, next, &_Tree->pos);
	}
	else {
		auto next = _Pos.right_child();
		circle c(std::to_string(_Tree->data), _Tree->pos);
		c.draw(RED);
		c.wait(300);
		c.draw(BLACK);

		if (_Tree->rchild != nullptr) {
			line l(_Tree->pos, next);
			l.draw(RED);
			l.wait(300);
			l.draw(BLACK);
		}
		search_tree_insert(_Tree->rchild, _Key, _Level + 1, next, &_Tree->pos);
	}
	return _Tree;
}

inline void search_tree_build(st& _Tree) {
	title_display("请输入数据量");
	split();
	input("n = ");
	int n;
	std::cin >> n;

	float text_width = ege::textwidth("data");
	float start_x = center_position(0, DISPLAY_W, text_width + 5 + BOX_L * n);
	string({ start_x, BOXS_Y }, "data", "Consolas").draw();
	box* boxs = new box[n];
	int* data = new int[n];
	for (int i = 0; i < n; i++) {
		boxs[i].rect.x = start_x + text_width + 5 + BOX_L * i;
		boxs[i].rect.y = BOXS_Y;
		boxs[i].draw();
	}

	title_display("请输入数据");
	split();
	for (int i = 0; i < n; i++) {
		putchar('<');
		putchar(' ');
		std::cin >> data[i];
		boxs[i].tip = std::to_string(data[i]);
		boxs[i].draw();
	}

	title_display("构造过程");
	split();
	printf("*              数据              层次              *\n");
	for (int i = 0; i < n; i++) {
		boxs[i].draw(RED);
		_Tree = search_tree_insert(_Tree, data[i], 1, node_position{}, nullptr);
		boxs[i].draw(GRAY);
	}

	split();
	delete[] boxs;
	delete[] data;
}

inline void search_tree_page() {
	ege::initgraph(DISPLAY_W, DISPLAY_H);
	ege::setbkcolor(WHITE);
	clear();
	title_display("Data Structure Display - 二叉排序树的构造与查询");
	ege_title("二叉排序树的构造与查询");

	st tree = nullptr;
	search_tree_build(tree);
	while (search_tree_search(tree));
	
	ege::closegraph();
	bt_destroy(tree);
}

_NAMESPACE_DSD_END

#endif // !_SEARCH_TREE_