#ifndef HASH_TABLE_LAB_HASHTABLE_H
#define HASH_TABLE_LAB_HASHTABLE_H
#include "vector"
#include "list"

struct HashFunc1{
    int operator() (const char& key) const{
        int hash = (int) key - 96;
        if (hash < 0) hash*=(-1);
        return hash;
    }
};

template <typename K, typename V, class HashFunction = HashFunc1>
class HashTable{
private:
    class Element{ // (key, value) pair
    private:
        K _key;
        V _value;
    public:
        Element(){_key = 0; _value = 0;}
        Element(const K& key, const V& value){_key = key; _value = value;}
        V GetValue() const {return _value;}
        K GetKey() const {return _key;}
    };

    int _size = 10;
    int _maxSize = 1000;

    std::vector<std::list<Element>> _table;
    // creating array of lists of elements (in collision case, we put new element in the end of list)

    bool Resize(int size){
        if (size < _maxSize) {
            _table.resize(size);
            _size = size;
            //std::cout << "resized to " << _size << "\n";
            return 1;
        }
        return 0;
    }

public:

    HashTable(){
        _table = std::vector<std::list<Element>>();
        _table.resize(_size);
    }
    ~HashTable() = default;

    //add returns 0 if element is new and added successfully, 1 if element with that key already is in table
    //2 if key is invalid (hash > max_size)
    short Add(const K& key, const V& value, const HashFunction& hashFunction = HashFunction()){
        int hash = hashFunction(key);
        if (hash >= _size)
            if (!Resize(hash + 1)) return 2;
        auto tableIter = _table.begin();
        tableIter += hash;
        for (auto listIter = (*tableIter).begin(); listIter != (*tableIter).end(); listIter++){
            if ((*listIter).GetKey() == key)
                return 1;
        }
        Element newElement = Element(key, value);
        (*tableIter).push_back(newElement);
        return 0;
    }

    //add returns 0 if element was in table and deleted successfully, 1 if there wasn't any elements with this key
    //2 if key is invalid (hash > max_size)
    short Remove(const K& key, const HashFunction& hashFunction = HashFunction()){
        int hash = hashFunction(key);
        if (hash >= _size) return 2;
        auto tableIter = _table.begin();
        tableIter += hash;
        for (auto listIter = (*tableIter).begin(); listIter != (*tableIter).end(); listIter++){
            if ((*listIter).GetKey() == key) {
                (*tableIter).erase(listIter);
                return 0;
            }
        }
        return 1;
    }

    //forbidden function ^_^
   /* void Print(){
        int t = 0;
        for (auto it = _table.begin(); it != _table.end(); it++){
            std::cout << t++ << ": ";
            for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
                std::cout << (*it2).GetKey() << "-" << (*it2).GetValue() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }*/

    auto begin() const {return _table.begin();}
    auto end() const {return _table.end();}

};



template <typename K, typename V, class HashFunction>
std::ostream& operator<<(std::ostream &os, const HashTable<K, V, HashFunction> &table) {
    int t = 0;
    for (auto it = table.begin(); it != table.end(); it++){
        os << t++ << ": ";
        for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++){
            os << (*it2).GetKey() << "-" << (*it2).GetValue() << " ";
        }
        os << "\n";
    }
    return os;
}

#endif //HASH_TABLE_LAB_HASHTABLE_H
