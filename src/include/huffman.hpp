#pragma once
// Functions and definations of Huffman Tree's constructer and
// visualizer.
// Maoner, Lukaß Zhang. 2023/12/19

#ifndef _HUFFMAN_HPP_
#define _HUFFMAN_HPP_

#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include "binary_tree.hpp"

extern char wait_key();

_NAMESPACE_DSD_BEGIN

struct huffman_node {
	int weight = 0;
	int parent = -1;
	int lchild = -1;
	int rchild = -1;
	int level  = 0;
	int order  = 0x3f3f3f3f;
	std::string data;
	std::string code;
	dsd::node_position pos;
	dsd::box data_box;
	dsd::box weight_box;
};

using huffman_tree = binary_array<huffman_node>;

void huffman_build(huffman_tree& T) {
	//找两个最小的数，开始构建哈夫曼树
	int n = T.leafnumber, s = 0, t = n, order = 0;
	for (int i = 0; i < n - 1; i++) {
		int k1 = 0;
		if (s < n && (t >= n + i || T.data[s].weight < T.data[t].weight)) {
			k1 = s++;
		}
		else {
			k1 = t++;
		}
		int k2 = 0;
		if (s < n && (t >= n + i || T.data[s].weight < T.data[t].weight)) {
			k2 = s++;
		}
		else {
			k2 = t++;
		}
		T.data[k1].parent = i + n;
		T.data[k1].order = min(T.data[k1].order, order++);
		T.data[k2].parent = i + n;
		T.data[k2].order = min(T.data[k2].order, order++);
		T.data[i + n].weight = T.data[k1].weight + T.data[k2].weight;
		T.data[i + n].lchild = k1;
		T.data[i + n].rchild = k2;
		T.data[i + n].order = min(T.data[i +  n].order, order++);
	}
}

void huffman_encode(huffman_tree& _Tree) {
	std::queue<huffman_node> q;
	huffman_node p = _Tree.data[2 * _Tree.leafnumber - 2];
	q.push(p);
	while (!q.empty()) {
		huffman_node node = q.front();
		q.pop();
		if (node.lchild != -1) {
			_Tree.data[node.lchild].code = node.code + "0";
			q.push(_Tree.data[node.lchild]);

		}
		if (node.rchild != -1) {
			_Tree.data[node.rchild].code = node.code + "1";
			q.push(_Tree.data[node.rchild]);
		}
	}
}

void huffman_level(huffman_tree& _Tree) {
	auto& root = _Tree.data[2 * _Tree.leafnumber - 2];
	root.level = 1;
	root.pos = dsd::node_position{};
	std::queue<huffman_node> q;
	q.push(root);
	while (!q.empty()) {
		huffman_node p = q.front(); 
		q.pop();
		if (p.lchild != -1) {
			_Tree.data[p.lchild].level = p.level + 1;
			_Tree.data[p.lchild].pos = p.pos.left_child();
			q.push(_Tree.data[p.lchild]);
		}
		if (p.rchild != -1) {
			_Tree.data[p.rchild].level = p.level + 1;
			_Tree.data[p.rchild].pos = p.pos.right_child();
			q.push(_Tree.data[p.rchild]);
		}
	}
}

void huffman_initialize(huffman_tree& _Tree) {
	title_display("请输入数据量");
	split();
	input("n = ");
	int n;
	std::cin >> n;
	_Tree.data = new huffman_node[2 * n - 1];
	_Tree.leafnumber = n;
	_Tree.text_width = ege::textwidth("      ");
	_Tree.start_x = center_position(0, DISPLAY_W, _Tree.text_width + 5 + BOX_L * 2 * n - 1);

	string({ _Tree.start_x, BOXS_Y }, "  data", "Consolas").draw();
	string({ _Tree.start_x, BOXS_Y + BOX_L }, "weight", "Consolas").draw();
	for (int i = 0; i < 2 * n - 1; i++) {
		_Tree.data[i].data_box.rect.x = _Tree.text_width + 5 + _Tree.start_x + BOX_L * i;
		_Tree.data[i].data_box.rect.y = BOXS_Y;
		_Tree.data[i].data_box.draw();
		_Tree.data[i].weight_box.rect.x = _Tree.text_width + 5 + _Tree.start_x + BOX_L * i;
		_Tree.data[i].weight_box.rect.y = BOXS_Y + BOX_L;
		_Tree.data[i].weight_box.draw();
	}

	title_display("请以\"数据 权重\"的格式输入数据");
	split();
	for (int i = 0; i < n; i++) {
		putchar('<');
		putchar(' ');
		std::string data;
		int weight;
		std::cin >> data >> weight;
		_Tree.data[i].data = data;
		_Tree.data[i].weight = weight;
		_Tree.data[i].data_box.tip = data;
		_Tree.data[i].weight_box.tip = std::to_string(weight);
		_Tree.data[i].data_box.draw();
		_Tree.data[i].weight_box.draw();
	}
	std::sort(_Tree.data, _Tree.data + n, [&](const huffman_node& _Node1, const huffman_node& _Node2) -> bool {
		return _Node1.weight < _Node2.weight;
	});
}

void huffman_display(huffman_tree& _Tree) {
	dsd::title_display("构造过程");
	dsd::split();
	printf("*     数据        权重        层次        编码     *\n");

	for (int i = 0; i < _Tree.leafnumber * 2 - 1; i++) {
		_Tree.data[i].data_box.rect.x = _Tree.start_x + _Tree.text_width + 5 + dsd::BOX_L * i;
		_Tree.data[i].weight_box.rect.x = _Tree.start_x + _Tree.text_width + 5 + dsd::BOX_L * i;
		_Tree.data[i].data_box.draw();
		_Tree.data[i].weight_box.draw();
	}

	int* temp = new int[_Tree.leafnumber * 2 - 1];
	for (int i = 0; i < _Tree.leafnumber * 2 - 1; i++) {
		temp[i] = i;
	}
	std::sort(temp, temp + _Tree.leafnumber * 2 - 1, [&](const int& _N1, const int& _N2) -> bool {
		return _Tree.data[_N1].order < _Tree.data[_N2].order;
	});
	for (int i = 0; i < _Tree.leafnumber * 2 - 1; i++) {
		dsd::circle pos(_Tree.data[temp[i]].data, _Tree.data[temp[i]].pos, std::to_string(_Tree.data[temp[i]].weight));
		printf("*      %-12s%-12d%-11d%-5s    *\n", _Tree.data[temp[i]].data.c_str(), _Tree.data[temp[i]].weight, _Tree.data[i].level, _Tree.data[temp[i]].code.c_str());
		_Tree.data[temp[i]].data_box.tip = _Tree.data[temp[i]].data;
		_Tree.data[temp[i]].weight_box.tip = std::to_string(_Tree.data[temp[i]].weight);

		if (_Tree.data[temp[i]].lchild != -1) {
			line(_Tree.data[temp[i]].pos, _Tree.data[_Tree.data[temp[i]].lchild].pos, "0", true).emphasize();
		}
		if (_Tree.data[temp[i]].rchild != -1) {
			line(_Tree.data[temp[i]].pos, _Tree.data[_Tree.data[temp[i]].rchild].pos, "1", false).emphasize();
		}

		pos.draw(RED);
		_Tree.data[temp[i]].data_box.draw(RED);
		_Tree.data[temp[i]].weight_box.draw(RED);
		pos.wait();
		pos.draw(BLACK);
		_Tree.data[temp[i]].data_box.draw(GRAY);
		_Tree.data[temp[i]].weight_box.draw(GRAY);
		pos.wait();
	}
	delete[] temp;
}

void huffman_page() {
	ege::initgraph(DISPLAY_W, DISPLAY_H);
	clear();
	ege::setbkcolor(WHITE);
	title_display("Data Structure Display - 构造哈夫曼树");
	ege_title("构造哈夫曼树");

	huffman_tree tree;
	huffman_initialize(tree);
	huffman_build(tree);
	huffman_level(tree);
	huffman_encode(tree);
	huffman_display(tree);
	ba_destory(tree);
	
	split();
	printf("* 按任意键以返回...\n< ");
	wait_key();
	ege::closegraph();
}

_NAMESPACE_DSD_END

#endif // !_HUFFMAN_HPP