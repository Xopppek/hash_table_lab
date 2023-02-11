#include <iostream>
#include "HashTable.h"
#include "string"

struct f{
    int operator() (const char& key) const{
        int hash = (int) key - 93;
        hash = hash*hash/100;
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
    HashTable<char, int, f> hashTable(6, 4);
    hashTable.DontMakeShort();
    hashTable.MakeShort();
   /* HashTable<char, int> hashTable1(2);
    std::cout << hashTable1 << std::endl;*/

    hashTable.Add('a', 5);
    hashTable.Add('b', 7);
    hashTable.Add('a', 8);
    hashTable.Add('j', 2);
    hashTable.Add('V', 11);
    hashTable.Add('T', 4);
    hashTable.Add('R', 9);
    hashTable.Add('m', 3);
    hashTable.Add('q', 17);
    hashTable.Add('g', 14);
    hashTable.Add('G', 16);
    hashTable.Add('o');
    //hashTable.Add('y', 10);



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

    std::cout << hashTable << std::endl;

    hashTable.Remove('G');

    std::cout << hashTable << std::endl;

    hashTable.Remove('q');

    std::cout << hashTable << std::endl;


    //std::cout << hashTable.IsFound('j') << " " << hashTable.GetValue('j') << "\n";

    std::cout << hashTable.IsFound('j') << "\n";
    std::cout << hashTable.IsFound('r') << "\n\n";


    hashTable.PrintCash();

    std::cout << std::endl;

    hashTable.Remove('j');
    hashTable.Add('r', 6);


    std::cout << hashTable << std::endl;

    hashTable.PrintCash();

    hashTable.IsFound('N');

    hashTable.PrintCash();
    hashTable.IsFound('y');
    hashTable.PrintCash();




    std::cout << hashTable['L'] << std::endl;


    std::cout << hashTable << std::endl;

    std::cout << hashTable['L'] << std::endl;

    int a = hashTable['L'];
    std::cout << a << " a " << std:: endl;
    hashTable['L'] = 100;
    std::cout << hashTable['L'] << std::endl;


/*
    std::cout << hashTable['o'] << std::endl;

    std::cout << hashTable << std::endl;

    hashTable['r'] = 10;
    std::cout << hashTable['r'] << std::endl;*/

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
