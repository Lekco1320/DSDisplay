// Functions of Main page.
// Lukaß Zhang, 2023/12/19

#include "drawer.hpp"
#include "huffman.hpp"
#include "bt_builder.hpp"
#include "about.hpp"
#include "search_tree.hpp"

extern char wait_key();

bool attribute() {
	dsd::clear();
	dsd::title_display("Data Structure Display - Group 2");
	dsd::title_display("目录");
	dsd::split();
	dsd::option('H', "构造哈夫曼树");
	dsd::option('B', "前序＆中序构造二叉树");
	dsd::option('S', "二叉排序树的构造与查询");
	dsd::option('A', "关于");
	dsd::option('Q', "退出");
	dsd::split();
	printf("* 按下键盘以选择功能...\n< ");
	switch (wait_key()) {
	case 'H':
		dsd::huffman_page();
		break;
	case 'B':
		dsd::bt_build_page();
		break;
	case 'S':
		dsd::search_tree_page();
		break;
	case 'A':
		dsd::about_page();
		break;
	case 'Q':
		printf("Q | 退出\n");
		return false;
	default:
		break;
	};
	return true;
}

int main() {
	ege::setfont(-18, 0, "Consolas");
	while (attribute());
	dsd::output("感谢您的使用！");
	ege::closegraph();
}