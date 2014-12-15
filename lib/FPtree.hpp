#ifndef FPTREE_HPP_
#define FPTREE_HPP_

#include <iostream>
#include <algorithm>
#include <memory>
#include "Node.hpp"
#include "Transaction.hpp"

using namespace std;

class FPtree
{
	public:
	//FPtree() : root_(nullptr) {
	FPtree() {
		//root_ = new Node;
		current_ = root_;
	}

	~FPtree() {
		//delete root_;
	}

	//void addTransaction(const Transaction &tran) {
	void addTransaction(Transaction &tran) {
		//for_each(tran.begin(), tran.end(), [&](ItemCount const *item) {
		for_each(tran.begin(), tran.end(), [&](shared_ptr<ItemCount> pitem) {
			current_->incFreq();
//cout << item->getItem();
//cout << pitem->getItem();
			//Node *tmp = current_->findChild(item->getItem());
			//Node *tmp = current_->findChild(pitem->getItem());
			shared_ptr<Node> tmp = current_->findChild(pitem->getItem());
cout << "passing..." << endl;
			//if (tmp == NULL) {
			if (tmp == nullptr) {
				//Node *child = new Node(item->getItem());
				//Node *child = new Node(pitem->getItem());
				//shared_ptr<Node> child(new Node(pitem->getItem(), current_));
				shared_ptr<Node> child(new Node(pitem->getItem()));
				child->setParent(current_);
				current_->addChild(child);
				current_ = child;
				//delete tmp;
			} else {
				current_ = tmp;
			}
		});
		current_ = root_;
//cout << endl;
	}

	private:
		shared_ptr<Node> root_;
		shared_ptr<Node> current_;
		//Node *root_;
		////Node *current_;
};

#endif
