#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Person
{
    int id;
    int score;

    Person(int id, int score) : id(id), score(score) {}

    bool operator>(const Person &other) const
    {
        return score > other.score; // Min heap based on score
    }
};

void heapify(priority_queue<Person, vector<Person>, greater<Person>> &minHeap)
{
    // Re-heapify after removing the root
    vector<Person> temp;
    while (!minHeap.empty())
    {
        temp.push_back(minHeap.top());
        minHeap.pop();
    }
    for (const auto &person : temp)
    {
        minHeap.push(person);
    }
}

void eliminateWeakest(priority_queue<Person, vector<Person>, greater<Person>> &minHeap)
{
    if (minHeap.empty())
    {
        cout << "No persons left to eliminate.\n";
        return;
    }

    Person weakest = minHeap.top();
    minHeap.pop();

    cout << "Eliminated person with ID " << weakest.id << " and score " << weakest.score << ".\n";

    heapify(minHeap);
}

int main()
{
    cout << "Testing the functions by first adding instances and then using the heap methods to eliminate the lowest of all.";
    cout << endl;
    priority_queue<Person, vector<Person>, greater<Person>> minHeap;
    cout << "Instances added";
    cout << endl;

    // Inserting persons into the heap
    minHeap.push(Person(1, 85));
    minHeap.push(Person(2, 72));
    minHeap.push(Person(3, 93));
    minHeap.push(Person(4, 64));
    minHeap.push(Person(5, 78));

    while (minHeap.size() > 1)
    {
        eliminateWeakest(minHeap);
    }

    if (!minHeap.empty())
    {
        Person winner = minHeap.top();
        cout << "Winner is person with ID " << winner.id << " and score " << winner.score << ".\n";
    }

    return 0;
}
