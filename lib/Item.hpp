/**
 * @file Item.hpp
 * @brief implementing item
 * @author sfchaos
 * @date 2014/12/16
 */

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @class Item
 * @brief class for item
 */
class Item
{
  public:
    Item() {}
    Item(string item) : item_(item) {}
    virtual ~Item() {}

    /**
     * @fn getItem()
     * @brief get the item
     */
    string getItem() const { return item_; }

    virtual bool operator == (string &s) const {
      return item_ == s;
    }

    virtual bool operator == (const string &s) const {
      return item_ == s;
    }

    virtual bool operator == (const Item &item) const {
      return item_ == item.item_;
    }

    virtual bool operator == (Item &item) const {
      return item_ == item.item_;
    }

    virtual bool operator < (const Item &item) const {
      return item_ < item.item_;
    }

    virtual bool operator < (Item &item) const {
      return item_ < item.item_;
    }

  private:
	/**　@brief an item */
    string item_;
};

ostream& operator << (ostream& os, const Item& item)
{
  os << item.getItem();
  return os;
}

#endif
