/**********************************************************************
* Functions and definations of binary tree.
* 
* Yuhao Zhang. 12/19/2023
**********************************************************************/
#pragma once
#ifndef _BINARY_TREE_HPP_
#define _BINARY_TREE_HPP_

#include "DSDisplay.h"
#include "drawer.hpp"

_NAMESPACE_DSD_BEGIN

template <typename _Ty>
struct bt_node {
	_Ty data;
	int level;
	node_position pos;
	bt_node* lchild;
	bt_node* rchild;
};

template <typename _Ty>
using binary_tree = bt_node<_Ty>*;

template <typename _Ty>
inline void bt_destroy(binary_tree<_Ty>& _Tree) {
	if (_Tree == nullptr) {
		return;
	}
	bt_destroy(_Tree->lchild);
	bt_destroy(_Tree->rchild);
	delete _Tree;
	_Tree = nullptr;
}

template <typename _Ty>
struct binary_array {
	_Ty*  data       = nullptr;
	int   leafnumber = 0;
	float start_x    = 0;
	int   text_width = 0;
};

template <typename _Ty>
inline void ba_destory(binary_array<_Ty>& _Array) {
	_Array.leafnumber = 0;
	_Array.start_x    = 0;
	_Array.text_width = 0;
	delete[] _Array.data;
	_Array.data       = nullptr;
}

_NAMESPACE_DSD_END

#endif // !_BINARY_TREE_HPP_