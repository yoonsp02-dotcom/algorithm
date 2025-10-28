#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector<Node *> children;
};

int C, longest, n;
int x[100], y[100], r[100];

bool encloses(int outter, int inner);
bool isChild(int parent, int child);
Node *getTree(int root);
int height(Node *root);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> x[i] >> y[i] >> r[i];

        Node *root = getTree(0);
        longest = 0;
        int h = height(root);
        cout << max(longest, h) << "\n";
    }

    return 0;
}

bool encloses(int outter, int inner) {
    double dist =
        sqrt(pow(x[outter] - x[inner], 2) + pow(y[outter] - y[inner], 2));
    return r[outter] > r[inner] && r[outter] > dist + r[inner];
}

bool isChild(int parent, int child) {
    if (!encloses(parent, child))
        return false;
    for (int i = 0; i < n; ++i) {
        if (i != parent && i != child && encloses(parent, i) &&
            encloses(i, child))
            return false;
    }
    return true;
}

Node *getTree(int root) {
    Node *ret = new Node();
    for (int ch = 0; ch < n; ++ch) {
        if (isChild(root, ch))
            ret->children.push_back(getTree(ch));
    }
    return ret;
}

int height(Node *root) {
    vector<int> heights;
    for (int i = 0; i < root->children.size(); ++i) {
        heights.push_back(height(root->children[i]) + 1);
    }
    if (heights.size() == 0)
        return 0;

    sort(heights.begin(), heights.end());
    if (heights.size() >= 2) {
        longest = max(longest, heights[heights.size() - 2] +
                                   heights[heights.size() - 1]);
    }

    return heights.back();
}