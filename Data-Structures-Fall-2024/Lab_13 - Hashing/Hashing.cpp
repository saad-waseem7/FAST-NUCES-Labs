#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class V>
class HashItem
{
public:
    int key;
    V value;
    short status; // 0: empty, 1: deleted, 2: occupied

    HashItem() : key(0), value(V()), status(0) {}
};

template <class V>
class HashMap
{
protected:
    HashItem<V> *hashArray;
    int capacity;
    int currentElements;

    float loadFactor() const
    {
        return static_cast<float>(currentElements) / capacity;
    }

    void doubleCapacity()
    {
        int oldCapacity = capacity;
        capacity *= 2;

        HashItem<V> *oldArray = hashArray;
        hashArray = new HashItem<V>[capacity];

        currentElements = 0;

        for (int i = 0; i < oldCapacity; i++)
        {
            if (oldArray[i].status == 2)
            {
                insert(oldArray[i].key, oldArray[i].value);
            }
        }

        delete[] oldArray;
    }

    // Virtual method for probing (linear probing by default)
    virtual int getNextCandidateIndex(int key, int i) const
    {
        return (key + i) % capacity;
    }

public:
    HashMap() : capacity(10), currentElements(0)
    {
        hashArray = new HashItem<V>[capacity];
    }

    HashMap(int const capacity) : capacity(capacity), currentElements(0)
    {
        if (capacity < 1)
        {
            cout << "Error: Capacity must be greater than 0!" << endl;
            exit(1);
        }
        hashArray = new HashItem<V>[capacity];
    }

    void insert(int const key, V const value)
    {
        if (loadFactor() >= 0.75)
        {
            doubleCapacity();
        }

        int index = key % capacity;
        int i = 0;

        while (hashArray[index].status == 2 && hashArray[index].key != key)
        {
            index = getNextCandidateIndex(key, ++i);
        }

        if (hashArray[index].status != 2)
        {
            currentElements++;
        }

        hashArray[index].key = key;
        hashArray[index].value = value;
        hashArray[index].status = 2;
    }

    bool deleteKey(int const key)
    {
        int index = key % capacity;
        int i = 0;

        while (hashArray[index].status != 0)
        {
            if (hashArray[index].status == 2 && hashArray[index].key == key)
            {
                hashArray[index].status = 1;
                currentElements--;
                return true;
            }
            index = getNextCandidateIndex(key, ++i);
        }
        return false;
    }

    V *get(int const key) const
    {
        int index = key % capacity;
        int i = 0;

        while (hashArray[index].status != 0)
        {
            if (hashArray[index].status == 2 && hashArray[index].key == key)
            {
                return &(hashArray[index].value);
            }
            index = getNextCandidateIndex(key, ++i);
        }
        return nullptr;
    }

    virtual ~HashMap()
    {
        delete[] hashArray;
    }
};

// Quadratic Probing HashMap
template <class V>
class QHashMap : public HashMap<V>
{
protected:
    int getNextCandidateIndex(int key, int i) const override
    {
        return (key + i * i) % this->capacity;
    }
};

// Double Hashing HashMap
template <class V>
class DHashMap : public HashMap<V>
{
private:
    const int PRIME = 7; // Any prime number for double hashing

protected:
    int getNextCandidateIndex(int key, int i) const override
    {
        int firstValue = key % this->capacity;
        int secondValue = (PRIME - (key % PRIME));
        return (firstValue + i * secondValue) % this->capacity;
    }
};

void populateHash(string filename, HashMap<string> *hash)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    int id;
    string name;

    while (file >> id >> name)
    {
        hash->insert(id, name);
    }
    file.close();
}

// Main program
int main()
{
    HashMap<string> *map;

    // Linear Probing
    map = new HashMap<string>;
    populateHash("Students.txt", map);
    if (map->get(9))
    {
        cout << *map->get(9) << endl;
    }
    map->deleteKey(9);
    if (!map->get(9))
    {
        cout << "Key 9 deleted successfully!" << endl;
    }
    delete map;

    // Quadratic Probing
    map = new QHashMap<string>;
    populateHash("Students.txt", map);
    if (map->get(98))
    {
        cout << *map->get(98) << endl;
    }
    map->deleteKey(98);
    if (!map->get(98))
    {
        cout << "Key 98 deleted successfully!" << endl;
    }
    delete map;

    // Double Hashing
    map = new DHashMap<string>;
    populateHash("Students.txt", map);
    if (map->get(101))
    {
        cout << *map->get(101) << endl;
    }
    map->deleteKey(101);
    if (!map->get(101))
    {
        cout << "Key 101 deleted successfully!" << endl;
    }
    delete map;

    return 0;
}
