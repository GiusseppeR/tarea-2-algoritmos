#ifndef TAREALOG_BINOMIALTREE_HPP
#define TAREALOG_BINOMIALTREE_HPP

#include <vector>

using namespace std;

struct BinomialTree{
    int degree;
    pair<int,int> data;
    vector<BinomialTree*> children;
};

void addBinomialTrees(BinomialTree& t1, BinomialTree& t2);
vector<BinomialTree> makeBinomialForest(vector<BinomialTree> array);

#endif
