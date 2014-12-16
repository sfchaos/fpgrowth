/**
 * @file Itemset.hpp
 * @brief implementing itemset
 * @author sfchaos
 * @date 2014/12/16
 */

#ifndef ITEMSET_HPP_
#define ITEMSET_HPP_

#ifndef ITEMSET_HPP_
#define ITEMSET_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <boost/algorithm/string/join.hpp>
#include "item.hpp"
#include "transaction.hpp"

using namespace std;

/**
 * @class Itemset
 * @brief class for itemset
 */
class Itemset
{
  public:
    Itemset() {}
    ~Itemset() {}

    /**
     * @fn addItem(const Item &item)
     * @brief add an item to itemset
     * @param[in] item  an item
     */
    void addItem(const Item &item) { is_.push_back(item); }

    /**
     * @fn addItem(const string &item)
     * @brief add an item to itemset
     * @param[in] item  an item
     */
    void addItem(const string &item) { is_.push_back(Item(item)); }

    /**
     * @fn getItemset()
     * @brief get the itemset
     */
    string getItemset() const {
      vector<string> result(is_.size());
      transform(is_.begin(), is_.end(),  result.begin(),
                [](const Item &item) { return item.getItem(); });
      return "{" + boost::algorithm::join(result, ",") + "}";
    }

    /**
     * @fn addId()
     * @brief add an ID
     */
    void addId(size_t id) { id_ = id; }

    /**
     * @fn getId()
     * @brief get the ID
     */
    size_t getId() const { return id_; }

    /**
     * @fn getImp()
     * @brief get the importance
     */
    double getImp() const { return imp_; }

    /**
     * @fn addImp()
     * @brief add an importance
     */
    void addImp(double imp) { imp_ = imp; }

    /**
     * @fn clear()
     * @brief clear the itemset
     */
    void clear() { is_.clear(); };

    /**
     * @fn size()
     * @brief get the itemset size
     */
    size_t size() const { return is_.size(); }

    /**
     * @fn sort()
     * @brief sort the items in the itemset
     */
    void sort() {
      std::sort(is_.begin(), is_.end());
    }
		const vector<size_t> &getTranId() const {
			return tranid_;
		}

    /**
     * @fn matchTran(TransactionSet &transet)
     * @brief  match the items in the itemset with the transaction
     * @param[in] transet  a set of transactions
     */
    void matchTran(TransactionSet &transet) {
      vector<Transaction>::const_iterator itr = transet.begin();
      vector<Transaction>::const_iterator itrEnd = transet.end();

      this->sort();

      while (itr != itrEnd) {
        bool matched = isSubset(is_, *itr);
        if (matched) {
          tranid_.push_back(itr - transet.begin());
        }
        itr++;
      }
    }

    bool operator < (const Itemset& is) const {
      return imp_ < is.imp_;
    }

  public:
    typedef vector<Item>::const_iterator const_iterator;

    const_iterator begin() const { return is_.begin(); }
    const_iterator end() const { return is_.end(); }


  private:
    /**　@brief an itemset */
    vector<Item> is_;
    /**　@brief the importance of the itemset */
    double imp_;
    /**　@brief the id of the itemset */
    size_t id_;
    /**　@brief a vector of transaction IDs */
    vector<size_t> tranid_;

    /**
     * @fn isSubset(vector<T> &a, const Transaction &tran)
     * @brief  judge whether the transaction is a subset
     * @param[in] transet  a set of transactions
     */
    template <typename T>
    bool isSubset(vector<T> &a, const Transaction &tran) {
      return includes(tran.begin(), tran.end(), a.begin(), a.end());
    }

};

#endif
