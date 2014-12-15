#ifndef TRANSACTIONDB_HPP_
#define TRANSACTIONDB_HPP_

#include <vector>
#include "Transaction.hpp"

using namespace std;

class TransactionDB
{
public:
	TransactionDB() {}
	~TransactionDB() {}
	void addTransaction(Transaction &tran) { trandb.push_back(tran); }

public:
    //typedef vector<Transaction>::const_iterator const_iterator;
    typedef vector<Transaction>::iterator iterator;
    iterator begin() { return trandb.begin(); }
    iterator end() { return trandb.end(); }
    size_t size() const { return trandb.size(); }

private:
	vector<Transaction> trandb;
};

#endif
