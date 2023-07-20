#include <iostream>
#include <vector>
#include "Helper.hpp"
#include "HCTree.hpp"
using namespace std;

void serializePostOrder(HCNode* root, FancyOutputStream & out){
    if(root == nullptr){
        out.write_byte('#');
    }
    else{
        out.write_byte(root->symbol);
        serializePostOrder(root->c0, out);
        serializePostOrder(root->c1, out);
    }
}

int main(int argc, char* argv[]) {
    //Parse the command line arguments and throw an error message if the user runs your program incorrectly

    if(argc != 3){
        cerr << "ERROR: Incorrect parameters" << endl;
        cerr << "USAGE: ./compress <original_file> <compressed_file>" << endl;
    }
    else{
        FancyInputStream input(argv[1]);

        if(input.filesize() == 0){
            FancyOutputStream out(argv[2]);
            return 0;
        }

        vector<int> freqs(256, 0);
        int cur = input.read_byte();
        while(cur != -1){
            freqs[cur] = freqs[cur] + 1;
            //cout << cur << endl;
            cur = input.read_byte();
        }

        HCTree tree;
        tree.build(freqs);
        bool serial = true; //true = use 4 byte chunks as headers, false = use 3 byte chunks
        FancyOutputStream out(argv[2]);

        if(serial == false){
            for(unsigned int i = 0; i < freqs.size(); i++){
                out.write_int(freqs[i]);
            }
        }
        else{
            for(unsigned int i = 0; i < freqs.size(); i++){
                out.write_byte(freqs[i] >> 16);
                out.write_byte(freqs[i] >> 8);
                out.write_byte(freqs[i]);
            }
        }
    
        input.reset();//move to beginning of file;

        cur = input.read_byte();
        while(cur != -1){
            unsigned char symbol = (unsigned char) cur;
            tree.encode(symbol, out);
            cur = input.read_byte();
        }
    }

 
}
