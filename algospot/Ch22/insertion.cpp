#include <bits/stdc++.h>

using namespace std;

typedef int KeyType;

struct Node {
    int priority, size;
    Node *left, *right;
    KeyType key;
    Node(const KeyType &_key)
        : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}

    void setLeft(Node *newleft) {
        left = newleft;
        calcSize();
    }
    void setRight(Node *newRight) {
        right = newRight;
        calcSize();
    }
    void calcSize() {
        size = 1;
        if (left)
            size += left->size;
        if (right)
            size += right->size;
    }
};

typedef pair<Node *, Node *> NodePair;

NodePair split(Node *root, KeyType key) {
    if (root == NULL)
        return NodePair(NULL, NULL);

    NodePair ret;
    if (root->key < key) {
        ret.first = root;
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        ret.second = rs.second;
    } else {
        ret.second = root;
        NodePair ls = split(root->left, key);
        root->setLeft(ls.second);
        ret.first = ls.first;
    }

    return ret;
}

Node *insert(Node *root, Node *node) {
    if (root == NULL) {
        return node;
    }

    if (root->priority < node->priority) {
        NodePair subtrees = split(root, node->key);
        node->setLeft(subtrees.first);
        node->setRight(subtrees.second);
        return node;
    }

    else if (root->key <= node->key) {
        root->setRight(insert(root->right, node));
    } else {
        root->setLeft(insert(root->left, node));
    }
    return root;
}

Node *merge(Node *a, Node *b) {
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    if (a->priority >= b->priority) {
        a->setRight(merge(a->right, b));
        return a;
    }

    b->setLeft(merge(a, b->left));
    return b;
}

Node *erase(Node *root, KeyType key) {
    if (root == NULL)
        return root;

    if (root->key == key) {
        Node *ret = merge(root->left, root->right);
        delete root;
        return ret;
    }

    if (root->key <= key)
        root->setRight(erase(root->right, key));
    else
        root->setLeft(erase(root->left, key));

    return root;
}

Node *kth(Node *root, int k) {
    int leftSize = 0;
    if (root->left)
        leftSize = root->left->size;
    if (leftSize + 1 == k)
        return root;
    if (leftSize >= k)
        return kth(root->left, k);
    return kth(root->right, k - leftSize - 1);
}

int countLessThan(Node *root, KeyType key) {
    if (root == NULL)
        return 0;

    if (root->key >= key)
        return countLessThan(root->left, key);

    int ls = (root->left ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right, key);
}

int C;

vector<int> insertion(int n, vector<int> &move) {
    vector<int> ret(n);
    Node *root = NULL;
    for (int i = 1; i <= n; ++i) {
        root = insert(root, new Node(i));
    }

    for (int i = n; i >= 1; --i) {
        int k = i - move[i - 1];
        Node *a = kth(root, k);
        ret[i - 1] = a->key;
        root = erase(root, a->key);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int n;
        cin >> n;
        vector<int> move(n);
        for (int i = 0; i < n; ++i)
            cin >> move[i];
        vector<int> ans = insertion(n, move);

        for (int i : ans)
            cout << i << " ";
        cout << "\n";
    }

    return 0;
}