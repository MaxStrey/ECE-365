#include "hash.h"  
#include <cmath>
#include <iostream> 


// Constructor implementation
hashTable::hashTable(int size) {
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
}




// The hash function.
int hashTable::hash(const std::string &key) {
    unsigned int hashVal = 0;
    for(char ch : key) {
        hashVal = 37 * hashVal + ch;
    }
    int index = hashVal % capacity;
    return index; // Modulo operation to fit into table size}
}



int hashTable::insert(const std::string &key, void *pv) {

    // Step 1: Check for rehashing
    if (filled >= capacity / 2) {
        std::cout << "Table more than half full, attempting to rehash." << std::endl;
        if (!rehash()) {
            std::cout << "Rehashing failed." << std::endl;
            return 2; // Rehash failed
        }
    }

    // Step 2: Calculate the hash value for the given key
    int pos = hash(key);

    // Step 3: Probe for the next open slot or check for duplicate
    while (data[pos].isOccupied && !data[pos].isDeleted) {
        if (data[pos].key == key) {
            std::cout << "Duplicate key found at position: " << pos << std::endl;
            return 1; // Duplicate key
        }
        pos = (pos + 1) % capacity; // Linear probing
        std::cout << "Position occupied, probing next position: " << pos << std::endl;
    }

    // Step 4: Insert the new key
    data[pos].key = key;
    data[pos].isOccupied = true;
    data[pos].isDeleted = false;
    data[pos].pv = pv;
    ++filled;


    return 0; // Insertion successful
}


int hashTable::findPos(const std::string &key) {
    int pos = hash(key);  // Start with the hash value as the initial position
    while (data[pos].isOccupied) {  // Loop until an unoccupied slot is found

        if (data[pos].key == key && !data[pos].isDeleted) {

            return pos;  // Key found, return position

        }
        pos = (pos + 1) % capacity;  // Probe to the next slot
    }
    return -1;  // Key not found
}


bool hashTable::contains(const std::string &key) {
    return findPos(key) != -1;
}


bool hashTable::rehash() {
    // Store old data
    std::vector<hashItem> oldData = data;

    // Double the capacity and find the next prime number
    capacity = getPrime(2 * capacity);
    std::cout << "Rehashing... New capacity: " << capacity << std::endl;

    // Clear the old data and resize
    data.clear();
    data.resize(capacity);

    // Reset filled count
    filled = 0;

    // Re-insert old data into new table
    for (const auto &item : oldData) {
        if (item.isOccupied && !item.isDeleted) {
            insert(item.key, item.pv);
        }
    }

    return true;
}


unsigned int hashTable::getPrime(int size) {
    if (size < 2) {
        return 2; // Smallest prime number
    }
    for (int i = size; ; ++i) {
        bool isPrime = true;
        for (int j = 2; j <= static_cast<int>(std::sqrt(i)); ++j) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            return i;
        }
    }
}


// void * hashTable::getPointer(const std::string &key, bool *b ){
//     if (b == nullptr) {
//         return nullptr;
//     }
    
//     int pos = findPos(key);
//     *b = false;
//     if (pos == -1){
//         return nullptr;
//     }
//     *b = true;
    
//     return data[pos].pv;
// }

void *hashTable::getPointer(const std::string &key, bool *b)
{
    int pos;
    if ((pos = findPos(key)) >= 0)
    {
        if (b != NULL)
        {
            *b = true;
        }
        return data[pos].pv;
    }
    if (b != NULL)
    {
        *b = false;
    }
    return NULL;
}






int hashTable::setPointer(const std::string &key, void *pv) {
    int pos = findPos(key);
    if (pos != -1) {
        data[pos].pv = pv;
        return 0;
    } else {
        return 1;
    }
}

bool hashTable::remove(const std::string &key) {
    int pos = findPos(key);
    if (pos != -1) {
        data[pos].isDeleted = true;
        --filled;  // Reduce the filled count as an item is removed
        return true;
    } else {
        return false;
    }
}





