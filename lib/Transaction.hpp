/**
 * @file Tranaction.hpp
 * @brief implementing transaction
 * @author sfchaos
 * @date 2014/12/16
 */

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

/**
 * @class Transaction
 * @brief class for Transaction
 */
class Transaction
{
  public:
    Transaction() {}
    Transaction(std::size_t id) : id_(id) {}
    ~Transaction() {
    }

    /**
     * @fn addItem(shared_ptr<ItemCount> pitem)
     * @brief add an item to the transaction
     * @param[in] pitem  a pointer to an item
     */
    void addItem(shared_ptr<ItemCount> pitem) {
      tran_.push_back(pitem);
    }

    /**
     * @fn addItem(const string &item)
     * @brief add an item to the transaction
     * @param[in] item  an item
     */
    void addItem(const string &item) {
      tran_.push_back(make_shared<ItemCount>(item));
    }

    /**
     * @fn clear()
     * @brief clear the transaction
     */
    void clear() { tran_.clear(); }

    /**
     * @fn find(const string &item)
     * @brief find the specified item in the transaction
     * @param[in] item  an item
     */
    bool find(const string &item) {
      return find_if(tran_.begin(), tran_.end(), [&](shared_ptr<ItemCount> pitem)->bool { return pitem->getItem() == item; }) != tran_.end();
    }

    /**
     * @fn sort()
     * @brief sort the items in the transaction
     */
    void sort() { std::sort(tran_.begin(), tran_.end(),
    			[](shared_ptr<ItemCount> pitem1, shared_ptr<ItemCount> pitem2)->bool { return pitem1->getCount() > pitem2->getCount(); }); }

    /**
     * @fn erase(unsigned int minsup)
     * @brief erase the items in the itemset with support less than the minimum support
     * @param[in] minsup  minimum support
     */
    void erase(unsigned int minsup) {
    	tran_.erase(remove_if(tran_.begin(), tran_.end(), [&](shared_ptr<ItemCount> pitem)->bool { return pitem->getCount() < minsup; }), tran_.end());
    }

    /**
     * @fn size()
     * @brief get the size of the transaction
     */
    size_t size() const { return tran_.size(); }


  public:
    typedef vector<shared_ptr<ItemCount>>::const_iterator const_iterator;

    const_iterator begin() const { return tran_.begin(); }
    const_iterator end() const { return tran_.end(); }

  private:
    size_t id_;
    vector<shared_ptr<ItemCount> > tran_;
};

#endif
