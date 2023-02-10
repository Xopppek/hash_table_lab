#include <iostream>
#include "HashTable.h"
#include "string"

struct f{
    int operator() (const char& key) const{
        int hash = (int) key - 93;
        if (hash < 0) hash*=(-1);
        return hash;
    }
};

struct g{
    int operator() (const std::string& key) const{
        int hash = key.size();
        return hash;
    }
};

int main() {
    HashTable<char, int> hashTable;

    hashTable.Add('a', 5);
    hashTable.Add('b', 7);
    hashTable.Add('a', 8);
    hashTable.Add('j', 2);
    hashTable.Add('V', 11);
    hashTable.Add('T', 4);
    hashTable.Add('T', 9);



   /* auto it = hashTable.begin();
    while(it != hashTable.end()){
        auto it2 = (*it).begin();

        while (it2 != (*it).end()){
            //std::cout << (*it2).GetKey() << "-" << (*it2).GetValue() << " ";
            int* x = &((*it2).GetValue());
            *x = 15;
            it2++;
        }
        std::cout << std::endl;
        it++;
    }*/

    std::cout << hashTable;

    std::cout << hashTable.IsFound('j') << " " << hashTable.GetValue('j') << "\n";
//    int* x = &(hashTable.Find('V'));
//    *x = 15;

    //std::cout << hashTable.IsFound('V') << " " << hashTable.Find('V');

    //hashTable.Remove('j');

   /* hashTable.Add("a", 7);
    hashTable.Add("a", 9);
    hashTable.Add("b", 8);
    hashTable.Add("ant", 8);
    hashTable.Add("am", 2);
    hashTable.Print();

    hashTable.Remove("a");*/

    return 0;
}
