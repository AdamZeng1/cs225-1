/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "lphashtable.h"

using hashes::hash;
using std::pair;

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
    unsigned int cur_hash = hash(key, size);
    while (table[cur_hash] != NULL) {
        cur_hash = (cur_hash + 1) % size;
    }
    table[cur_hash] = new pair<K, V>(key, value);
    should_probe[cur_hash] = true;
    elems++;
    if (shouldResize()) resizeTable();
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    unsigned int cur_hash = hash(key, size);
    while (table[cur_hash] != NULL && table[cur_hash]->first != key) {
        cur_hash = (cur_hash + 1) % size;
    }
    if (table[cur_hash] == NULL) return;
    else if (table[cur_hash]->first == key) {
        delete table[cur_hash];
        table[cur_hash] = NULL;
        elems--;
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    unsigned int cur_hash = hash(key, size);
    while (should_probe[cur_hash]) {
        if (table[cur_hash] != NULL) {
            if (table[cur_hash]->first == key) return cur_hash;
        }
        cur_hash = (cur_hash + 1) % size;
    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
    size_t new_size = findPrime(size * 2);
    pair<K, V>** new_table = new pair<K, V>*[new_size];
    delete[] should_probe;
    should_probe = new bool[new_size];
    for (size_t i = 0; i < new_size; i++) {
        new_table[i] = NULL;
        should_probe[i] = false;
    }

    for (size_t slot = 0; slot < size; slot++) {
        if (table[slot] != NULL) {
            unsigned int cur_hash = hash(table[slot]->first, new_size);
            while (new_table[cur_hash] != NULL) {
                cur_hash = (cur_hash + 1) % new_size;
            }
            new_table[cur_hash] = table[slot];
            should_probe[cur_hash] = true;
        }
    }

    delete[] table;
    table = new_table;
    size = new_size;
}
