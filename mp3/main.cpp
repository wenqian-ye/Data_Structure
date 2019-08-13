#include "list.h"

int main() {
    List<int> test;
    srand(time(NULL));

    for(unsigned i = 0; i < 10; i+=2){
        int r = rand()%10;
        test.insertBack(r);
    }
    List<int> test1;
    srand(time(NULL));
    for(unsigned i = 1; i < 16 ; i+=1){
        int r = rand()%10;
        test1.insertBack(r);
    }

    test1.print(cout);
    test1.sort();

    test1.print(cout);
    return 0;
}
