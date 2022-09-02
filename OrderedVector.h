#pragma once
/// this file is subject to RENAME (maybe RangeTree)
#include <iostream>
#include <vector>
#include <memory>


// TODO :: eleminate uneccessary DS
template <typename T>
class OrderedVector : public std::vector <T> {
public:
    // copy construtor
    OrderedVector (const std::vector <T>& vec) : std::vector <T> (vec) {
        std::sort (this->begin(), this->end());
    }
    
    // move constructor
    OrderedVector (std::vector <T>&& vec) : std::vector <T> (std::move (vec)) {
        std::sort (this->begin(), this->end());
    }
    
    void sort () {
        std::sort (this->begin(), this->end());
    }
    
    override void push_back ( const T& val ) {
        this->push_back (val);
        this->sort ();
    }
    
    // TODO :: refactor with hash_set
    template <typename F1, F2>
    std::vector <T> getIntersections (
        const OrederedVector <T>& other,
        const F1&& equality,
        const F2&& inEquality
    ) {
        std::vector <T> pois; // point of intersections
        auto& it1 = this->begin();
        auto& it2 = other.begin();
        while (it1 != this->end() || it2 != other.end()) {
            while (equality (*it1, *it2)) {
                pois.push_back (*it1);
                ++it1;
                ++it2;
            }
            // it1->pos < it2->pos
            while (
                inEquality (*it1, *it2) 
                && !equality (*it1, *it2)
            ) {
                ++it1;
            }
            while ( 
                !inEquality (*it1, *it2) 
                && !equality (*it1, *it2) 
            ) {
                ++it2;
            }
        }
        return pois;
    }
};

template <typename T, typename S, typename C>
struct HackedQueue : private priority_queue<T, S, C> {
private:
    std::vector <T>& m_container = Container (std::priority_queue <T, S, C> (*this));
public:
    static S& Container(priority_queue<T, S, C>& q) {
        return q.*&HackedQueue::c;
    }
    std::vector <T> :: iterator begin () {
        return m_container.begin();
    }
    std::vector <T> :: iterator end () {
        return m_container.end();
    }
    std::vector <T> :: reverse_iterator rbegin () {
        return m_container.rbegin();
    }
    std::vector <T> :: reverse_iterator rend () {
        return m_container.rend();
    }
    
    std::vector <T> getIntersections (
        const HackedQueue& other
    ) {
        std::vector <T> pois;
        std::unordered_set <T> has ( this->begin, this->end );
        for (const auto& x: other) {
            if (has.find (x) != has.end()) {
            	pois.push_back (x);   
            }
        }
        return pois;
    }
};
/*
*	TODO :: Make a interval based data structure 
*	with following features :- 
*	Tree of list or vectors or something
*	-> It depends on the width of the global interval 
*	-> It makes N nodes equal to width / 10 on each level
*	-> Each node is a reduced interval with width of parent->width / N
*	-> This rule recursively applies to each node.
*/


// #include "Event.hpp"
class Event;

class Trigger {
private:
	using EventTypeId = int;
private:
	static idGen;
	int typeId;
	int id;
	std::unordered_map < EventTypeId, std::unordered_set <std::shared_ptr <Event>> > eventsMap;
public:
	
	template <typename Trigger>
	void init () {
		typeId = getTypeid <Trigger> ();
		id = this->idGen++;
	}
	
	template <typename Event>
	std::shared_ptr <Event> addEvent (std::shared_ptr <Event> event_ptr) {
		eventsMap [getEventId <Event>()] = event_ptr;
	}
	
	template <typename Event>
	void removeEvent (std::shared_ptr <Event> event_ptr) {
		eventsMap.erase (getEventId <Event> ());
	}
	
	void executeEvents () {
		for (auto& [id, set] : eventsMap) {
			for (auto& event_ptr: set) {
				if (event_ptr != nullptr)
					event_ptr->execute ();
			}
		}
	}
};
Trigger::idGen = 0;


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
		int index = getIndex (pos, root->n, root->width);
		int expectedPos = getPos (index, root->n, root->width);
		if ( expectedPos == pos ) {
			int n = std::min (root->n, root->width % root->n);
			int width = root->width / n;
			auto node = std::make_shared <TreeNode> (
				TreeNode (
					width, pos, n
				)
			);
			root->insertNode (index, node);
		}
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
		
