/**
 * @file ItemCount.hpp
 * @brief implementing item with count(frequency)
 * @author sfchaos
 * @date 2014/12/16
 */

#ifndef ITEM_COUNT_HPP_
#define ITEM_COUNT_HPP_

#include <iostream>
#include <string>
#include "Item.hpp"

using namespace std;

/**
 * @class ItemCount
 * @brief class for item with count(frequency)
 */
class ItemCount : public Item
{
public:
   ItemCount() {}
   ItemCount(string item) : Item(item), count_(1) {}

   /**
    * @fn incCount()
    * @brief increment by one the count of the item
    */
   void incCount() { count_++; }

   /**
    * @fn getCount()
    * @brief increment by one the count of the item
    */
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
   /**　@brief a count of the item */
   unsigned int count_;
};

#endif
