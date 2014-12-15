#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "ItemCount.hpp"

using namespace std;

class Node
{
	public:
	  Node() {}
	  Node(const ItemCount &item) : item_(item.getItem()), freq_(1) {}
	  //Node(const ItemCount &item, shared_ptr<Node> parent = nullptr) : item_(item.getItem()), parent_(parent), freq_(1) {}
	  ~Node() {
		  //for_each(children_.begin(), children_.end(), [](Node const *node) { delete node; });
		  //delete parent_;
	  }

	  //void addChild(Node *child) { children_.push_back(child); }
	  void addChild(shared_ptr<Node> child) { children_.push_back(child); }

	  //Node* findChild(const ItemCount &item) const {
	  shared_ptr<Node> findChild(const ItemCount &item) const {
		//vector<Node*>::iterator result = find_if(children_.begin(), children_.end(), [&](Node const *child)->bool {
		//auto result = find_if(children_.begin(), children_.end(), [&](Node const *child)->bool {
		auto result = find_if(children_.begin(), children_.end(), [&](shared_ptr<Node> child)->bool {
			return child->getItem() == item.getItem();
		});
		if (result == children_.end()) {
			//return NULL;
			return nullptr;
		} else {
			return *result;
		}
	  }

	  void setParent(shared_ptr<Node> parent) { parent_ = parent; }

	  void incFreq() { freq_++; }
	  string getItem() const { return item_; }

	private:
	  string item_;
	  unsigned int freq_;
	  //vector<Node*> children_;
	  vector<shared_ptr<Node>> children_;
	  //Node *parent_;
	  shared_ptr<Node> parent_;
};

#endif
