/********************************************************************************* 
* Order.cpp
* Implementation of performing operations of Binary Search Tree by using Dictionary ADT
*********************************************************************************/
#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    int line_count = 0;
    string line;
    Dictionary newD = Dictionary();
    ifstream in;
    ofstream out;
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    while (getline(in, line)) {
      line_count++;
      newD.setValue(line, line_count);
    }

    out << newD << endl;
    out << newD.pre_string() << endl;

    in.close();
    out.close();

    return(EXIT_SUCCESS);
}
