#include <bits/stdc++.h>

using namespace std;

int c;
string upsideTree(string tree, string::iterator &iter);

int main() {
    cin >> c;
    while (c--) {
        string tree;
        cin >> tree;
        auto iter = tree.begin();
        cout << upsideTree(tree, iter) << "\n";
    }

    return 0;
}
// 3 4
// 1 2
string upsideTree(string tree, string::iterator &iter) {
    if (iter == tree.end())
        return "";

    if (*iter == 'x') {
        iter++;
        string leftTop = upsideTree(tree, iter);
        string rightTop = upsideTree(tree, iter);
        string leftBottom = upsideTree(tree, iter);
        string rightBottom = upsideTree(tree, iter);
        return string("x") + leftBottom + rightBottom + leftTop + rightTop;
    }
    string ret = string(1, *iter);
    iter++;
    return ret;
}