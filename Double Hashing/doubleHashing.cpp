#include <iostream>
#include <vector>
using namespace std;

class HashTable
{
private:
    static const int TABLE_SIZE = 20;

    struct KeyValue
    {
        int key;
        int value;
        bool isEmpty;

        KeyValue() : key(0), value(0), isEmpty(true) {}
        KeyValue(int k, int v, bool empty) : key(k), value(v), isEmpty(empty) {}

        bool operator==(const KeyValue &other) const
        {
            return key == other.key && value == other.value && isEmpty == other.isEmpty;
        }
    };

    vector<KeyValue> table;

    int hashFunction1(int key)
    {
        return key % TABLE_SIZE;
    }

    int hashFunction2(int key)
    {
        return 1 + (key % 5);
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    ~HashTable() {}

    void insert(int key, int value)
    {
        int index = hashFunction1(key);
        int step = hashFunction2(key);

        int i = 0;
        while (i < TABLE_SIZE)
        {
            if (table[index].isEmpty)
            {
                table[index].key = key;
                table[index].value = value;
                table[index].isEmpty = false;
                return;
            }
            index = (index + step) % TABLE_SIZE;
            i++;
        }

        cout << "Error: Hash Table Full." << endl;
    }

    int search(int key)
    {
        int index = hashFunction1(key);
        int step = hashFunction2(key);

        int i = 0;
        while (i < TABLE_SIZE)
        {
            if (!table[index].isEmpty && table[index].key == key)
            {
                return table[index].value;
            }
            index = (index + step) % TABLE_SIZE;
            i++;
        }
        return -1;
    }

    void remove(int key)
    {
        int index = hashFunction1(key);
        int step = hashFunction2(key);

        int i = 0;
        while (i < TABLE_SIZE)
        {
            if (!table[index].isEmpty && table[index].key == key)
            {
                table[index].isEmpty = true;
                return;
            }
            index = (index + step) % TABLE_SIZE;
            i++;
        }
        // cout << "Error: Not Found!." << endl;
    }

    void printTable()
    {
        cout << "Hash Table:" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            cout << "Bucket " << i << ": ";
            if (!table[i].isEmpty)
            {
                cout << "(" << table[i].key << ", " << table[i].value << ")" << endl;
            }
            else
            {
                cout << endl;
            }
        }
    }
};

int main()
{
    HashTable ht;

    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(22, 220);
    ht.insert(6, 60);
    ht.insert(15, 150);

    ht.printTable();

    cout << "Searching for key 6: " << ht.search(6) << endl;
    cout << "Searching for key 15: " << ht.search(15) << endl;
    cout << "Searching for key 7: " << ht.search(7) << endl;

    ht.remove(6);
    ht.remove(15);

    ht.printTable();
    
    cout << "Searching for key 22: " << ht.search(22) << endl;
    cout << "Searching for key 15: " << ht.search(15) << endl;
    cout << "Searching for key 1: " << ht.search(1) << endl;

    return 0;
}
