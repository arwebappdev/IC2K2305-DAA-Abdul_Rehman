
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Create a binary tree recursively
Node* createTree() {

    int value;

    cout << "Enter node value (-1 for no node): ";
    cin >> value;

    if (value == -1) {
        return nullptr;
    }

    Node* newNode = new Node(value);

    cout << "Enter left child of " << value << endl;
    newNode->left = createTree();

    cout << "Enter right child of " << value << endl;
    newNode->right = createTree();

    return newNode;
}

// Preorder: Root, Left, Right
void preorder(Node* root) {

    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";

    preorder(root->left);
    preorder(root->right);
}

// Inorder: Left, Root, Right
void inorder(Node* root) {

    if (root == nullptr) {
        return;
    }

    inorder(root->left);

    cout << root->data << " ";

    inorder(root->right);
}

// Postorder: Left, Right, Root
void postorder(Node* root) {

    if (root == nullptr) {
        return;
    }

    postorder(root->left);
    postorder(root->right);

    cout << root->data << " ";
}

// Free dynamically allocated memory
void deleteTree(Node* root) {

    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int main() {

    cout << "Binary Tree Creation\n\n";

    Node* root = createTree();

    cout << "\nPreorder Traversal: ";
    preorder(root);

    cout << "\nInorder Traversal: ";
    inorder(root);

    cout << "\nPostorder Traversal: ";
    postorder(root);

    cout << endl;

    deleteTree(root);

    return 0;
}
