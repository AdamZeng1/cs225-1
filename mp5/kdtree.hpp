/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
	if (first[curDim] == second[curDim]) return first < second;
	return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
	double bestDistance = 0;
	double curDiff;
	for (unsigned i = 0; i < 3; i++) {
		curDiff = (currentBest[i] - target[i]);
		bestDistance += curDiff * curDiff;
	}

	double potnDistance = 0;
	for (unsigned i = 0; i < 3; i++) {
		curDiff = (potential[i] - target[i]);
		potnDistance += curDiff * curDiff;
	}

    return potnDistance < bestDistance;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
	vector<Point<Dim>> newVect = ; // Put vector here wtf
	size = 0;
	root = helper(newPoints, 0, 0, newPoints.size());
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::helper(const vector<Point<Dim>>& newPoints, int dimension, int startidx, int endidx) {
	if (startidx == endidx || newPoints.empty()) return NULL;
	int mid = (startidx + endidx) / 2;
	Point<Dim> curPoint = quickSelect(newPoints, mid, dimension, startidx, endidx);

	KDTreeNode * newNode = new KDTreeNode(curPoint);

	newNode->left = helper(newPoints, (dimension + 1) % Dim, startidx, mid);
	newNode->right = helper(newPoints, (dimension + 1) % Dim, mid + 1, endidx);

	size++;

	return newNode;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(const vector<Point<Dim>>& newPoints, int k, int dimension, int startidx, int endidx) {
	if (endidx == startidx) return newPoints[startidx];

	//if (k > 0 && k <= endidx - startidx + 1) {

		int idx = partition(newPoints, dimension, startidx, endidx);

		if (idx - startidx == k - 1) 
			return newPoints[idx];

		else if (idx - startidx > k - 1)
			return quickSelect(newPoints, k, dimension, startidx, idx - 1);

		else // (idx - startidx < k - 1)
			return quickSelect(newPoints, k, dimension, idx + 1, endidx);

	//}
	//return Point<Dim>;
}

template <int Dim>
int KDTree<Dim>::partition(const vector<Point<Dim>>& newPoints, int dimension, int start, int end) {
	Point<Dim> curPoint = newPoints[end];
	int i = start;
	for (int j = start; j < (end - start); j++) {
		if (smallerDimVal(newPoints[j], curPoint, dimension)) {
			Point<Dim> & temp = newPoints[i];
			newPoints[i] = newPoints[j];
			newPoints[j] = temp;
			i++;
		}
	}
	Point<Dim> temp = newPoints[i];
	newPoints[i] = newPoints[end];
	newPoints[end] = temp;
	return i;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

