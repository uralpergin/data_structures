#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    int hash = 0;
    for(int i = 0; i < key.length() ; i++){
        hash += key[i] * PRIME_LIST[i];
    }
    hash = hash % tableSize;
    return hash;
    // TODO
}

void KeyedHashTable::ReHash()
{   
    int old_tablesize = tableSize;
    tableSize = FindNearestLargerPrime(2 * old_tablesize);
    
    HashData* old = new HashData[old_tablesize];
    for(int k = 0; k < old_tablesize; k++){
        old[k].key = table[k].key;
        old[k].intArray = table[k].intArray;
    }
    delete[] table;
    occupiedElementCount = 0;
    table = new HashData[tableSize];
    for(int i = 0; i < tableSize; i++){
        table[i].key = "";
        table[i].intArray.clear(); 
    }
    for(int j = 0; j < old_tablesize; j++){
        if(old[j].key != "" && old[j].key != "_DELETED_"){
           Insert(old[j].key, old[j].intArray);
        }    
    }
    delete[] old;
    // TODO
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    for(int i = 0; i < PRIME_TABLE_COUNT-1; i++){
        if(requestedCapacity < 2) return 2;
        else if(requestedCapacity >= PRIME_LIST[i] && requestedCapacity < PRIME_LIST[i+1]) return PRIME_LIST[i+1];
    }
    // TODO
}

KeyedHashTable::KeyedHashTable()
{
    table = new HashData[2];
    tableSize = 2;
    occupiedElementCount = 0;
    std::vector<int> newArray;
    for(int i = 0; i < 2; i++){
        table[i].key = "";
        table[i].intArray = newArray;
    }
    
    // TODO
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    int size = FindNearestLargerPrime(requestedCapacity);
    table = new HashData[size];
    tableSize = size;
    occupiedElementCount = 0;
    std::vector<int> newArray;
    for(int i = 0; i < tableSize; i++){
        table[i].key = "";
        table[i].intArray = newArray;   
    }
    // TODO
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{   this-> table = NULL;
    *this = other;
    
    // TODO
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{   
    delete[] table;
    table = new HashData[other.tableSize];
    tableSize = other.tableSize;
    occupiedElementCount = other.occupiedElementCount;
    for(int i = 0; i < other.tableSize; i++){
        table[i].key = (other.table)[i].key;
        table[i].intArray = (other.table)[i].intArray;
    }
    return *this;
    // TODO
}

KeyedHashTable::~KeyedHashTable()
{
    ClearTable();
    delete[] table;
    // TODO
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    int code = Hash(key);
    int i = 1;
    while(table[code].key != "" && table[code].key != "_DELETED_"){
        code =  (code + i) % tableSize;
        i+=2;
    }
    if(table[code].key != key){
        table[code].key = key;
        table[code].intArray = intArray;
        occupiedElementCount++;
        int element = occupiedElementCount;
        if((occupiedElementCount * EXPAND_THRESHOLD) >= tableSize) ReHash();
        occupiedElementCount = element;
        return true;
    }
    return false;
    // TODO
}

bool KeyedHashTable::Remove(const std::string& key)
{
    for(int i = 0; i < tableSize; i++){
        if(table[i].key == key){
            table[i].key = "_DELETED_";
            std::vector<int> newArray;
            table[i].intArray = newArray;
            return true;
        }
    }
    return false;
    // TODO
}

void KeyedHashTable::ClearTable()
{
    std::vector<int> empty;
    for(int i = 0; i < tableSize; i++){
        table[i].key = "";
        table[i].intArray = empty;    
    }
    occupiedElementCount=0;
   // TODO
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{   
    
    int code = Hash(key);
    int i = 1;
    while(table[code].key != "" && table[code].key != "_DELETED_"){
        if(table[code].key == key){
            valueOut = table[code].intArray;
            return true;
        }
        code = (code + i) % tableSize;
        i+=2;
    }
    return false;
    // TODO
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}