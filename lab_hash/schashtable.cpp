/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "schashtable.h"
 
#include <iostream>

using hashes::hash;
using std::list;
using std::pair;
using std::vector;
  
template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new list<pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new list<pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new list<pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    unsigned int cur_hash = hash(key, size);
    table[cur_hash].push_front(pair<K, V>(key, value));
    elems++;
    if (shouldResize()) resizeTable();
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    unsigned int cur_hash = hash(key, size);
    if (table[cur_hash].empty()) return;
    typename list<pair<K, V>>::iterator it = table[cur_hash].begin();
    while (it != table[cur_hash].end()) {
        if ((*it).first == key) {
            table[cur_hash].erase(it);
            elems--;
            break;
        }
        it++;
    }
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    unsigned int cur_hash = hash(key, size);
    typename list<pair<K, V>>::iterator it = table[cur_hash].begin();
    while (it != table[cur_hash].end()) {
        if ((*it).first == key) return (*it).second;
        it++;
    }
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hash(key, size);
    pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new list<pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    size_t new_size = findPrime(size * 2);

    list<pair<K, V>>* new_table = new list<pair<K, V>>[new_size];

    for (auto iter = begin(); iter != end(); iter++) {
        unsigned cur_hash = hash(iter->first, new_size);
        pair<K, V> temp(iter->first, iter->second); 
        new_table[cur_hash].push_front(temp);
    } 
    delete[] table;
    table = new_table;
    size = new_size;
}
