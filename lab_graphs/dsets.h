/* Your code here! */

#ifndef DSETS_H
#define DSETS_H

#include <vector>
#include <string>


using namespace std;
//using namespace cs225;

class DisjointSets{
public:
    vector<int > DS;

    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    //int size(int elem);

    DisjointSets();
    DisjointSets(int n);

    //~DisjointSets();








};



#endif