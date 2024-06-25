#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;

    // Constructor
    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1; // New node is initially added at leaf level, height is 1
    }
};

// AVL tree class
class AVLTree
{
private:
    Node *root;

    int getHeight(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node *node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node *node)
    {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *balance(Node *node)
    {
        updateHeight(node);

        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1)
        {
            if (getBalanceFactor(node->left) >= 0)
                return rightRotate(node);

            else
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        else if (balanceFactor < -1)
        {
            if (getBalanceFactor(node->right) <= 0)
                return leftRotate(node);

            else
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;

        return balance(node);
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *node, int value)
    {
        if (node == nullptr)
            return node;

        if (value < node->data)
            node->left = deleteNode(node->left, value);
        else if (value > node->data)
            node->right = deleteNode(node->right, value);
        else
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                Node *temp = (node->left != nullptr) ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else
            {
                Node *temp = minValueNode(node->right);

                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }
        if (node == nullptr)
            return node;
        return balance(node);
    }

    void inorder(Node *node)
    {
        if (node != nullptr)
        {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    AVLTree()
    {
        root = nullptr;
    }
    void insert(int value)
    {
        root = insert(root, value);
    }
    void deleteKey(int value)
    {
        root = deleteNode(root, value);
    }

    void inorderTraversal()
    {
        inorder(root);
        cout << endl;
    }
};

int main()
{
    AVLTree tree;

    // Inserting keys into AVL tree
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    cout << "Inorder traversal of AVL tree: ";
    tree.inorderTraversal();

    tree.deleteKey(30);
    tree.deleteKey(500);
    cout << "Inorder traversal of AVL tree after deletion: ";
    tree.inorderTraversal();

    return 0;
}
