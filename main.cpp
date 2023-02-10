#include <iostream>
#include "HashTable.h"

struct f{
    int operator() (const char& key) const{
        int hash = (int) key - 93;
        if (hash < 0) hash*=(-1);
        return hash;
    }
};


int main() {
    HashTable<char, int> hashTable;

    hashTable.Add('a', 5);
    hashTable.Add('b', 7);
    hashTable.Add('a', 8);
    hashTable.Add('j', 2);
    hashTable.Add('V', 1);
    hashTable.Add('T', 4);
    hashTable.Add('T', 9);
    hashTable.Print();

    hashTable.Remove('j');
    hashTable.Print();
    return 0;
}
