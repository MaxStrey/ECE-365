#include "heap.h"
#include <iostream>
#include <climits>
using namespace std;

// Initializes the heap.
heap::heap(int capacity)
{
    data.resize(capacity + 1);
    mapping = new hashTable(capacity * 2);
    this->capacity = capacity;
    size = 0;
}

// Inserts a node into the tree at the bottom and uses percolate up
// to put it into place
int heap::insert(const std::string &id, int key, void *pv)
{

    if (size == capacity)
    {
        return 1;
    }
    if (mapping->contains(id) == false)
    {
        size++;
        data[size].id = id;
        data[size].key = key;
        data[size].pData = pv;
        mapping->insert(id, &data[size]);
        percolateUp(size);
    }
    else
    {
        return 2;
    }
    return 0;
}

// sets a new key for a node specified by its ID
int heap::setKey(const std::string &id, int key)
{
    if (!(mapping->contains(id)))
        return 1;

    int old, loc;
    node *pn = static_cast<node *>(mapping->getPointer(id));

    loc = getPos(pn);
    old = pn->key;
    pn->key = key;

    if (key > old)
    {
        percolateDown(loc);
    }
    else if (key < old)
    {
        percolateUp(loc);
    }
    return 0;
}

// deletes the topmost node, replaces it with the last node in the data vector,
// and uses percolateDown from the top to adjust the tree
int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (size == 0)
        return 1;

    mapping->remove(data[1].id);
    if (pId != NULL)
        *pId = data[1].id;
    if (pKey != NULL)
        *pKey = data[1].key;
    if (ppData != NULL)
        *(static_cast<void **>(ppData)) = data[1].pData;

    data[1] = data[size--];
    percolateDown(1);
    return 0;
}

// strategy from book where remove is a combination of
// decreaseKey(id, infinity) (here, smallest int is used for infinity)
// and deleteMin()
int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    if (!(mapping->contains(id)))
        return 1;

    node *pn = static_cast<node *>(mapping->getPointer(id));
    if (pKey != NULL)
        *pKey = pn->key;
    if (ppData != NULL)
        *(static_cast<void **>(ppData)) = pn->pData;

    setKey(id, INT_MIN);
    deleteMin();
    return 0;
}

// percolat up -- starts with a value at the bottom of the tree
//which works its way up to the top via swaps with larger values
void heap::percolateUp(int posCur)
{
    node inserted = data[posCur];
    for (; posCur > 1 && inserted.key < data[posCur / 2].key; posCur /= 2)
    {
        data[posCur] = data[posCur / 2];
        mapping->setPointer(data[posCur].id, &data[posCur]);
    }
    data[posCur] = inserted;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

// percolate down -- inverse of percolate up
// strategy from textbook used where a pair of uneven nodes are
// made even (left to right)
void heap::percolateDown(int posCur)
{
    int child;
    node removed = data[posCur];
    for (; posCur * 2 <= size; posCur = child)
    {
        child = posCur * 2;
        if (child != size && data[child + 1].key < data[child].key)
            child++;
        if (data[child].key < removed.key)
        {
            data[posCur] = data[child];
            mapping->setPointer(data[posCur].id, &data[posCur]);
        }
        else
            break;
    }
    data[posCur] = removed;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

// Gets the position of a node in the data vector
int heap::getPos(node *pn)
{
    return (pn - &data[0]);
}

// ONLY FOR DEBUGGING.. NOT USED IN REAL PROGRAM
void heap::printHeap()
{
    cout << "Start: ";
    for (int i = 1; i <= size; i++)
    {
        cout << i << ": " << data[i].id << "|" << data[i].key << ",";
    }
    cout << " End\n";
}