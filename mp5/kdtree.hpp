/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
	if (curDim < 0 || curDim >= Dim) return false;  // Check if curDim is valid
    if(first[curDim]==second[curDim])  // If the point have same value at curDim, tiebreak 
      	return first<second;
    return (first[curDim] < second[curDim]);  // Tiebreak
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double cur_dist = 0, pot_dist = 0;
    for(int i=0; i<Dim;i++){  // Add up squares of differences for each dimension
       	cur_dist += ((target[i]-currentBest[i])*(target[i]-currentBest[i]));
       	pot_dist += ((target[i]-potential[i])*(target[i]-potential[i]));
    }
    if(cur_dist==pot_dist) return potential < currentBest;  // Tiebreak
    return pot_dist<cur_dist;
}

template <int Dim>
unsigned KDTree<Dim>::quickSelect_position(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned pivotIndex){
  	Point<Dim> pivotValue = list[pivotIndex];
  	//swap pivot value and end of list
  	Point<Dim> temp = list[pivotIndex];
  	list[pivotIndex] = list[right];
  	list[right] = temp;
  	unsigned storeIndex = left;
  	//move through all points moving those less than pivot value
  	for(unsigned i = left;i<right;i++){
    	if(smallerDimVal(list[i],pivotValue,dimension)){
    		//swap if less than
      		temp = list[storeIndex];
      		list[storeIndex] = list[i];
      		list[i] = temp;
      		storeIndex++;
    	}
  	}
  	temp = list[storeIndex];
  	list[storeIndex] = list[right];
  	list[right] = temp;
  	return storeIndex;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned k){
  	if(left==right) return list[left];
  	unsigned pivotIndex = k;
  	pivotIndex = quickSelect_position(list,dimension,left,right,pivotIndex);  // partition
  	if(k==pivotIndex) return list[k];
  	else if(k<pivotIndex)  // Traverse to left of pivot
    	return quickSelect(list, dimension, left, pivotIndex-1, k);
  	else return quickSelect(list, dimension, pivotIndex+1, right, k); // Traverse to right of pivot
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::ctorHelper(vector<Point<Dim>>& points_, int dimension, unsigned left, unsigned right){
  	if(points_.empty()||left<0||right>=points_.size()||right<0||left>=points_.size())
    	return NULL;  // Check if parameters are in bounds
  	if(left>right) return NULL;
  	unsigned median_idx = (left+right)/2;  // Choose pivot index
  	KDTreeNode* subroot_ = new KDTreeNode(quickSelect(points_,dimension%Dim,left,right,median_idx));
  	size+=1;
  	dimension++;
  	subroot_->left = ctorHelper(points_,dimension,left,median_idx-1);  // Recurse left side
  	subroot_->right = ctorHelper(points_,dimension,median_idx+1,right);  // Recurse right side
 	return subroot_;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    size = 0;
    vector<Point<Dim>> points_;
    points_.assign(newPoints.begin(), newPoints.end());
    root = ctorHelper(points_, 0, 0, points_.size()-1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
	copy(this->root, other.root);
	size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  	if (this != NULL) clear(root);
  	copy(this->root, rhs.root);
  	size = rhs.size;
  	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  	clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {
    return findNearestNeighbor(root, query, 0);  // Use helper function
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode * subroot, const Point<Dim>& query, int dimension) const {
	Point<Dim> currentBest = subroot->point;
	bool flag;
	// Check bounds
	if (subroot->left == NULL && subroot->right == NULL) return subroot->point;
	// Should traverse left subtree?
	if (smallerDimVal(query, subroot->point, dimension)) {
		if (subroot->left == NULL)  // If can't traverse left, then traverse right
			currentBest = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
		else  // Traverse left
			currentBest = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
		flag = true;  // Set left flag to true
	}
	// Should traverse right subtree?
	else {
		if (subroot->right == NULL)  // If can't traverse right, then traverse left
			currentBest = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
		else  // Traverse right
			currentBest = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
		flag = false;  // Set left flag to false
	}
	// If current node's point is closer to target, switch it
	if (shouldReplace(query, currentBest, subroot->point)) currentBest = subroot->point;
	
	// Calculate radius of closest point and then also split distance
	double radius = 0;
	for (int i = 0; i < Dim; i++) {
		radius += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
	}
	double split_distance = subroot->point[dimension] - query[dimension];
	split_distance = split_distance * split_distance;

	// Check if we need to traverse the other subtree or not
	if (split_distance <= radius) {
		KDTreeNode * need_to_check = flag ? subroot->right : subroot->left;
		if (need_to_check != NULL) {  // If we can traverse other subtree, then traverse
			Point<Dim> otherBest = findNearestNeighbor(need_to_check, query, (dimension + 1) % Dim);
			// Replace currentbest if need be
			if (shouldReplace(query, currentBest, otherBest)) currentBest = otherBest;
		}
	}
	return currentBest;
}

// Helper function for destructor and = operator
template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * subroot) {
	if (subroot == NULL) return;
	if (subroot->left != NULL) clear(subroot->left);
	if (subroot->right != NULL) clear(subroot->right);
	delete subroot;
	subroot = NULL;
}

// Helper function for copy constructor and = operator
template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * subroot, KDTreeNode * othersubroot) {
	subroot = new KDTreeNode();
	subroot->point = othersubroot->point;
	copy(subroot->left, othersubroot->left);
	copy(subroot->right, othersubroot->right);
}