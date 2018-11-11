#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num) {
	for (int count = 0; count < num; count++)
		_elems.push_back(-1);
}

int DisjointSets::find(int elem) {
	if (_elems[elem] < 0) return elem;
	else {
		int answer = find(_elems[elem]);
		_elems[elem] = answer;
		return answer;
	}
}

void DisjointSets::setunion(int a, int b) {
	while (_elems[a] >= 0)
		a = _elems[a];
	while (_elems[b] >= 0) 
		b = _elems[b];
	int newSize = _elems[a] + _elems[b];
	if (_elems[a] <= _elems[b]) {
		_elems[b] = a;
		_elems[a] = newSize;
	}
	else {
		_elems[a] = b;
		_elems[b] = newSize;
	}
}

int DisjointSets::size(int elem) {
	while (_elems[elem] >= 0) elem = _elems[elem];
	return _elems[elem] * -1;
}