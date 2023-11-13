#include <iostream>
#include <queue>

using namespace std;

enum Traversal{Breadth = 1, Preorder = 2, Inorder = 3, Postorder = 4};

class BstNode {
    public:
        int data{};
        BstNode *right{}, *left{};
        
        BstNode() = default;
        virtual ~BstNode(){}
};

void newNode(BstNode **root, int value) {
        BstNode *newNode{new BstNode};

        newNode->data = value;
        *root = newNode;
}

BstNode *insert(BstNode *root, int value) {
    if (root == nullptr) newNode(&root, value);
    else if (value <= root->data) root->left = insert(root->left, value);
    else root->right = insert(root->right, value);

    return root;
}

BstNode *findMin(BstNode *root) {
    if (root->left == nullptr) return root;
    return findMin(root->left);
}    

BstNode *deletion(BstNode *root, int value) {
    if (root == nullptr) return root;
    else if (value < root->data) root->left = deletion(root->left, value);
    else if (value > root->data) root->right = deletion(root->right, value);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            BstNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            BstNode *temp = root;
            root = root->left;
            delete temp;
        }
        else {
            BstNode *temp = findMin(root->right);
            root->data = temp->data;
            root->right = deletion(root->right, temp->data);
        }
    }

    return root;
}

// Inorder traversal would work as well
bool isBinarySearchTree(BstNode *root, int min, int max) {
    if (root == nullptr) return true;
    else if (root->data > min 
        && root->data <= max 
        && isBinarySearchTree(root->left, min, root->data) 
        && isBinarySearchTree(root->right, root->data, max)) return true;
    else return false;
}

BstNode *searchNode(BstNode *root, int value) {
    if (root == nullptr) return root;
    else if (value == root->data) return root;
    else if (value < root->data) return searchNode(root->left, value);
    return searchNode(root->right, value);
}

BstNode *findSuccessor(BstNode *root, int value) {
    BstNode *node = searchNode(root, value);

    if (node->right != nullptr) {
        BstNode *temp = node->right;

        while (temp->left != nullptr) {
            temp = temp->left;
        }

        return temp;
    }
    else {
        BstNode *ancestor{root}, *successor{};

        while (ancestor != node) {
            if (value <= ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else ancestor = ancestor->right;
        }

        return successor;
    }
}

void breadthTraversal(BstNode *root) {
    queue<BstNode*> Q;

    Q.push(root);
    
    while (!Q.empty()) {   
        cout << Q.front()->data << ' ';
        if (Q.front()->left != nullptr) Q.push(Q.front()->left);
        if (Q.front()->right != nullptr) Q.push(Q.front()->right);
        Q.pop();
    }
}

// DLR
void depthTraversalPreorder(BstNode *root) {
    if (root == nullptr) return;
    cout << root->data << ' ';
    depthTraversalPreorder(root->left);
    depthTraversalPreorder(root->right);
}

// LDR
void depthTraversalInorder(BstNode *root) {
    if (root == nullptr) return;
    depthTraversalInorder(root->left);
    cout << root->data << ' ';
    depthTraversalInorder(root->right);
}

// LRD
void depthTraversalPostorder(BstNode *root) {
    if (root == nullptr) return;
    depthTraversalPostorder(root->left);
    depthTraversalPostorder(root->right);
    cout << root->data << ' ';
}

void printResult(BstNode *root, int answer) {
    switch (answer) {
    case Breadth:
        cout << "The tree in level order is: ";
        breadthTraversal(root);
        break;
    case Preorder:
        cout << "The tree in preorder is: ";
        depthTraversalPreorder(root);
        break;
    case Inorder:
        cout << "The tree in inorder is: ";
        depthTraversalInorder(root);
        break;
    case Postorder:
        cout << "The tree in postorder is: ";
        depthTraversalPostorder(root);
        break;
    default:
        cout << "Invalid answer.";
        break;
    }
}

int main() {
    BstNode *root{};
    int number, value, answer;

    cout << "How many elements? ";
    cin >> number;
    cout << "Enter integers: ";

    while (number != 0) { 
        cin >> value;
        root = insert(root, value);
        number--;
    }
    
    do {
        cout << "How would you like to display: 1. Breadth 2. Preorder 3. Inorder 4. Postorder? ";
        cin >> answer;
        printResult(root, answer);
    } while ((answer - 1) % 4 > 3);

    cout << "\nEnter a number to be deleted: ";
    cin >> value;

    deletion(root, value);
    printResult(root, answer);
      
    return 0;
}