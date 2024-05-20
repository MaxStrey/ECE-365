#include "heap.h"
#include <iostream> 


heap::heap(int capacity) : mapping(capacity * 2) {
    currentSize = 0; 
    data.resize(capacity+1);
}


void heap::percolateUp(int posCur) {
    node tmp = data[posCur];
    int parent;

    for (; posCur > 1; posCur = parent) {
        parent = posCur / 2;
        if (tmp.key < data[parent].key) {
            data[posCur] = data[parent];
            mapping.setPointer(data[posCur].id, &data[posCur]); // Update mapping here
        } else {
            break;
        }
    }

    data[posCur] = tmp;
    mapping.setPointer(tmp.id, &data[posCur]); // Update mapping here as well
}


void heap::percolateDown(int posCur) {
    node tmp = data[posCur];
    int child;

    for (; posCur * 2 <= currentSize; posCur = child) {
        child = posCur * 2;
        if (child != currentSize && data[child + 1].key < data[child].key) {
            child++;
        }
        if (data[child].key < tmp.key) {
            data[posCur] = data[child];
            mapping.setPointer(data[posCur].id, &data[posCur]);
        } else {
            break;
        }
    }
    data[posCur] = tmp;
    mapping.setPointer(data[posCur].id, &data[posCur]);
}


int heap::getPos(node *pn) {
    int pos = pn - &data[0];
    return pos;
}


int heap::insert(const std::string &id, int key, void *pv) {
    std::cout << "Insert method called with id: " << id << ", key: " << key << std::endl;
    std::cout << std::boolalpha << mapping.contains(id) << std::endl;

    if (currentSize == data.size() - 1) {
        std::cout << "Heap is full. Unable to insert." << std::endl;
        return 1; // Heap is already filled to capacity
    }

    if (mapping.contains(id)) {
        std::cout << "ID already exists in mapping. Unable to insert." << std::endl;
        return 2; // A node with the given id already exists
    }

    // Insert the new node
    currentSize++;
    data[currentSize].id = id;
    data[currentSize].key = key;
    data[currentSize].pData = pv;

    // Update mapping right after inserting
    mapping.insert(id, &data[currentSize]);

    // Percolate up to maintain heap property
    percolateUp(currentSize);
    heapprint();

    return 0; // Insertion successful
}


int heap::setKey(const std::string &id, int key) {
    bool exist;
    node *pn = static_cast<node *>(mapping.getPointer(id, &exist));
    if (!exist) {
        return 1; // Node with the given ID does not exist
    }
    // origin = oldkey
    //pn = nptr
    int posCur = getPos(pn);
    int oldKey = pn->key;
    pn->key = key;

    // Determine whether to percolate up or down based on the new key
    if (oldKey > key) {
        // New key is smaller, percolate up
        percolateUp(posCur);
    } else if (oldKey < key) {
        // New key is larger, percolate down
        percolateDown(posCur);
    }
    heapprint();
    return 0; // Key updated successfully
}


int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (currentSize == 0) {
        return 1; // Heap is empty
    }

    if (pId) {
        *pId = data[1].id;
    }
    if (pKey) {
        *pKey = data[1].key;
    }
    if (ppData) {
        *(static_cast<void **>(ppData)) = data[1].pData;
    }

    // Move the last node to the root and adjust the heap
    mapping.remove(data[1].id);
    data[1] = data[currentSize--];
    percolateDown(1);
    heapprint();

    return 0; // Deletion successful
}


int heap::remove(const std::string &id, int *pKey, void *ppData) {
    bool exist;
    node *pn = static_cast<node *>(mapping.getPointer(id, &exist));
    if (!exist) {
        return 1; // Node with the given ID does not exist
    }

    int posCur = getPos(pn);
    mapping.remove(pn->id);
    data[0] = data[currentSize];
    data[currentSize] = data[posCur];
    data[posCur] = data[0];
    mapping.setPointer(data[posCur].id, &data[posCur]);

    if (pKey) {
        *pKey = data[currentSize].key;
    }
    if (ppData) {
        *(static_cast<void **>(ppData)) = data[currentSize].pData;
    }

    currentSize--;
    if (data[posCur].key > data[currentSize+1].key) {
        percolateDown(posCur);
    }
    if (data[posCur].key < data[currentSize+1].key) {
        percolateUp(posCur);
    }

    return 0; // Node removal successful
}



void heap::heapprint(){
    int counter = 0;
    int counting = 0;
    int limit = 1;
    std::cout<<std::endl<<std::endl<<std::endl<<"start:"<<std::endl;
    for(auto i :data)
    {
        if(counter>currentSize)
        break;
        
        if (counter)
        {
            //cout<< "Index:"<<counter;
            std::cout<< "\tid:"<<i.id;
            std::cout<< "\tkey:"<<i.key<<"\t";
            counting++;
            if(counting == limit)
            {
                std::cout<<std::endl;
                counting = 0;
                limit *= 2;
            }
        }
        counter++;
    }
}

