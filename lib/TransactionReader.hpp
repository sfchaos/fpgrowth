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


class TransactionReader
{
  public:
    TransactionReader() {}
    ~TransactionReader() {}
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
