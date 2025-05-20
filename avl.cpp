#include <iostream>
#include <algorithm>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;

    NODE(int data) : key(data), p_left(nullptr), p_right(nullptr), height(1) {}
};

// Function 1: Create a new node
NODE* createNode(int data) {
    return new NODE(data);
}

// Utility to get height of a node
int getHeight(NODE* node) {
    return node ? node->height : 0;
}

// Utility to get balance factor of a node
int getBalance(NODE* node) {
    return node ? getHeight(node->p_left) - getHeight(node->p_right) : 0;
}

// Update height of a node
void updateHeight(NODE* node) {
    if (node)
        node->height = 1 + max(getHeight(node->p_left), getHeight(node->p_right));
}

// Right rotate
NODE* rotateRight(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;

    x->p_right = y;
    y->p_left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotate
NODE* rotateLeft(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;

    y->p_left = x;
    x->p_right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balance the node
NODE* balance(NODE* node) {
    updateHeight(node);
    int balanceFactor = getBalance(node);

    // Left Left Case
    if (balanceFactor > 1 && getBalance(node->p_left) >= 0)
        return rotateRight(node);

    // Left Right Case
    if (balanceFactor > 1 && getBalance(node->p_left) < 0) {
        node->p_left = rotateLeft(node->p_left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balanceFactor < -1 && getBalance(node->p_right) <= 0)
        return rotateLeft(node);

    // Right Left Case
    if (balanceFactor < -1 && getBalance(node->p_right) > 0) {
        node->p_right = rotateRight(node->p_right);
        return rotateLeft(node);
    }

    return node;
}

// Function 2: Insert into AVL tree
void Insert(NODE*& pRoot, int x) {
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return; // Duplicate value, do nothing

    pRoot = balance(pRoot);
}

// Get the node with the minimum key in subtree
NODE* getMinValueNode(NODE* node) {
    NODE* current = node;
    while (current->p_left)
        current = current->p_left;
    return current;
}

// Function 3: Remove a node
void Remove(NODE*& pRoot, int x) {
    if (!pRoot) return;

    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        // Node with one child or no child
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else {
            NODE* temp = getMinValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }

    if (pRoot)
        pRoot = balance(pRoot);
}

// Function 4: Check if binary tree is AVL
bool isAVL(NODE* pRoot) {
    if (!pRoot) return true;

    int lh = getHeight(pRoot->p_left);
    int rh = getHeight(pRoot->p_right);

    if (abs(lh - rh) > 1)
        return false;

    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
