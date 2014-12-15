#ifndef ITEM_COUNT_HPP_
#define ITEM_COUNT_HPP_

#include <iostream>
#include <string>
#include "Item.hpp"

using namespace std;

class ItemCount : public Item
{
public:
   ItemCount() {}
   ItemCount(string item) : Item(item), count_(1) {}
   void incCount() { count_++; }
   unsigned int getCount() const { return count_; }
   ~ItemCount() {}

   bool operator < (const ItemCount &item) const {
	 if (count_ > item.count_) {
		return true;
	 } else if (count_ == item.count_) {
		if (this->getItem() <= item.getItem()) {
			return true;
		} else {
			return false;
		}
	 } else {
		return false;
	 }
   }

   bool operator < (ItemCount &item) const {
	 if (count_ > item.count_) {
		return true;
	 } else if (count_ == item.count_) {
		if (this->getItem() <= item.getItem()) {
			return true;
		} else {
			return false;
		}
	 } else {
		return false;
	 }
   }

private:
   unsigned int count_;
};

/*
class pMatchItemCount
{
public:
  pMatchItemCount(const ItemCount &item) : p_(&item) {}
  pMatchItemCount(ItemCount const *p1) : p_(p1) {}
  ~pMatchItemCount() { delete const_cast<ItemCount*>(p_); }
  bool operator() (ItemCount const *p2) const { return p_->getItem() == p2->getItem(); }
  bool operator() (const string& s) const { cout << "s is " << s << endl; return p_->getItem() == s; }
private:
  ItemCount const *p_;
};
*/

#endif
