/* Your code here! */

#include "dsets.h"

void DisjointSets::addelements(int num){
    for(int i=0; i<num; i++){
        parentVec.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    if(parentVec[elem] < 0) return elem;

    int answer = find(parentVec[elem]);
    parentVec[elem] = answer;

    return answer;
}   

void DisjointSets::setunion(int a, int b){
    int aIdx = find(a);
    int bIdx = find(b);
    
    if(aIdx == bIdx) return;

    if(parentVec[aIdx] <= parentVec[bIdx]){
        parentVec[aIdx] += parentVec[bIdx];
        parentVec[bIdx] = aIdx;
    }
    else{
        parentVec[bIdx] += parentVec[aIdx];
        parentVec[aIdx] = bIdx;
    }
}

int DisjointSets::size(int elem){
    cout << std::endl;
    return -parentVec[find(elem)];
}