#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
};

// Function to insert a new node in the BST
void insertNode(struct Node* root, int x)
{
    struct Node* current = root;
    while(current != nullptr && current->value != x)
    {
        if(current->value > x && current->left != nullptr)
            current = current->left;
        else if(current->value > x && current->left == nullptr) 
        {
            struct Node* temp = new Node;
            temp->value = x;
            temp->left = nullptr;
            temp->right = nullptr;
            current->left = temp;
            return;
        }
        else if(current->value < x && current->right != nullptr)
            current = current->right;
        else if(current->value < x && current->right == nullptr)
        {
            struct Node* temp = new Node;
            temp->value = x;
            temp->left = nullptr;
            temp->right = nullptr;
            current->right = temp;
            return;
        }
    }
    // Key already exists
    if(current != nullptr) return;
}

// Function to find the smallest node greater than the current node
struct Node* findInorderSuccessor(struct Node* current)
{
    struct Node* successor = current->right;
    while(successor->left != nullptr) successor = successor->left;
    return successor;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int x)
{
    if(root == nullptr) return root;
    else
    {
        if(root->value > x)
        {
            root->left = deleteNode(root->left, x);
            return root;
        }
        else if(root->value < x)
        {
            root->right = deleteNode(root->right, x);
            return root;
        }
        else
        {
            // If the node has no children, return nullptr
            if(root->left == nullptr && root->right == nullptr) return nullptr;
            // If the node has only one child, return the child
            else if(root->left != nullptr && root->right == nullptr)
                return root->left;
            else if(root->right != nullptr && root->left == nullptr)
                return root->right;
            // If the node has two children, replace it with its inorder successor
            else
            {
                struct Node* successor = findInorderSuccessor(root);
                root->value = successor->value;
                root->right = deleteNode(root->right, successor->value);
                return root;
            }
        }
    }
}

// Function to search for a node in the BST
void searchNode(struct Node* root, int x)
{
    struct Node* current = root;
    while(current != nullptr && current->value != x)
    {
        if(current->value > x) current = current->left;
        else if(current->value < x) current = current->right;
    }
    if(current == nullptr) cout << "NO";
    else cout << "YES";
    return;
}

int main() 
{
    int numOperations;
    cin >> numOperations;
    struct Node* root = nullptr;
    for(int i = 0; i < numOperations; i++)
    {
        char operation;
        cin >> operation;
        switch(operation)
        {
            case 'B':
            {
                int value;
                cin >> value;
                if(root == nullptr)
                {
                    root = new Node;
                    root->value = value;
                    root->left = nullptr;
                    root->right = nullptr;
                }
                else insertNode(root, value);
                break;
            }
            case 'S':
            {
                int value;
                cin >> value;
                root = deleteNode(root, value);
                break;
            }
            case 'R':
            {
                int value;
                cin >> value;
                searchNode(root, value);
                cout << endl;
                break;
            }
        };
    }   
    return 0;
}
