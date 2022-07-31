#pragma once
/// this file is subject to RENAME (maybe RangeTree)
#include <iostream>
#include <vector>
#include <functional>

constexpr static inline bool isEqual(int a, int b) {
	return a == b;
}
constexpr static inline bool isLessThan(int a, int b) {
	return a < b;
}
constexpr static inline bool isLessThanEqual(int a, int b) {
	return a <= b;
}
extern const int WIN_W;

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
	template <typename RangeTreeItr> 
	class _RT_itr {
	public:
		using val_t = typename RangeTree valueType;
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
		val_t& operator++ () {
			// 
		}
	};
	class TreeNode {
	public:
		int width;
		int xPos;
		int n;
		std::vector < T > nodes;
	public:
		TreeNode(int width, int xPos, std::vector <T> nodes = {}) {
			this->width = width;
			this->xPos = xPos;
			this->n = log10(width);
			if (nodes.empty())
				nodes.reserve(this->n);
			this->nodes = std::move(nodes);
		}
	};
	int width; // global widht size of the window
	TreeNode root;
public:
	void insert(const T& val, int xPos) {
		
	}
	T& find(int xPos) {

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
