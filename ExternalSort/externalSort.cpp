#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class ExternalSort
{
public:
    // Constructor
    ExternalSort(std::string inputFileName, std::string outputFileName);

    // Destructor
    ~ExternalSort();

    // External sorting algorithm
    void sort();

private:
    std::string inputFileName;
    std::string outputFileName;
    int chunkSize;  // Size of each chunk to fit into memory
    int memorySize; // Total memory size available
    std::vector<std::string> tempFileNames;

    // Helper functions
    void deleteTempFiles();
    void mergeSortedChunks(const vector<string> &inputFiles, const string &outputFileName);
    void writeChunkToTempFile(const vector<int> &chunk, const string &fileName);
};

// Quicksort function
int partition(vector<int> &arr, int lower, int upper)
{
    int pivot = arr[upper];
    int i = (lower - 1);

    for (int j = lower; j <= upper - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[upper]);
    return (i + 1);
}

void quickSort(vector<int> &arr, int lower, int upper)
{
    if (lower < upper)
    {
        int pi = partition(arr, lower, upper);
        quickSort(arr, lower, pi - 1);
        quickSort(arr, pi + 1, upper);
    }
}

// Heap functions
void heapify(vector<pair<int, ifstream *>> &heap, int i)
{
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < heap.size() && heap[l].first < heap[smallest].first)
        smallest = l;

    if (r < heap.size() && heap[r].first < heap[smallest].first)
        smallest = r;

    if (smallest != i)
    {
        swap(heap[i], heap[smallest]);
        heapify(heap, smallest);
    }
}

void buildHeap(vector<pair<int, ifstream *>> &heap)
{
    int startIdx = (heap.size() / 2) - 1;
    for (int i = startIdx; i >= 0; i--)
    {
        heapify(heap, i);
    }
}

pair<int, ifstream *> extractMin(vector<pair<int, ifstream *>> &heap)
{
    pair<int, ifstream *> root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify(heap, 0);
    return root;
}

void insertToHeap(vector<pair<int, ifstream *>> &heap, pair<int, ifstream *> element)
{
    heap.push_back(element);
    int i = heap.size() - 1;
    while (i && heap[(i - 1) / 2].first > heap[i].first)
    {
        swap(heap[i], heap[(i - 1) / 2]);
        i = ((i - 1) / 2);
    }
}

// Constructor
ExternalSort::ExternalSort(std::string inputFileName, std::string outputFileName)
{
    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;
    chunkSize = 10000;  // Default chunk size
    memorySize = 10000; // Default memory size
}

// Destructor
ExternalSort::~ExternalSort()
{
    deleteTempFiles();
}

// External sorting algorithm
void ExternalSort::sort()
{
    ifstream inputFile(inputFileName);
    vector<int> chunk;
    int num;

    while (inputFile >> num)
    {
        chunk.push_back(num);
        if (chunk.size() == chunkSize)
        {
            quickSort(chunk, 0, chunk.size() - 1);
            string tempFileName = "temp" + to_string(tempFileNames.size()) + ".txt";
            writeChunkToTempFile(chunk, tempFileName);
            tempFileNames.push_back(tempFileName);
            chunk.clear();
        }
    }

    if (!chunk.empty())
    {
        quickSort(chunk, 0, chunk.size() - 1);
        string tempFileName = "temp" + to_string(tempFileNames.size()) + ".txt";
        writeChunkToTempFile(chunk, tempFileName);
        tempFileNames.push_back(tempFileName);
    }

    inputFile.close();
    mergeSortedChunks(tempFileNames, outputFileName);
}

// Write chunk to temporary file
void ExternalSort::writeChunkToTempFile(const std::vector<int> &chunk, const std::string &fileName)
{
    ofstream tempFile(fileName);
    for (int num : chunk)
    {
        tempFile << num << " ";
    }
    tempFile.close();
}

// Delete temporary files
void ExternalSort::deleteTempFiles()
{
    for (string fileName : tempFileNames)
    {
        remove(fileName.c_str());
    }
    tempFileNames.clear();
}

// Merge sorted chunks
void ExternalSort::mergeSortedChunks(const std::vector<std::string> &inputFiles, const std::string &outputFileName)
{
    vector<pair<int, ifstream *>> minHeap;
    vector<ifstream> streams(inputFiles.size());
    for (size_t i = 0; i < inputFiles.size(); ++i)
    {
        streams[i].open(inputFiles[i]);
        int num;
        if (streams[i] >> num)
        {
            insertToHeap(minHeap, make_pair(num, &streams[i]));
        }
    }

    ofstream outputFile(outputFileName);
    while (!minHeap.empty())
    {
        pair<int, ifstream *> smallest = extractMin(minHeap);
        outputFile << smallest.first << " ";
        if (*smallest.second >> smallest.first)
        {
            insertToHeap(minHeap, smallest);
        }
    }

    outputFile.close();
    for (ifstream &stream : streams)
    {
        stream.close();
    }
}

// Function to create a file with random numbers
void createRandomFile(const std::string &fileName, int numElements, int maxValue)
{
    ofstream outputFile(fileName);
    srand(time(0));
    for (int i = 0; i < numElements; ++i)
    {
        outputFile << (rand() % maxValue) << " ";
    }
    outputFile.close();
}

// Main function to demonstrate the usage of ExternalSort
int main()
{
    string smallInputFileName = "small_input.txt";
    string smallOutputFileName = "small_sorted_output.txt";
    string largeInputFileName = "large_input.txt";
    string largeOutputFileName = "large_sorted_output.txt";

    // Create a small input file with specific numbers
    ofstream smallInputFile(smallInputFileName);
    vector<int> smallNumbers = {56, 12, 33, 99, 17, 42, 70, 81, 3, 20};
    for (int num : smallNumbers)
    {
        smallInputFile << num << " ";
    }
    smallInputFile.close();

    // Create a large input file with random numbers
    int numElements = 100000; // Number of random elements
    int maxValue = 1000000;   // Maximum value of random elements
    createRandomFile(largeInputFileName, numElements, maxValue);

    // Perform external sort on the small file
    ExternalSort smallSorter(smallInputFileName, smallOutputFileName);
    smallSorter.sort();
    cout << "Small file sorting complete" << endl;

    // Perform external sort on the large file
    ExternalSort largeSorter(largeInputFileName, largeOutputFileName);
    largeSorter.sort();
    cout << "Large file sorting complete" << endl;

    return 0;
}
