
#include "hash.h"
#include <iostream>
using namespace std;
int primeNo[] = {11, 100003, 200003, 400009, 800011, 1600033, 3200003, 6400013};

// Creates the hash table vector with null data
hashTable::hashTable(int size)
{
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }
}
// Hashing Function: (Source: http://www.cse.yorku.ca/~oz/hash.html)
// Uses SDBM for hashing due to its low rate of collision
int hashTable::hash(const string &key)
{
    unsigned int hash = 0;
    unsigned int i = 0;
    unsigned int len = key.length();

    for (i = 0; i < len; i++)
    {
        hash = (key[i]) + (hash << 6) + (hash << 16) - hash;
    }
    return hash % capacity;
}

// Insert function into the hash table. Checks to see if hashTable size is too small, if so invokes
// rehash function. This function is responsible for getting hask key from hash() and inputing the data into appropriate slot
// using linear probing for collision aversion
int hashTable::insert(const string &key, void *pv)
{
    int check;
    if ((filled * 2) >= capacity)
        check = rehash();

    if (check == 2)
    {
        return 2;
    }

    int pos = hash(key);
    if (contains(key) == true)
    {
        return 1;
    }

    while (data[pos].isOccupied == true && data[pos].isDeleted == false)
    {
        pos++;
        if (pos == capacity)
            pos = 0;
    }
    filled++;
    data[pos].key = key;
    data[pos].isOccupied = true;
    data[pos].isDeleted = false;
    data[pos].pv = pv;
    return 0;
}
// Rehash function is responsible for copying old data into a temportary hash table, expand and reset the data table,
// and finally re-enter the old values into the new table
bool hashTable::rehash()
{
    vector<hashItem> oldData = data;
    int newSize = getPrime(capacity);
    try
    {
        data.resize(newSize);
    }
    catch (const bad_alloc)
    {
        return 2;
    }
    filled = 0;
    capacity = newSize;
    for (int i = 0; i < data.size(); i++)
    {
        data[i].key = "";
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }

    for (int i = 0; i < oldData.size(); i++)
    {
        hashItem oldPoint = oldData[i];
        if (oldPoint.isOccupied && !oldPoint.isDeleted)
        {
            insert(oldPoint.key, oldPoint.pv);
        }
    }
    return 1;
}
// Finds the position of a specified value by hashing the value and searching for the position
int hashTable::findPos(const std::string &key)
{
    int pos = hash(key);
    while (data[pos].isOccupied)
    {
        if (data[pos].key == key && data[pos].isDeleted == false)
        {
            return pos;
        }
        else
        {
            pos++;
            if (pos == capacity)
                pos = 0;
        }
    }
    return -1;
}

//  Generates a prime twice as large as specified hashtable size
unsigned int hashTable::getPrime(int size)
{
    unsigned int prime;
    for (int i = 0; i < sizeof(primeNo) / sizeof(int); i++)
    {
        if (primeNo[i] >= (size * 2))
        {
            prime = primeNo[i];
            break;
        }
    }
    return prime;
}

// Checks to see if a specified value exists withing the hash table
bool hashTable::contains(const std::string &key)
{

    if (findPos(key) < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Finds the position of a hashItem by its key, if the position does exist.
// if the position exists, the function returns the item's pv, else it returns NULL
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

// Finds position of a hashItem (by its key) if the position exists.
//If it does exist, the function returns 0 and sets the hashItem's pv, else it returns 1.
int hashTable::setPointer(const std::string &key, void *pv)
{
    int pos;
    if ((pos = findPos(key)) >= 0)
    {
        data[pos].pv = pv;
        return 0;
    }
    return 1;
}

// Lazily deletes by setting a hashItem's isDeleted value to be true.
bool hashTable::remove(const std::string &key)
{
    int pos;
    if ((pos = findPos(key)) >= 0)
    {
        data[pos].isDeleted = true;
        return true;
    }
    return false;
}