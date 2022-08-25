#pragma once
/// this file is subject to RENAME (maybe RangeTree)
#include <iostream>
#include <vector>

/*
*	TODO :: Make a interval based data structure 
*	with following features :- 
*	Tree of list or vectors or something
*	-> It depends on the width of the global interval 
*	-> It makes N nodes equal to width / 10 on each level
*	-> Each node is a reduced interval with width of parent->width / N
*	-> This rule recursively applies to each node.
*/

template <typename myRangeTree>
class RangeTreeIterator {
public:
	using val_t = typename myRangeTree::valueType;
	using ptr_t = std::shared_ptr < val_t >;
	using iterator = RangeTreeIterator < myRangeTree >;
	using node_ptr = std::shared_ptr < typename myRangeTree::TreeNode >;
private:
	node_ptr m_node;
	ptr_t m_ptr;
public:
	// construct iterator from tree node
	RangeTreeIterator(node_ptr node) {
		m_node = node;
		m_ptr = std::make_shared <val_t> (node->val);
	};
public:
	val_t& operator* () {
		return *this->m_ptr;
	}
	ptr_t& operator-> () {
		return this->m_ptr;
	}
	bool operator == (const iterator& other) {
		return this->m_node == other.m_node;
	}
};

template <typename T>
class RangeTree {
public:
	using valueType = T;
	using iterator = RangeTreeIterator <RangeTree <T> >;
public:
	class TreeNode {
	public:
		int width;
		int pos;
		int n;
		std::vector < std::shared_ptr <TreeNode> > nodes;
		T val;
	public:
		TreeNode (int width, int pos, std::vector <std::shared_ptr <TreeNode> > nodes = {}) {
			this->width = width;
			this->pos = pos;
			/// TODO :: take the ceil of the log 
			this->n = std::ceil ( log10(width) );
			if (nodes.empty())
				nodes.reserve(this->n);
			for (int i = pos; i < width + pos; i += width / n) {
				nodes.push_back( std::make_shared <TreeNode> (
						TreeNode(width / n, i)
					)
				);
			}
			this->nodes = std::move(nodes);
		}
		TreeNode (int width, int pos, const T& val, std::vector <std::shared_ptr <TreeNode> > nodes = {}) {
			this->width = width;
			this->pos = pos;
			/// TODO :: take the ceil of the log 
			this->n = std::ceil ( log10(width) );
			if (nodes.empty())
				nodes.reserve(this->n);
			for (int i = pos; i < width + pos; i += width / n) {
				nodes.push_back( std::make_shared <TreeNode> (
						TreeNode(width / n, i, val)
					)
				);
			}
			this->nodes = std::move(nodes);
			this->val = val;
		}
		TreeNode (int width, int pos, T&& val, std::vector <std::shared_ptr <TreeNode> > nodes = {}) {
			this->width = width;
			this->pos = pos;
			/// TODO :: take the ceil of the log 
			this->n = std::ceil(log10(width));
			if (nodes.empty())
				nodes.reserve(this->n);
			for (int i = pos; i < width + pos; i += width / n) {
				nodes.push_back( std::make_shared <TreeNode> (TreeNode(width / n, i)) );
			}
			this->nodes = std::move(nodes);
			this->val = std::move (val);
		}
	public:
		// TODO :: make a fucntion to remove the node from the tree
		void remove() {
			for (auto& node : this->nodes) {
				node->remove();
			}
			this->~TreeNode();
		}
		// TreeNode deconstructor
		~TreeNode() {
			remove();
		}

		
		//// TODO :: make a function to find the node in the tree

		//TreeNode findNode(int x) {
		//	if (x < this->pos || x >= this->pos + this->width)
		//		return TreeNode(0, 0);
		//	for (auto& node : this->nodes) {
		//		if (node.pos <= x && x < node.pos + node.width)
		//			return node.findNode(x);
		//	}
		//	return TreeNode(0, 0);
		//}
	};
private:
	
	int width; // global widht size of the window
	std::shared_ptr <TreeNode> root;
	
public: // constructors
	RangeTree() = default;
	RangeTree(int width) {
		this->width = width;
		this->root = std::make_shared <TreeNode>(TreeNode (width, 0));
	}
	RangeTree(int width, const T& val) {
		this->width = width;
		this->root = std::make_shared <TreeNode>(TreeNode(width, 0, val));
	}
	RangeTree(int width, T&& val) {
		this->width = width;
		this->root = std::make_shared <TreeNode>(  
			TreeNode( width, 0, std::move (val) )
		);
	}
public: // assignemt operators
	// move assignment
	RangeTree <T> & operator= (RangeTree<T>&& other) {
		this->width = other.width;
		this->root = std::move(other.root);
		return *this;
	}
	// copy assignment
	RangeTree<T>& operator= (const RangeTree<T>& other) {
		this->width = other.width;
		this->root = other.root;
		return *this;
	}

private: // Private Methods
	iterator insert(const T& val, int pos, std::shared_ptr <TreeNode> root) {
		auto index = pos * root->n / root->width;
		if (root->nodes.empty()) {
			root->nodes.reserve(root->n);
			for (int i = pos; i < width + pos; i += width / root->n) {
				root->nodes.push_back( std::make_shared <TreeNode> (
						TreeNode(width / root->n, i)
					)
				);
			}
		}
		if (root->nodes[index]->pos == pos) {
			root->nodes[index]->val = val;
			return iterator(root->nodes[index]);
		}
		else {
			insert(val, pos, root->nodes[index]);
		}
	}
	// find recursive
	iterator find(int pos, std::shared_ptr <TreeNode> root) {
		auto index = pos * root->n / root->width;
		if (root->nodes.empty()) {
			return iterator(nullptr);
		}
		if (root->nodes[index]->pos == pos) {
			return iterator (root);
		}
		else {
			return find(pos, root->nodes[index]);
		}
	}
	// remove func recursive
	void remove(int pos, std::shared_ptr <TreeNode> root) {
		auto index = pos * root->n / root->width;
		if (root->nodes.empty())
			return;
		if (root->nodes[index]->pos == pos) {
			root->nodes[index]->remove();
		}
		else {
			remove(pos, root->nodes[index]);
		}
	}

public: // Public Methods
	// iterator begin
	iterator begin() {
		return iterator(this->root);
	}
	// iterator end
	iterator end() {
		return iterator(nullptr);
	}
	// insert
	iterator insert(const T& val, int pos) {
		return insert(val, pos, this->root);
	}
	// find
	iterator find(int pos) {
		return find(pos, this->root);
	}
	// remove
	void remove(int pos) {
		remove(pos, this->root);
	}
};
