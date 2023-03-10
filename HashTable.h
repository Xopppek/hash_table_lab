#ifndef HASH_TABLE_LAB_HASHTABLE_H
#define HASH_TABLE_LAB_HASHTABLE_H
#include "vector"
#include "list"
#include "algorithm"

struct HashFunc1{
    int operator() (const char& key) const{
        int hash = (int) key - 96;
        if (hash < 0) hash*=(-1);
        return hash;
    }
};

template <typename K, typename V>
class Cash{
private:
    class CashElement{
    private:
        K _key;
        bool _isInTable;
        V _value;
    public:
        CashElement(K key, bool isInTable, V value = V()) : _key(key), _value(value), _isInTable(isInTable) {};
        K GetKey() const {return _key;}
        V GetValue() const {return _value;}
        bool IsInTable() const {return _isInTable;}
        void Remove(){_isInTable = 0;}
        void Add(const V& value){_isInTable = 1; _value = value;}
    };
    size_t _capacity;
    size_t _size = 0;
    std::list<CashElement> CashElements;
public:
    Cash(size_t capacity = 3){CashElements = std::list<CashElement>(); _capacity = capacity;}
    ~Cash() = default;
    void Set(const K& key, const bool& isInTable, const V& value = V()){
        CashElement newCashElement = CashElement(key, isInTable, value);
        if (_size == _capacity)
            CashElements.pop_front();
        else
            _size++;
        CashElements.push_back(newCashElement);
    }
    //returns 0 if not in table, 1 if is in table, 2 if is not in cash
    short GetStatus(const K& key) const{
        for (auto iter = CashElements.begin(); iter != CashElements.end(); iter++){
            if ((*iter).GetKey() == key)
                return (*iter).IsInTable();
        }
        return 2;
    }

    V GetValue(const K& key) const {
        for (auto iter = CashElements.begin(); iter != CashElements.end(); iter++) {
            if ((*iter).GetKey() == key)
                return (*iter).GetValue();
        }
        throw "no element in cash";
    }

    bool IsInCash(const K& key) const{
        for (auto iter = CashElements.begin(); iter != CashElements.end(); iter++){
            if ((*iter).GetKey() == key)
                return true;
        }
        return false;
    }

    void Add(const K& key, const V& value){
        for (auto iter = CashElements.begin(); iter != CashElements.end(); iter++){
            if ((*iter).GetKey() == key)
                (*iter).Add(value);
        }
    }

    void Remove(const K& key){
        for (auto iter = CashElements.begin(); iter != CashElements.end(); iter++){
            if ((*iter).GetKey() == key)
                (*iter).Remove();
        }
    }

    auto begin() const {return CashElements.begin();}
    auto end() const {return CashElements.end();}
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
        V& GetValue() {return _value;}
    };



    size_t _size = 0;
    size_t _maxSize = 1000;
    bool wantedToBeShort = true;

    Cash<K, V> cash;

    std::vector<std::list<Element>> _table;
    // creating array of lists of elements (in collision case, we put new element in the end of list)

    bool Resize(int size){
        if (size < _maxSize && size >= 0) {
            _table.resize(size);
            _size = size;
            //std::cout << "resized to " << _size << "\n";
            return true;
        }
        return false;
    }

    V& GetRawValue(const K& key, const HashFunction& hashFunction = HashFunction()){
        if (cash.GetStatus(key) == 0) throw "no element";
        int hash = hashFunction(key);
        if (hash >= _size || hash < 0) throw "invalid key";
        auto tableIter = _table.begin();
        tableIter += hash;
        for (auto listIter = (*tableIter).begin(); listIter != (*tableIter).end(); listIter++){
            if ((*listIter).GetKey() == key) {
                return (*listIter).GetValue();
            }
        }
        throw "no element";
    }



public:

    HashTable(){
        _table = std::vector<std::list<Element>>();
        _table.resize(_size);
        cash = Cash<K, V>();
    }
    HashTable(size_t size){
        _table = std::vector<std::list<Element>>();
        _size = size;
        _table.resize(_size);
        cash = Cash<K, V>();
    }
    HashTable(size_t size, size_t cashSize){
        _table = std::vector<std::list<Element>>();
        _size = size;
        _table.resize(_size);
        cash = Cash<K, V>(cashSize);
    }
    ~HashTable() = default;

    //add returns 0 if element is new and added successfully, 1 if element with that key already is in table
    //2 if key is invalid (hash > max_size or hash < 0)
    short Add(const K& key, const V& value = V(), const HashFunction& hashFunction = HashFunction()){
        int hash = hashFunction(key);
        if (hash < 0) return 2;
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
        if (cash.IsInCash(key)) cash.Add(key, value);
        return 0;
    }

    void CleanTail(){
        while((_table.end()-1)->empty()) {
            _table.pop_back();
            _size--;
        }
    }

    //add returns 0 if element was in table and deleted successfully, 1 if there wasn't any elements with this key
    //2 if key is invalid (hash > max_size or hash < 0)
    short Remove(const K& key, const HashFunction& hashFunction = HashFunction()){
        if (cash.GetStatus(key) == 0) return 1;

        int hash = hashFunction(key);
        if (hash >= _size || hash < 0) return 2;
        auto tableIter = _table.begin();
        tableIter += hash;
        for (auto listIter = (*tableIter).begin(); listIter != (*tableIter).end(); listIter++){
            if ((*listIter).GetKey() == key) {
                (*tableIter).erase(listIter);
                if (cash.IsInCash(key)) cash.Remove(key);
                if (wantedToBeShort) CleanTail();
                return 0;
            }
        }
        return 1;
    }

    void MakeShort(){wantedToBeShort = true;}

    void DontMakeShort(){wantedToBeShort = false;}


    bool IsFound(const K& key, const HashFunction& hashFunction = HashFunction()){
        short status = cash.GetStatus(key);
        if(status == 1) return true;
        else if (status == 0) return false;

        int hash = hashFunction(key);
        if (hash >= _size || hash < 0) {cash.Set(key, false); return false;}
        auto tableIter = _table.begin();
        tableIter += hash;
        for (auto listIter = (*tableIter).begin(); listIter != (*tableIter).end(); listIter++){
            if ((*listIter).GetKey() == key) {
                cash.Set(key, true, (*listIter).GetValue());
                return true;
            }
        }
        cash.Set(key, false);
        return false;
    }

    V GetValue(const K& key, const HashFunction& hashFunction = HashFunction()){
        if (cash.GetStatus(key) == 0) throw "no element";
        int hash = hashFunction(key);
        if (hash >= _size || hash < 0) throw "invalid key";

        if (cash.IsInCash(key)) return cash.GetValue(key);

        auto tableIter = _table.begin();
        tableIter += hash;
        for (auto listIter = (*tableIter).begin(); listIter != (*tableIter).end(); listIter++){
            if ((*listIter).GetKey() == key) {
                cash.Set(key, true, (*listIter).GetValue());
                return (*listIter).GetValue();
            }
        }
        cash.Set(key, false);
        throw "no element";
    }

    //use it only if IsFound


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

   void PrintCash(){
       auto it = cash.begin();
       while (it != cash.end()){
           std::cout << (*it).GetKey() << "-" << (*it).IsInTable() << "-" << (*it).GetValue() << " ";
           it++;
       }
       std::cout << std::endl;
   }


   V& operator[] (const K& key){
       HashFunction hashFunction;
       int hash = hashFunction(key);
       if (hash < 0) throw "incorrect key";
       if (hash >= _size) {
           Add(key, V());
           return (_table[hash].begin()->GetValue());
       }
       auto keyIsEven = [&key](const Element& element){ return (key == element.GetKey()); };

       auto result = std::find_if(_table[hash].begin(), _table[hash].end(), keyIsEven);

       if(result == _table[hash].end()) {
           Add(key, V());
       }
       return (GetRawValue(key));
   }

   bool IsInCash(const K& key){
       return cash.IsInCash(key);
   }

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
