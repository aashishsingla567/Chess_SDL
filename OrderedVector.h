#pragma once
/// this file is subject to RENAME (maybe RangeTree)
#include <iostream>
#include <vector>
#include <memory>

/*
*	TODO :: Make a interval based data structure 
*	with following features :- 
*	Tree of list or vectors or something
*	-> It depends on the width of the global interval 
*	-> It makes N nodes equal to width / 10 on each level
*	-> Each node is a reduced interval with width of parent->width / N
*	-> This rule recursively applies to each node.
*/

template <typename T>
class RangeTree {
public:
	using valueType = T;
private:
	int width; // global width
    std::make_shared<TreeNode> root;
private:
	class TreeNode {
	public:
	    valueType val;
		int width;
		int pos;
		int n;
		std::shared_ptr <TreeNode> parent;
		std::vector < std::shared_ptr <TreeNode> > nodes;
	public:
		TreeNode(int width, int pos,  int n = 10) { /// ! make value of n soft coded
			this->width = width;
			this->pos = pos;
			this->n = (pos * n)/ width;
			if (nodes.empty())
				nodes.reserve(this->n);
		}
		valueType getValue () const {
		    return this->val;
		}
		void setValue (const valueType& val) {
		    this->val = val;
		}
		void setValue (valueType&& val) {
		    this->val = std::move (val);
		}
		void setChild (long index, std::shared_ptr <TreeNode> child ) {
		    this->nodes[index] = child;
		    child->parent = std::shared_ptr <TreeNode> (this);
		}
		std::shared_ptr <TreeNode> getChild (long index) {
		    return this->nodes[index];
		}
	};
	template <typename RangeTree>
	class iterator {
	public:
		using val_t = typename RangeTree::valueType;
		using ptr_t = std::shared_ptr < typename RangeTree::TreeNode >;
	private:
		ptr_t m_ptr;
	public:
		val_t& operator* () {
			return *this->m_ptr;
		}
		ptr_t& operator-> () {
			return this->m_ptr;
		}
// 		val_t& operator++ () {
// 			// 
// 		}
	};

private:
	static constexpr inline int getIndex (int pos, int n, int width) {
		return (pos * n) / width;
	}
	static constexpr inline int getPos (int index, int n, int width) {
		return (index * width) / n;
	}
private:
	void insert(const T& val, int pos, std::shared_ptr <TreeNode> root) {
		int index = getIndex (pos, n, width);
		int expectedPos = getPos (index, n, width);
		if ( 
	}
	T& find(int pos, std::shared_ptr <TreeNode> root) {
		
	}
public:
    RangeTree (int width) {
        this->root = std::make_shared <TreeNode> (
            TreeNode (width, 0, 10);
        );
        this->root->parent = nullptr;      
    }
	
};

struct Size {
	int width;
	int height;
};

// put in a different header (EventsSystem)
#include "ECS.hpp"

// put in a different header
class EventsTree {
private:
	RangeTree < std::shared_ptr < RangeTree < std::shared_ptr <Event> > > > m_tree;
	Size m_windowSize;
public:
	void addEvent() {
		
	};
	void removeEvent() {

	};
};
