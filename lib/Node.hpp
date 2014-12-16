/**
 * @file Node.hpp
 * @brief implementing FP-tree Node
 * @author sfchaos
 * @date 2014/12/16
 */

#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "ItemCount.hpp"

using namespace std;

/**
 * @class Node
 * @brief class for FP-tree Node
 */
class Node
{
	public:
	  Node() {}
	  Node(const ItemCount &item) : item_(item.getItem()), freq_(1) {}
	  ~Node() {
	  }

	  /**
	   * @fn addChild(shared_ptr<Node> child)
	   * @brief add a child to the FP-Node
	   * @param[in] child  a pointer to a Node
	   */
	  void addChild(shared_ptr<Node> child) { children_.push_back(child); }

	  /**
	   * @fn findChild(const ItemCount &item)
	   * @brief find a child node of the specified item
	   * @param[in] item  an item with count(frequency)
	   */
	  shared_ptr<Node> findChild(const ItemCount &item) const {
		auto result = find_if(children_.begin(), children_.end(), [&](shared_ptr<Node> child)->bool {
			return child->getItem() == item.getItem();
		});
		if (result == children_.end()) {
			return nullptr;
		} else {
			return *result;
		}
	  }

	  /**
	   * @fn setParent(shared_ptr<Node> parent)
	   * @brief set the parent node
	   * @param[in] parent  a pointer to a Node
	   */
	  void setParent(shared_ptr<Node> parent) { parent_ = parent; }

	  /**
	   * @fn incFreq()
	   * @brief increment by one the frequency of the node
	   */
	  void incFreq() { freq_++; }

	  /**
	   * @fn getItem()
	   * @brief get the item
	   */
	  string getItem() const { return item_; }

	private:
	  /**　@brief an item */
	  string item_;
	  /**　@brief the frequency of the item */
	  unsigned int freq_;
	  /**　@brief the children of this node */
	  vector<shared_ptr<Node>> children_;
	  /**　@brief the parent of this node */
	  shared_ptr<Node> parent_;
};

#endif
