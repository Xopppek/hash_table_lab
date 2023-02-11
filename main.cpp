#include <iostream>
#include "HashTable.h"
#include "string"
#include "cassert"

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

template <typename K, typename V, class HashFunction>
bool tablesAreEven(HashTable<K, V, HashFunction> hashTable1, HashTable<K, V, HashFunction> hashTable2){
    auto tableIt1 = hashTable1.begin();
    auto tableIt2 = hashTable2.begin();
    while (tableIt1 != hashTable1.end()){
        auto listIt1 = (*tableIt1).begin();
        auto listIt2 = (*tableIt2).begin();
        while (listIt1 != (*tableIt1).end()){
            if (listIt1->GetKey() != listIt2->GetKey() || listIt1->GetValue() != listIt2->GetValue()) return false;
            listIt1++;
            listIt2++;
        }
        if(listIt2 != (*tableIt2).end()) return false;
        tableIt1++;
        tableIt2++;
    }
    if (tableIt2 != hashTable2.end()) return false;
    return true;
}

int main() {
    HashTable<char, int, f> hashTable(6, 4);

    //=============ADDING ELEMENT=============//
    std::cout<< "ADDING ELEMENTS TESTS" << std::endl;
    hashTable.Add('g', 6);
    assert((hashTable['g'] == 6));
    std::cout << "Checkpoint 1 passed" << std::endl;
    hashTable.Add('T', 1);
    assert((hashTable['T'] == 1));
    std::cout << "Checkpoint 2 passed" << std::endl;
    hashTable.Add('M', 10);
    assert((hashTable['M'] == 10));
    std::cout << "Checkpoint 3 passed" << std::endl;


    std::cout << std::endl;
    //==========REMOVING ELEMENT========//
    std::cout<< "REMOVING ELEMENTS TESTS" << std::endl;
    hashTable.Remove('g');
    assert((!hashTable.IsFound('g')));
    std::cout << "Checkpoint 1 passed" << std::endl;
    hashTable.Remove('T');
    assert((!hashTable.IsFound('T')));
    std::cout << "Checkpoint 2 passed" << std::endl;
    hashTable.Remove('M');
    assert((!hashTable.IsFound('M')));
    std::cout << "Checkpoint 3 passed" << std::endl;

    std::cout << std::endl;

    //=========IS FOUND==========//
    std::cout<< "SEARCHING ELEMENTS TESTS" << std::endl;
    hashTable.Add('k');
    hashTable.Remove('k');
    hashTable.Add('B');

    assert((!hashTable.IsFound('k')));
    std::cout << "Checkpoint 1 passed" << std::endl;
    assert((!hashTable.IsFound('T')));
    std::cout << "Checkpoint 2 passed" << std::endl;
    assert((hashTable.IsFound('B')));
    std::cout << "Checkpoint 3 passed" << std::endl;

    std::cout << std::endl;

    //=======GETTING VALUE========//

    std::cout<< "GETTING VALUE TESTS" << std::endl;
    hashTable.Add('k', 7);
    hashTable.Add('L');
    hashTable.Add('r', 12);

   /* std::cout << hashTable['k'] << std::endl;
    std::cout << hashTable << std::endl;
    hashTable.PrintCash();
    std::cout << std:: endl;
    std::cout << hashTable.GetValue('k') << std::endl;*/

    assert((hashTable.GetValue('k') == 7));
    std::cout << "Checkpoint 1 passed" << std::endl;
    assert((hashTable.GetValue('L') == 0));
    std::cout << "Checkpoint 2 passed" << std::endl;
    assert((hashTable.GetValue('r') == 12));
    std::cout << "Checkpoint 3 passed" << std::endl;


    std::cout << std::endl;
    //=========CASH TEST=========//
    std::cout<< "CASH TESTS" << std::endl;
    hashTable.Add('z', 12);
    hashTable.Add('x', 15);
    hashTable.Add('c', 1);
    hashTable.Add('q', 10);
    hashTable.GetValue('x');

    assert((hashTable.IsInCash('z') == 0));
    std::cout << "Checkpoint 1 passed" << std::endl;
    assert((hashTable.IsInCash('x') == 1));
    std::cout << "Checkpoint 2 passed" << std::endl;

    //hashTable.PrintCash();

    hashTable.GetValue('z');
    hashTable.IsFound('c');
    hashTable.IsFound('g');
    hashTable.IsFound('a');
    assert((hashTable.IsInCash('x') == 0));
    //hashTable.PrintCash();
    std::cout << "Checkpoint 3 passed" << std::endl;




   /* HashTable<char, int, f> hashTable(6, 4);
    hashTable.MakeShort();*/
   /* HashTable<char, int> hashTable1(2);
    std::cout << hashTable1 << std::endl;*/

    /*hashTable.Add('a', 5);
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

    HashTable<char, int, f> hashTable2(6, 4);
    hashTable2.Add('a', 5);
    hashTable2.Add('b', 7);
    hashTable2.Add('a', 8);
    hashTable2.Add('j', 2);
    hashTable2.Add('V', 11);
    hashTable2.Add('T', 4);
    hashTable2.Add('R', 9);
    hashTable2.Add('m', 3);
    hashTable2.Add('q', 17);
    hashTable2.Add('g', 14);
    hashTable2.Add('e', 16);
    hashTable2.Add('o');

    std::cout << tablesAreEven(hashTable, hashTable2) << " equal\n\n";*/
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

    /*std::cout << hashTable << std::endl;

    hashTable.Remove('G');

    std::cout << hashTable << std::endl;

    hashTable.Remove('q');

    std::cout << hashTable << std::endl;
*/

    //std::cout << hashTable.IsFound('j') << " " << hashTable.GetValue('j') << "\n";

   /* std::cout << hashTable.IsFound('j') << "\n";
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

    std::cout << hashTable.GetValue('L') << std::endl;*/
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
