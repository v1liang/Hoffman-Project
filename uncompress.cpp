#include <iostream>
#include <vector>
#include "Helper.hpp"
#include "HCTree.hpp"
#include <list>


int main(int argc, char* argv[]) {
    // your program's main execution code
    if(argc != 3){
        cerr << "ERROR: Incorrect parameters" << endl;
        cerr << "USAGE: ./uncompress <compressed_file> <uncompressed_file>" << endl;
    }
    else{
        bool serial = true;
        FancyInputStream input(argv[1]);
        if(input.filesize() == 0){
            FancyOutputStream out(argv[2]);
            return 0;
        }
         
        //false means use 256 version
        //true means use bt builder version
        int sum = 0;
        HCTree tree;

        if(serial == false){
            //header is all 256 file things put together
            vector<int> freqs(256, 0);
            for(unsigned int i = 0; i < freqs.size(); i++){
                freqs[i] = input.read_int();
                sum += freqs[i];
            }
            tree.build(freqs);
        }
        else{
            // list<unsigned char> list = deserialize(input, tree.getRoot());
            // tree.setRoot(deserializePostOrder(list.begin(), list.end(), sum));
            vector<int> freqs(256, 0);
            for(unsigned int i = 0; i < freqs.size(); i++){
                unsigned int val = 0;
                val |= input.read_byte() << 16;
                val |= input.read_byte() << 8;
                val |= input.read_byte();

                freqs[i] = val;
                sum += freqs[i];
            }
            tree.build(freqs);
        }
        

        FancyOutputStream out(argv[2]);

        //want to check if it is the end
        
        //ToDo: NEED TO EDIT BC SUM WILL NO LONGER BE USED;
        int index = 0;

        
            while(index != sum){
                //cout << symbol << std::endl;
                unsigned char symbol = tree.decode(input);
                //cout << symbol + " ";
                //cout << " "; 
                out.write_byte(symbol);
                index++;
            }

    
 


    }
            // int i = 0;
            // while(i < 10){                
            //     unsigned char symbol = tree.decode(input);
            //     //cout << symbol;
            //     i++;
            //     out.write_byte(symbol);
            // }

}
