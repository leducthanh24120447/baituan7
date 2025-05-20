#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

// Function to create a new node
NODE* createNode(int data) {
    NODE* newNode = new NODE();
    if (!newNode) {
        cout << "Memory allocation failed!\n";
        return nullptr;
    }
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}

// Function to insert a node in the binary tree
NODE* insertNode(NODE* root, int data) {
    if (!root) return createNode(data);

    queue<NODE*> q;
    q.push(root);

    while (!q.empty()) {
        NODE* current = q.front();
        q.pop();

        if (!current->p_left) {
            current->p_left = createNode(data);
            break;
        }
        else {
            q.push(current->p_left);
        }

        if (!current->p_right) {
            current->p_right = createNode(data);
            break;
        }
        else {
            q.push(current->p_right);
        }
    }
    return root;
}

// Pre-order traversal
void NLR(NODE* pRoot) {
    if (pRoot) {
        cout << pRoot->key << " ";
        NLR(pRoot->p_left);
        NLR(pRoot->p_right);
    }
}

// In-order traversal
void LNR(NODE* pRoot) {
    if (pRoot) {
        LNR(pRoot->p_left);
        cout << pRoot->key << " ";
        LNR(pRoot->p_right);
    }
}

// Post-order traversal
void LRN(NODE* pRoot) {
    if (pRoot) {
        LRN(pRoot->p_left);
        LRN(pRoot->p_right);
        cout << pRoot->key << " ";
    }
}

// Level-order traversal
void LevelOrder(NODE* pRoot) {
    if (!pRoot) return;

    queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        NODE* current = q.front();
        q.pop();
        cout << current->key << " ";

        if (current->p_left) q.push(current->p_left);
        if (current->p_right) q.push(current->p_right);
    }
}

// Count nodes
int countNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// Sum of nodes
int sumNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

// Count leaf nodes
int countLeaf(NODE* pRoot) {
    if (!pRoot) return 0;
    if (!pRoot->p_left && !pRoot->p_right) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}

// Function to process a command dynamically
void processCommand(NODE*& root, const string& command) {
    stringstream ss(command);
    string action;
    int value;

    ss >> action;
    if (action == "insert") {
        if (ss >> value) {
            root = insertNode(root, value);
        }
        else {
            cout << "Invalid insert command. Use 'insert <number>'\n";
        }
    }
    else if (action == "NLR") {
        NLR(root);
        cout << endl;
    }
    else if (action == "LNR") {
        LNR(root);
        cout << endl;
    }
    else if (action == "LRN") {
        LRN(root);
        cout << endl;
    }
    else if (action == "LevelOrder") {
        LevelOrder(root);
        cout << endl;
    }
    else if (action == "countNode") {
        cout << countNode(root) << endl;
    }
    else if (action == "sumNode") {
        cout << sumNode(root) << endl;
    }
    else if (action == "countLeaf") {
        cout << countLeaf(root) << endl;
    }
    else {
        cout << "Unknown command. Available commands: insert <value>, NLR, LNR, LRN, LevelOrder, countNode, sumNode, countLeaf\n";
    }
}
