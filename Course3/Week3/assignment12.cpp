/* Huffman coding with idea of tree data structure. */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Node {
    public:
        Node *left{}, *right{};
        int weight{};

        Node(int weight) : weight(weight){}
        virtual ~Node() {
            if (left) {
                delete left;
                left = nullptr;
            }
            if (right) {
                delete right;
                right = nullptr;
            }
        }
};

struct compare {
    bool operator()(Node *left, Node *right) {
        return left->weight > right->weight;
    }
};

int findMax(Node *node) {
    if (!node) return -1;
    else {
        int lDepth = findMax(node->left);
        int rDepth = findMax(node->right);

        return max(lDepth, rDepth) + 1;
    }
}

int findMin(Node *node) {
    if (!node) return -1;
    else {
        int lDepth = findMin(node->left);
        int rDepth = findMin(node->right);

        return min(lDepth, rDepth) + 1;
    }
}

int main() {
    int number, weight;
    Node *left, *right, *root;
    ifstream file("huffman.txt");
    priority_queue<Node*, vector<Node*>, compare> pQ;

    file >> number;

    while (file >> weight) {
        pQ.push(new Node(weight));
    }

    while (pQ.size() > 1) {
        left = pQ.top();
        pQ.pop();

        right = pQ.top();
        pQ.pop();

        root = new Node(left->weight + right->weight);
        root->left = left;
        root->right = right;
        pQ.push(root);
    }

    cout << findMax(pQ.top()) << '\n' << findMin(pQ.top());
    
    return 0;
}