//
// Created by isaac on 11/19/2019.
//

#ifndef HASHINGA_PROBING_H
#define HASHINGA_PROBING_H


// If this produces errors, go into CMakeLists.txt and change the 14 to 17.
#if __cplusplus < 17
#include <experimental/optional>
using std::experimental::optional;
using std::experimental::nullopt;
using std::experimental::make_optional;
#else
#include <optional>
using std::optional;
using std::nullopt;
using std::make_optional;
#endif

#include <iostream>
#include <functional>
#include <string>
#include <vector>
using std::vector;
using std::function;
using std::string;
using std::cout;
using std::endl;

template<typename Object>
class Probing {
private:
    enum state {empty, filled, removed};
    struct hashItem {
        Object item;
        state status;
    };
    vector<hashItem> hashTable;
    int numItems;

    // the function to get the string key from an Object
    function<string(const Object &)> getKey;

    // hashing function
    unsigned long hornerHash(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % hashTable.size();
    }

    //sdbm taken from https://stackoverflow.com/questions/14409466/simple-hash-functions
    unsigned long sdbmHash(string key) {
        unsigned long hashVal = 0;
        for (char letter : key){
            hashVal = letter + (hashVal << 6) + (hashVal << 16) - hashVal;
        }

        return hashVal % hashTable.size();
    }

    // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

    void rehash(int &numReads) {
        // copy the hash table
        vector<hashItem> oldTable = hashTable;
        // empty and resize table
        int oldSize = hashTable.size();
        hashTable.clear();
        hashTable.resize(nextPrime(oldSize * 2));
        // default everything to empty
        for (int i = 0; i < hashTable.size(); ++i) {
            hashTable[i].status = empty;
        }
        // reset numItems
        numItems = 0;
        // reinsert the filled indices from the old table
        for (hashItem &h : oldTable) {
            if (h.status == filled) {
                insert(h.item,numReads);
            }
        }
    }


public:
    // Constructor
    Probing(unsigned int tableSize, function<string(const Object &)> getKey) {
        hashTable.clear();
        hashTable.resize(nextPrime(tableSize));
        // Set hash table with default null values
        for (int i = 0; i < hashTable.size(); ++i) {
            hashTable[i].status = empty;
            hashTable[i].item = Object();
        }
        this->getKey = getKey;
        numItems = 0;
    }

    // insert
    void insert(Object item, int &numReads) {
        // get the key from the item
        string key = getKey(item);
        // hash the key to get an index
        unsigned long index = hornerHash(key);
        // probe until we find a spot where we can insert
        //Quadratic base iterator
        int base = 2;
        while (hashTable[index].status == filled && key != getKey(hashTable[index].item)) {
            ++++numReads; //Accessing Hash Element every time hasTable[index] happens!
            index = (index + (int)(pow(base,2)) ) % hashTable.size();
            ++base;
        }
        //Reset base
        base = 2;
        if (hashTable[index].status != filled) {
            ++numReads; //Accessing Hash Element every time hasTable[index] happens!
            hashTable[index].item = item;
            if (hashTable[index].status == empty) {
                ++numReads; //Accessing Hash Element every time hasTable[index] happens!
                ++numItems;
            }
            hashTable[index].status = filled;

            if (numItems > hashTable.size() / 2) {
                rehash(numReads);
            }
        }
    }

    // Alt insert
    void altInsert(Object item, int &numReads) {
        // get the key from the item
        string key = getKey(item);
        // hash the key to get an index
        unsigned long index = sdbmHash(key);
        // probe until we find a spot where we can insert
        //Quadratic base iterator
        int base = 2;
        while (hashTable[index].status == filled && key != getKey(hashTable[index].item)) {
            ++++numReads; //Accessing Hash Element every time hasTable[index] happens!
            index = (index + (int)(pow(base,2)) ) % hashTable.size();
            ++base;
        }
        //Reset base
        base = 2;
        if (hashTable[index].status != filled) {
            ++numReads; //Accessing Hash Element every time hasTable[index] happens!
            hashTable[index].item = item;
            if (hashTable[index].status == empty) {
                ++numReads; //Accessing Hash Element every time hasTable[index] happens!
                ++numItems;
            }
            hashTable[index].status = filled;

            if (numItems > hashTable.size() / 2) {
                rehash(numReads);
            }
        }
    }


    // find
    optional<Object> find(string key) {
        // hash the key to get an index
        unsigned long index = hornerHash(key);
        while (hashTable[index].status != empty) {
            if (hashTable[index].status == filled) {
                // check to see if it is a match
                if (key == getKey(hashTable[index].item)) {
                    // we found the item
                    return hashTable[index].item;
                }
            }
            index = (index + 1) % hashTable.size();
        }
        // Did not find the item
        return nullopt;
    }

    // remove
    optional<Object> remove(string key) {
        // hash the key to get an index
        unsigned long index = hornerHash(key);
        while (hashTable[index].status != empty) {
            if (hashTable[index].status == filled) {
                // check to see if it is a match
                if (key == getKey(hashTable[index].item)) {
                    // we found the item
                    // remove it
                    hashTable[index].status = removed;
                    return hashTable[index].item;
                }
            }
            index = (index + 1) % hashTable.size();
        }
        // Did not find the item
        return nullopt;
    }

    void printTable() const {
        for (int i = 0; i < hashTable.size(); ++i) {
            cout << i << ": ";
            if (hashTable[i].status == filled) {
                cout << hashTable[i].item;
            }
            cout << endl;
        }
    }
};

#endif //HASHINGA_PROBING_H
