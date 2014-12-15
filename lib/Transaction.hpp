#ifndef TRANSACTION_HPP_
#define TRANSACTION_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iterator>

#include "ItemCount.hpp"

using namespace std;

class Transaction
{
  public:
    Transaction() {}
    Transaction(std::size_t id) : id_(id) {}
    ~Transaction() {
    	//for_each(tran_.begin(), tran_.end(), [&](ItemCount *pitem) { delete pitem; });
    }
    //void addItem(ItemCount* const pitem) {
    //  tran_.push_back(pitem);
    //}
    //void addItem(const ItemCount &item) {
    //  tran_.push_back(const_cast<ItemCount*>(&item));
    //}
    void addItem(shared_ptr<ItemCount> pitem) {
      tran_.push_back(pitem);
    }
    void addItem(const string &item) {
      //tran_.push_back(new ItemCount(item));
      tran_.push_back(make_shared<ItemCount>(item));
    }
    void clear() { tran_.clear(); }
    bool find(const string &item) {
      //return std::find_if(tran_.begin(), tran_.end(), item) == tran_.end();
      //return find_if(tran_.begin(), tran_.end(), [&](ItemCount const *pitem)->bool { return pitem->getItem() == item; }) != tran_.end();
      return find_if(tran_.begin(), tran_.end(), [&](shared_ptr<ItemCount> pitem)->bool { return pitem->getItem() == item; }) != tran_.end();
    }
    //void sort() { std::sort(tran_.begin(), tran_.end()); }
    void sort() { std::sort(tran_.begin(), tran_.end(),
    			[](shared_ptr<ItemCount> pitem1, shared_ptr<ItemCount> pitem2)->bool { return pitem1->getCount() > pitem2->getCount(); }); }
    void erase(unsigned int minsup) {
    	//tran_.erase(remove_if(tran_.begin(), tran_.end(), [&](ItemCount const *pitem)->bool { return pitem->getCount() < minsup; }), tran_.end());
//cout << "before erase" << endl;
    	//for_each(tran_.begin(), tran_.end(), [](shared_ptr<ItemCount> pitem)->void{ cout << pitem->getItem() << ": " << pitem->getCount() << endl; });
    	tran_.erase(remove_if(tran_.begin(), tran_.end(), [&](shared_ptr<ItemCount> pitem)->bool { return pitem->getCount() < minsup; }), tran_.end());
//cout << "after erase" << endl;
    	//for_each(tran_.begin(), tran_.end(), [](shared_ptr<ItemCount> pitem)->void{ cout << pitem->getItem() << ": " << pitem->getCount() << endl; });
//cout << endl;
    }
    size_t size() const { return tran_.size(); }


  public:
    //typedef vector<ItemCount*>::const_iterator const_iterator;
    typedef vector<shared_ptr<ItemCount>>::const_iterator const_iterator;

    const_iterator begin() const { return tran_.begin(); }
    const_iterator end() const { return tran_.end(); }

  private:
    size_t id_;
    //vector<ItemCount*> tran_;
    vector<shared_ptr<ItemCount> > tran_;
};

#endif
