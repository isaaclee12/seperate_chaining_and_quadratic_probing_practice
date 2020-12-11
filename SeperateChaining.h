//
// Created by isaac on 11/19/2019.
//


#ifndef HASHINGB_SEPARATECHAINING_H
#define HASHINGB_SEPARATECHAINING_H

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
class SeparateChaining {
private:
    vector<vector<Object>> table;

    // function to get the string key from an Object
    function<string(const Object &)> getKey;

    unsigned long hornerHash(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % table.size();
    }

    //sdbm taken from https://stackoverflow.com/questions/14409466/simple-hash-functions
    unsigned long sdbmHash(string key) {
        unsigned long hashVal = 0;
        for (char letter : key){
            hashVal = letter + (hashVal << 6) + (hashVal << 16) - hashVal;
        }

        return hashVal % table.size();
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

public:
    // Constructor
    SeparateChaining(unsigned int tableSize, function<string(const Object &)> getKey) {
        table.clear();
        // resizing should create empty vectors at each index
        table.resize(nextPrime(tableSize));
        this->getKey = getKey;
    }

    // insert
    void insert(Object item, int &numReads) {
        // get the key from the item
        string key = getKey(item);
        // hash the key to get the index
        unsigned long index = hornerHash(key);
        // make sure we aren't adding a duplicate to the table
        for (int i = 0; i < table[index].size(); ++i) {
            ++numReads; //Accessing Table Element in the if boolean that follows to check for dupes,, increase # reads
            if (key == getKey(table[index][i])) {
                // found a duplicate
                // cannot insert
                return;
            }
        }
        // add the item to the vector at the index in the table
        table[index].push_back(item);
    }

    //Alt Insert
    void altInsert(Object item, int &numReads) {
        // get the key from the item
        string key = getKey(item);
        // hash the key to get the index
        unsigned long index = sdbmHash(key);
        // make sure we aren't adding a duplicate to the table
        for (int i = 0; i < table[index].size(); ++i) {
            ++numReads; //Accessing Table Element in the if boolean that follows to check for dupes,, increase # reads
            if (key == getKey(table[index][i])) {
                // found a duplicate
                // cannot insert
                return;
            }
        }
        // add the item to the vector at the index in the table
        table[index].push_back(item);
    }

    // find
    optional<Object> find(string key) {
        // hash the key to get the index
        unsigned long index = hornerHash(key);
        // check the vector at the index to find the item
        int i = 0;
        while (i < table[index].size()) {
            string hashKey = getKey(table[index][i]);
            if (hashKey == key) {
                // Found the item
                return table[index][i];
            }
            ++i;
        }
        // Did not find the item
        return nullopt;
    }

    // remove
    optional<Object> remove(string key) {
        // hash the key to get the index
        unsigned long index = hornerHash(key);
        // check the vector at the index to find the item
        int i = 0;
        while (i < table[index].size()) {
            string hashKey = getKey(table[index][i]);
            if (hashKey == key) {
                // Found the item
                Object returnVal = table[index][i];
                // Remove the item from the table
                table[index].erase(table[index].begin() + i);
                return returnVal;
            }
            ++i;
        }
        // Did not find the item
        return nullopt;
    }

    void printTable() {
        for (int i = 0; i < table.size(); ++i) {
            cout << i << ": ";
            for (int j = 0; j < table[i].size(); ++j) {
                cout << table[i][j] << ", ";
            }
            cout << endl;
        }
    }

};

#endif //HASHINGB_SEPARATECHAINING_H
