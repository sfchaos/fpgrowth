#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <boost/tokenizer.hpp>

#include "ItemCount.hpp"
#include "Transaction.hpp"
#include "TransactionDB.hpp"
#include "Node.hpp"
#include "FPtree.hpp"

using namespace std;

class FPgrowth
{
public:
	FPgrowth(unsigned int minsup) : minsup_(minsup), fpt_(new FPtree) {}
	~FPgrowth() {
	  //for_each(header_.begin(), header_.end(), [&](ItemCount const *pitem) { delete pitem; });
	  delete fpt_;
	}
	void readTran(const string &fn) {
		string line;
		Transaction tran;
		string item;
		ifstream ifs(fn.c_str());

		// read each itemset
		while (ifs && getline(ifs, line)) {
			tran.clear();
			istringstream istrs((char *) line.c_str());
			// read each item
			while (istrs >> item) {
				// make the same items unique in a transaction
				if (!tran.find(item)) {
					// if item is not in item header, add it
cout << "item: " << item << endl;
					//vector<ItemCount*>::iterator result = find_if(header_.begin(), header_.end(), pMatchItemCount(item));
					//auto result = find_if(header_.begin(), header_.end(), [&](ItemCount *pitem){ return pitem->getItem() == item;});
					auto result = std::find_if(header_.begin(), header_.end(), [&](shared_ptr<ItemCount> pitem){ return pitem->getItem() == item; });
					shared_ptr<ItemCount> pitem = make_shared<ItemCount>(item);
					if (result == header_.end()) {
cout << "add item: " << item << endl;
						//ItemCount *pitem = new ItemCount(item);
						//shared_ptr<ItemCount> pitem = make_shared<ItemCount>(item);
						header_.push_back(pitem);
						tran.addItem(pitem);
					} else {
//cout << "increase count: " << item << endl;
						(*result)->incCount();
						tran.addItem(*result);
					}
					//tran.addItem(pitem);
				}
			}
	        trandb_.addTransaction(tran);
		}
	}

	void construct() {
		for_each(trandb_.begin(), trandb_.end(), [&](Transaction &tran) {
			// sort items by descending frequency order
			//sort(tran.begin(), tran.end());
			tran.sort();
			// delete items with frequency less than minimum support
			tran.erase(minsup_);
			// delete items with frequency less than minimum support
			header_.erase(remove_if(header_.begin(), header_.end(), [&](shared_ptr<ItemCount> pitem)->bool { return pitem->getCount() < minsup_; }), header_.end());
			sort(header_.begin(), header_.end(), [](shared_ptr<ItemCount> pitem1, shared_ptr<ItemCount> pitem2)->bool { return pitem1->getCount() > pitem2->getCount(); });
			// construct fptree
			fpt_->addTransaction(tran);
		});
	}

private:
	unsigned int minsup_;
	TransactionDB trandb_;
	//vector<ItemCount*> header_;
	vector<shared_ptr<ItemCount> > header_;
	FPtree *fpt_;
};
