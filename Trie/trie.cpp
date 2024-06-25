#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int ALPHABET_SIZE = 26;

class TrieNode
{
public:
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false)
    {
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            children[i] = nullptr;
        }
    }
};

class Trie
{
public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        deleteTrie(root);
    }

    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            int index = ch - 'a';
            if (node->children[index] == nullptr)
            {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    bool search(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            int index = ch - 'a';
            if (node->children[index] == nullptr)
            {
                return false;
            }
            node = node->children[index];
        }
        return node->isEndOfWord;
    }

    void remove(const string &word)
    {
        remove(root, word, 0);
    }

    void display()
    {
        string prefix;
        display(root, prefix);
    }

private:
    TrieNode *root;

    void deleteTrie(TrieNode *node)
    {
        if (node == nullptr)
            return;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            deleteTrie(node->children[i]);
        }
        delete node;
    }

    bool remove(TrieNode *node, const string &word, int depth)
    {
        if (node == nullptr)
            return false;

        if (depth == word.size())
        {
            if (!node->isEndOfWord)
                return false;

            node->isEndOfWord = false;

            for (int i = 0; i < ALPHABET_SIZE; ++i)
            {
                if (node->children[i] != nullptr)
                {
                    return false;
                }
            }

            return true;
        }

        int index = word[depth] - 'a';
        if (remove(node->children[index], word, depth + 1))
        {
            delete node->children[index];
            node->children[index] = nullptr;

            return !node->isEndOfWord && none_of(node->children, node->children + ALPHABET_SIZE, [](TrieNode *child)
                                                 { return child != nullptr; });
        }

        return false;
    }

    void display(TrieNode *node, string &prefix)
    {
        if (node == nullptr)
            return;

        if (node->isEndOfWord)
        {
            cout << prefix << endl;
        }

        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if (node->children[i] != nullptr)
            {
                prefix.push_back('a' + i);
                display(node->children[i], prefix);
                prefix.pop_back();
            }
        }
    }
};

int main()
{
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("hi");
    trie.insert("hell");
    trie.insert("hill");
    trie.insert("code");
    trie.insert("coder");
    trie.insert("test");

    cout << "Words in trie:" << endl;
    trie.display();

    cout << endl;

    cout << "Searching for 'hello': " << (trie.search("hello") ? "Found" : "Not Found") << endl;
    cout << "Searching for 'world': " << (trie.search("world") ? "Found" : "Not Found") << endl;
    cout << "Searching for 'hi': " << (trie.search("hi") ? "Found" : "Not Found") << endl;
    cout << "Searching for 'bye': " << (trie.search("bye") ? "Found" : "Not Found") << endl;
    cout << "Searching for 'code': " << (trie.search("code") ? "Found" : "Not Found") << endl;
    cout << "Searching for 'testing': " << (trie.search("testing") ? "Found" : "Not Found") << endl;

    trie.remove("hi");
    trie.remove("coder");
    trie.remove("hell");
    cout << "\nAfter deleting:" << endl;
    trie.display();

    return 0;
}
