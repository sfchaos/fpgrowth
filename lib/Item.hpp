#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Item
{
  public:
    Item() {}
    Item(string item) : item_(item) {}
    virtual ~Item() {}
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
    string item_;
};

ostream& operator << (ostream& os, const Item& item)
{
  os << item.getItem();
  return os;
}

#endif
