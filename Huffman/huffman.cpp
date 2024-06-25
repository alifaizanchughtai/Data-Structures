#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct HuffNode
{
    char alphabet;
    int char_count;
    HuffNode *left;
    HuffNode *right;
};

HuffNode *getHuffNode(char ch, int freq, HuffNode *left, HuffNode *right);
void stringToBits(HuffNode *root, string str, unordered_map<char, string> &freqTable);
string bitsToString(HuffNode *root, int &i, string str);
void buildHeap(vector<HuffNode *> &huffmanHeap);
void heapify(vector<HuffNode *> &huffmanHeap, int i);
HuffNode *extractMin(vector<HuffNode *> &huffmanHeap);
unordered_map<char, string> HuffmanTree(string inputText);

HuffNode *getHuffNode(char ch, int freq, HuffNode *left, HuffNode *right)
{
    HuffNode *node = new HuffNode();
    node->alphabet = ch;
    node->char_count = freq;
    node->left = left;
    node->right = right;
    return node;
}

void stringToBits(HuffNode *root, string str, unordered_map<char, string> &freqTable)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
        freqTable[root->alphabet] = str;

    stringToBits(root->left, str + "0", freqTable);
    stringToBits(root->right, str + "1", freqTable);
}

string bitsToString(HuffNode *root, int &i, string str)
{
    HuffNode *current = root;
    while (current->left || current->right)
    {
        if (str[i] == '0')
            current = current->left;
        else
            current = current->right;
        i++;
    }
    return string(1, current->alphabet);
}

void heapify(vector<HuffNode *> &huffmanHeap, int i)
{
    int lowest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < huffmanHeap.size() && huffmanHeap[left]->char_count < huffmanHeap[lowest]->char_count)
        lowest = left;

    if (right < huffmanHeap.size() && huffmanHeap[right]->char_count < huffmanHeap[lowest]->char_count)
        lowest = right;

    if (lowest != i)
    {
        swap(huffmanHeap[i], huffmanHeap[lowest]);
        heapify(huffmanHeap, lowest);
    }
}

void buildHeap(vector<HuffNode *> &huffmanHeap)
{
    int n = huffmanHeap.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(huffmanHeap, i);
}

HuffNode *extractMin(vector<HuffNode *> &huffmanHeap)
{
    HuffNode *temp = huffmanHeap[0];
    huffmanHeap[0] = huffmanHeap.back();
    huffmanHeap.pop_back();
    heapify(huffmanHeap, 0);
    return temp;
}

unordered_map<char, string> HuffmanTree(string inputText)
{
    unordered_map<char, int> freq;
    for (char ch : inputText)
    {
        freq[ch]++;
    }

    vector<HuffNode *> huffmanHeap;
    for (auto pair : freq)
    {
        huffmanHeap.push_back(getHuffNode(pair.first, pair.second, nullptr, nullptr));
    }

    buildHeap(huffmanHeap);

    while (huffmanHeap.size() != 1)
    {
        HuffNode *left = extractMin(huffmanHeap);
        HuffNode *right = extractMin(huffmanHeap);
        int sum = left->char_count + right->char_count;
        huffmanHeap.push_back(getHuffNode('\0', sum, left, right));
        buildHeap(huffmanHeap);
    }

    HuffNode *root = extractMin(huffmanHeap);

    unordered_map<char, string> freqTable;
    stringToBits(root, "", freqTable);

    cout << "Huffman Codes:\n"
         << endl;
    for (auto pair : freqTable)
    {
        cout << pair.first << " " << pair.second << endl;
    }

    cout << "\nOriginal String:\n"
         << inputText << endl;

    string encodedString = "";
    for (char ch : inputText)
    {
        encodedString += freqTable[ch];
    }

    cout << "\nEncoded String:\n"
         << encodedString << endl;

    int idx = 0;
    cout << "\nDecoded String:\n";
    while (idx < (int)encodedString.size())
    {
        cout << bitsToString(root, idx, encodedString);
    }
    cout << endl;

    return freqTable;
}

int main()
{
    string inputText = "huffman coding example";
    unordered_map<char, string> huffmanCodes = HuffmanTree(inputText);

    return 0;
}
