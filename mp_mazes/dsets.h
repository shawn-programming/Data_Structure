/* Your code here! */
#pragma once

#include <iostream>
#include <vector>

using namespace std;

class DisjointSets {
public:
    DisjointSets(){}
    DisjointSets(int num){
        addelements(num);
    }
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
    vector<int> parentVec;
private:
    vector<int> elem;
    
};
