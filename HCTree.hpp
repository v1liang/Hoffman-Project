#ifndef HCTREE_HPP
#define HCTREE_HPP
#include <queue>
#include <vector>
#include <fstream>
#include "Helper.hpp"
using namespace std;

/**
 * A Huffman Code Tree class
 */
class HCTree {
    private:
        HCNode* root;
        vector<HCNode*> leaves;

    public:
        /**
         * Constructor, which initializes everything to null pointers
         */
        HCTree() : root(nullptr) {
            leaves = vector<HCNode*>(256, nullptr);
        }

        ~HCTree();

        HCNode* getRoot();

        void setRoot(HCNode* node);

        /**
         * Use the Huffman algorithm to build a Huffman coding tree.
         */
        void build(const vector<int>& freqs);

        /**
         * Write to the given FancyOutputStream the sequence of bits coding the given symbol.
         */
        void encode(unsigned char symbol, FancyOutputStream & out) const;

        /**
         * Return symbol coded in the next sequence of bits from the stream.
         */
        unsigned char decode(FancyInputStream & in) const;
};
#endif // HCTREE_HPP
