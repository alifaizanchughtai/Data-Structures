#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random book name
string generateRandomBookName()
{
    string prefixes[] = {"The", "A", "An", "My", "Your", "Our"};
    string topics[] = {"Adventure", "Mystery", "Fantasy", "Science Fiction", "Romance", "Thriller"};
    string suffixes[] = {"Book", "Tale", "Adventure", "Story"};

    string bookName = prefixes[rand() % 6] + " " +
                      topics[rand() % 6] + " " +
                      suffixes[rand() % 4];

    return bookName;
}

int main()
{
    stack<string> bookStack;
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    // Push 10 random books onto the stack
    cout << "Stacking up books...\n";
    for (int i = 0; i < 10; ++i)
    {
        string bookName = generateRandomBookName();
        bookStack.push(bookName);
        cout << "Pushed \"" << bookName << "\" onto the stack.\n";
    }

    // Pop all books from the stack
    cout << "\nPopping books from the stack...\n";
    while (!bookStack.empty())
    {
        cout << "Popped \"" << bookStack.top() << "\" from the stack.\n";
        bookStack.pop();
    }

    return 0;
}
