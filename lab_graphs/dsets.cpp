/* Your code here! */
include "dsets.h"

//using namespace cs225;

DisjointSets::DisjointSets(){
    DS.resize(100, -1);
}

DisjointSets::DisjointSets(int n){
    DS.resize(n, -1);
}

void DisjointSets::addelements(int num){
    if(DS.size() == 0)
        DS.resize(num, -1);
    else{
        int newSize = int(DS.size() ) + num;
        DS.resize(newSize, -1);
    }
}

int DisjointSets::find(int elem){
    if(DS[elem] < 0 )
        return elem;
    else{
        int temp = find(DS[elem]);
        DS[elem] = temp;
        return temp;
    }
    //return DS[elem] = find(DS[elem]);
}

void DisjointSets::setunion(int a, int b){
    int root1 = find(a);
    int root2 = find(b);

    int newSize = DS[root1] + DS[root2];

    if(DS[root1] < DS[root2]){
        DS[root2] = root1;
        DS[root1] = newSize;
    }
    else{
        DS[root1] = root2;
        DS[root2] = newSize;
    }
}