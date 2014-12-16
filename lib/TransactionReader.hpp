/**
 * @file TranactionReader.hpp
 * @brief implementing the reader of transaction
 * @author sfchaos
 * @date 2014/12/16
 */

#ifndef TRANSACTION_READER_
#define TRANSACTION_READER_

#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <boost/tokenizer.hpp>

#include "Transaction.hpp"
#include "TransactionDB.hpp"

/**
 * @class TransactionReader
 * @brief class for Transaction reader
 */
class TransactionReader
{
  public:
    TransactionReader() {}
    ~TransactionReader() {}

    /**
     * @fn readTransaction(string fn, TransactionDB &trandb)
     * @brief read transaction
     * @param[in] fn  a file containing transaction
     * @param[in] trandb  a transaction database containing transactions
     */
    void readTransaction(string fn, TransactionDB &trandb) {
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
          vector<string>::iterator itr_tr;
          if (tran.find(item)) {
            tran.addItem(item);
          }
        }
        trandb.addTransaction(tran);
      }
    }
};

#endif
