#include "HCTree.hpp"
#include <iostream>
#include <stack>

void postOrderTraverse(HCNode* root){
    
    if(root == nullptr){
        return;
    }

    if(root->c0 != nullptr){
        postOrderTraverse(root->c1);
    }
    if(root->c1 != nullptr){
        postOrderTraverse(root->c0);
    }
    delete root;
    
}

HCTree::~HCTree() {
    postOrderTraverse(this->root);
}


HCNode* HCTree::getRoot(){
    return this->root;
}

void HCTree::setRoot(HCNode* node){
    this->root = node;
}
void HCTree::build(const vector<int>& freqs){

    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> forest;

    for(unsigned int i = 0; i < freqs.size(); i++){
        if(freqs[i] == 0){
            continue;
        }
        else{
            HCNode* node = new HCNode(freqs[i], i);
            //cout << node->symbol << endl;
            forest.push(node);
            this->leaves[i] = node;
            
        }
    }
    
    //start w/ 1st smallest node being popped

    
    while(forest.size() > 0){
        HCNode* first = forest.top();
        forest.pop();
        HCNode* second = forest.top();
        forest.pop();
        // cout << first->symbol << endl;
        // cout << second->symbol << endl;
        
        HCNode* insert = new HCNode(first->count + second->count, first->symbol);
        insert->c0 = first;
        insert->c0->p = insert;
        insert->c1 = second;
        insert->c1->p = insert;
       // cout << insert->count << endl;

        forest.push(insert);        
        if(forest.size()== 1){
            this->root = forest.top();
            //cout << this->root->symbol << endl;
            forest.pop();
        }
    }

}

void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const {

    //goal: given a symbol (unsigned char), encode based on hoffman tree
    int index = (int) symbol;
    HCNode* curr = this->leaves[index];
    stack<int> st;
    while(curr != this->root){

        if(curr == curr->p->c0){
            st.push(0);
        }
        else{
            st.push(1);
        }
        curr = curr->p;
    }

    while(!st.empty()){
        unsigned int curr = st.top();
        st.pop();
        out.write_bit(curr);
    }
}

unsigned char HCTree::decode(FancyInputStream & in) const{
    //starting from root, take in bit, travese down tree, return symbol
    HCNode* curr = this->root;

    
    while(curr->c0 != nullptr && curr->c1 != nullptr){
        int val = in.read_bit();
       // cout << val << endl;
        if(val == -1){
            return -1;
        }
        if(val == 0){
            curr = curr->c0;
        }
        if(val == 1){
            curr = curr->c1;
        }
    }
    return curr->symbol;
}
