/**
 * @file FPtree.hpp
 * @brief implementing FP-tree algorithm
 * @author sfchaos
 * @date 2014/12/16
 */

#ifndef FPTREE_HPP_
#define FPTREE_HPP_

#include <iostream>
#include <algorithm>
#include <memory>
#include "Node.hpp"
#include "Transaction.hpp"

using namespace std;


/**
 * @class FPtree
 * @brief class for FP-tree
 */

class FPtree
{
	public:
	FPtree() {
		current_ = root_;
	}

	~FPtree() {
	}

    /**
     * @fn addTransaction(Transaction &tran)
     * @brief add a transaction to FP-tree
     * @param[in] tran  a transaction
     */
	void addTransaction(Transaction &tran) {
		for_each(tran.begin(), tran.end(), [&](shared_ptr<ItemCount> pitem) {
			current_->incFreq();
			shared_ptr<Node> tmp = current_->findChild(pitem->getItem());
cout << "passing..." << endl;
			if (tmp == nullptr) {
				shared_ptr<Node> child(new Node(pitem->getItem()));
				child->setParent(current_);
				current_->addChild(child);
				current_ = child;
			} else {
				current_ = tmp;
			}
		});
		current_ = root_;
	}

	private:
		/**　@brief a pointer to root node */
		shared_ptr<Node> root_;
		/**　@brief a pointer to current node */
		shared_ptr<Node> current_;
};

#endif
