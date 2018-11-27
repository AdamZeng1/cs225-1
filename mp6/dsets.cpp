#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num) {
	// Loop, adding elements to array
	for (int count = 0; count < num; count++)
		_elems.push_back(-1);
}

int DisjointSets::find(int elem) {
	// If elem is root, return it
	if (_elems[elem] < 0) return elem;
	// Else recurse up the ds until root
	else {
		int answer = find(_elems[elem]);
		_elems[elem] = answer;
		return answer;
	}
}

void DisjointSets::setunion(int a, int b) {
	// Find a's root and set a equal to it
	while (_elems[a] >= 0)
		a = _elems[a];
	// Find b's root and set b equal to it
	while (_elems[b] >= 0) 
		b = _elems[b];
	int newSize = _elems[a] + _elems[b];
	// If first ds is smaller than second, set b parent to a
	if (_elems[a] <= _elems[b]) {
		_elems[b] = a;
		_elems[a] = newSize;
	}
	// Else, set a parent to b
	else {
		_elems[a] = b;
		_elems[b] = newSize;
	}
}

int DisjointSets::size(int elem) {
	// Find root node, return its number * -1 (height)
	while (_elems[elem] >= 0) elem = _elems[elem];
	return _elems[elem] * -1;
}