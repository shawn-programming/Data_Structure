/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if(first[curDim] == second[curDim]){
      return first < second;
    }
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double diffCurr = 0;
    double diffPot = 0;
    for(int i=0; i<Dim; i++){
      diffCurr += pow(target[i] - currentBest[i], 2);
      diffPot += pow(target[i] - potential[i], 2);
    }
    if(diffCurr == diffPot){
      return currentBest > potential;
    }
    return diffCurr > diffPot;
}

template <int Dim>
void quickSelect(vector<Point<Dim>>& newPoints, int index, int currDim, int start, int end){
  double last = newPoints[end][currDim];
  int i = start;
  int j = end;
  // cout<<"index: "<<i<<endl;
  

  while(i < j){
    // cout<<"Points: ";
    // for(unsigned int i=0; i<newPoints.size(); i++){
    //   cout<<newPoints[i]<<" ";
    // }
    // cout<<endl;
    while(((newPoints[i][currDim]<last) || (newPoints[i][currDim] == last && newPoints[i] < newPoints[end])) && i<j) i++;
    while(((newPoints[j][currDim]>last) || (newPoints[j][currDim] == last && newPoints[j] > newPoints[end])) && i<j) j--;

    Point<Dim> temp = newPoints[i];
    newPoints[i] = newPoints[j];
    newPoints[j] = temp;
  }
  // cout << "i is " << i << endl;
  // cout << "j is " << j << endl;
  if((newPoints[j][currDim]>last) || (newPoints[j][currDim] == last && newPoints[j] > newPoints[end])){
    Point<Dim> temp = newPoints[i];
    newPoints[i] = newPoints[end];
    newPoints[end] = temp;
    // cout << "i is " << i << endl;
    // cout << "j is " << j << endl;
  }

  // cout<<endl;
  if(i == index) return;

  if(i < index){
    start = i+1;
  }
  else{
    end = i-1;
  }

  return quickSelect(newPoints, index, currDim, start, end);
}

template <int Dim>
void KDTree<Dim>::MakeTree(KDTreeNode*& node, vector<Point<Dim>> points, int currDim, int start, int end) {
    if(start > end){
          return;
    }

    int mid = (end-start)/2 + start;
    // cout<<"curr dim: "<<currDim<<"index: "<<mid<<endl;
    quickSelect(points, mid, currDim, start, end);
    node = new KDTreeNode(points[mid]);
    // cout << "Mid: " << mid << " Start: " << start <<  " End: " << end << endl;
    // cout << "Point: ";
    // for(unsigned int i=0; i<points.size(); i++){
    //   cout<< points[i][currDim] <<" ";
    // }
    // cout << endl;

    MakeTree(node->left, points, (currDim+1)%Dim, start, mid-1);
    MakeTree(node->right, points, (currDim+1)%Dim, mid+1, end);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    vector<Point<Dim>> points = newPoints;
    
    MakeTree(root, points, 0, 0, points.size()-1);
    
    /**
     * @todo Implement this function!
     */
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  // *this = other;
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
void KDTree<Dim>::assign(KDTreeNode* to, KDTreeNode* from){
  if(!to){
    return;
  }
  
  to->point = from->point;

  assign(to->left, to->left);
  assign(to->right, to->right);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  assign(root, rhs->root);
  size = rhs->size;

  return *this;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* node){
  if(!node){
    return;
  }
  clear(node->left);
  if(node->left) delete node->left;
  clear(node->right);
  if(node->right) delete node->right;
}

template <int Dim>
void KDTree<Dim>::clear(){
  clear(root);
  delete root;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */

  clear();
}
template <int Dim>
bool KDTree<Dim>::valid(Point<Dim>& curr, const Point<Dim>& query, Point<Dim>& closest, int dim) const {
  double dist = 0;
  // cout << "Closest: " << closest[0] << " " << closest[1];
  for(int i=0; i<Dim; i++){
    dist += ((query[i] - closest[i]) * (query[i] - closest[i]));
  }
  // for(int i=0; i<Dim; i++){
    if(((curr[dim] - query[dim]) * (curr[dim] - query[dim])) > dist) {
      //cout << " i: " <<i <<" Dist: " << dist << " curr: " << ((curr[i] - query[i]) * (curr[i] - query[i])) << "point: " << curr[0] << " " << curr[1] <<endl;
      return false;
      }
  // }
  return true;
}

template <int Dim>
void KDTree<Dim>::findNearestR(KDTreeNode* curr, const Point<Dim>& query, Point<Dim>& closest, int currDim, bool& flag) const{
  if(!curr) return;
  // cout <<" curr Dim: " << currDim << " Point "<< curr->point[0] << " " << curr->point[1] << " visited" << endl;
  // cout <<"Current Point: " << curr->point[currDim] << " Query: " << query[currDim] << endl;
  if(smallerDimVal(query, curr->point, currDim)){
    findNearestR(curr->left, query, closest, (currDim+1)%Dim, flag);
    // cout <<"Current Point is: " << curr->point[0] << " " << curr->point[1] << endl;
    if(valid(curr->point, query, closest, currDim)) findNearestR(curr->right, query, closest, (currDim+1)%Dim, flag);
    // cout <<" done " <<endl;
  } 
  else{
    findNearestR(curr->right, query, closest, (currDim+1)%Dim, flag);
    // cout <<"Current Point is: " << curr->point[0] << " " << curr->point[1] << endl;
    if(valid(curr->point, query, closest, currDim)) findNearestR(curr->left, query, closest, (currDim+1)%Dim, flag);
  }
  if(!flag){
    closest = curr->point;
    // cout <<"Closest "<< curr->point[0] << " " << curr->point[1] << " visited, curr Dim: " << currDim << endl;
    flag = true;
  }

  if(shouldReplace(query, closest, curr->point)){
    closest = curr->point;
    // cout <<"Closest "<< curr->point[0] << " " << curr->point[1] << " visited, curr Dim: " << currDim << endl;
  }
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    bool flag = false;
    Point<Dim> best;
    findNearestR(root, query, best, 0, flag);
    // cout << "target is: " << best[0] <<" "<< best[1] << " Founded" << endl;
    return best;
}

 