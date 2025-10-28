#include <bits/stdc++.h>

using namespace std;

int C;

void printPostorder(vector<int> &preorder, vector<int> &inorder);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int n;
        cin >> n;
        vector<int> preorder(n), inorder(n), postorder(n);
        for (int i = 0; i < n; ++i)
            cin >> preorder[i];
        for (int i = 0; i < n; ++i)
            cin >> inorder[i];

        printPostorder(preorder, inorder);
        cout << "\n";
    }

    return 0;
}

void printPostorder(vector<int> &preorder, vector<int> &inorder) {
    int n = preorder.size();
    if (preorder.size() == 0)
        return;

    int root = preorder[0];
    int rootIdxInInorder =
        find(inorder.begin(), inorder.end(), root) - inorder.begin();
    vector<int> leftPreorder, leftInorder, rightPreorder, rightInorder;
    for (int i = 0; i < rootIdxInInorder; ++i) {
        leftPreorder.push_back(preorder[i + 1]);
        leftInorder.push_back(inorder[i]);
    }
    for (int i = rootIdxInInorder + 1; i < n; ++i) {
        rightPreorder.push_back(preorder[i]);
        rightInorder.push_back(inorder[i]);
    }

    printPostorder(leftPreorder, leftInorder);
    printPostorder(rightPreorder, rightInorder);
    cout << root << " ";
}