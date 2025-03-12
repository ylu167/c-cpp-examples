/********************************************************************************* 
* Shuffle.cpp
* Implementation of performing shuffle operations and counting the numbers of shuffles as it goes until the list is brought back to its original order
*********************************************************************************/
#include "List.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    int n = 0;
    if (argc > 0){
        n = std::stoi(argv[1]);
    }
    for(int i = 1; i <= n; i++){
        List L;
        List L_merge;
        
        for(int j = 0; j < i; j++){
            L.insertAfter(j);
            L.moveNext();
            L_merge.insertAfter(j);
            L_merge.moveNext();
        }

        int equal = 0;
        int count = 0;

        while(equal == 0){
            count++;
            List left;
            List right;
            L_merge.moveFront();
            for (int j = 1; j <= L.length(); j++){
                if (L_merge.position() >= L_merge.length() / 2){
                    right.insertAfter(L_merge.peekNext());
                    right.moveNext();
                }else{
                    left.insertAfter(L_merge.peekNext());
                    left.moveNext();
                }
                L_merge.moveNext();
            }
            //cout << left << endl;
            //cout << right << endl;
            
            int is_right = 1;
            left.moveFront();
            right.moveFront();
            L_merge.clear();
            for (int j = 1; j <= L.length(); j++){
                if (is_right == 1){
                    L_merge.insertAfter(right.peekNext());
                    L_merge.moveNext();
                    right.moveNext();
                    is_right = 0;
                }else if (is_right == 0){
                    L_merge.insertAfter(left.peekNext());
                    L_merge.moveNext();
                    left.moveNext();
                    is_right = 1;
                }
            }

            if (L.equals(L_merge)){
                cout << " ";
                printf("%-16d", i);
                equal = 1;
                cout << count << endl;
            }
        }
    }
    return 0;
}
