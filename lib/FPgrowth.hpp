/**
 * @file FPgrowth.hpp
 * @brief implementing FP-growth algorithm
 * @author sfchaos
 * @date 2014/12/16
 */

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

/**
 * @class FPgrowth
 * @brief class for FP-growth algorithm
 */

class FPgrowth
{
public:
	FPgrowth(unsigned int minsup) : minsup_(minsup), fpt_(new FPtree) {}

	~FPgrowth() {
	  delete fpt_;
	}

    /**
     * @fn readTran(const string &fn)
     * @brief read transactions from file
     * @param[in] fn  a file containing transactions
     */
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
					auto result = std::find_if(header_.begin(), header_.end(), [&](shared_ptr<ItemCount> pitem){ return pitem->getItem() == item; });
					shared_ptr<ItemCount> pitem = make_shared<ItemCount>(item);
					if (result == header_.end()) {
cout << "add item: " << item << endl;
						header_.push_back(pitem);
						tran.addItem(pitem);
					} else {
						(*result)->incCount();
						tran.addItem(*result);
					}
				}
			}
	        trandb_.addTransaction(tran);
		}
	}

    /**
     * @fn construct()
     * @brief construct FP-tree
     */
	void construct() {
		for_each(trandb_.begin(), trandb_.end(), [&](Transaction &tran) {
			// sort items by descending frequency order
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
	/**　@brief minimum support */
	unsigned int minsup_;
	/**　@brief transaction database */
	TransactionDB trandb_;
	//vector<ItemCount*> header_;
	/**　@brief a vector of items with count */
	vector<shared_ptr<ItemCount> > header_;
	/**　@brief a pointer to the FP-tree */
	FPtree *fpt_;
};
