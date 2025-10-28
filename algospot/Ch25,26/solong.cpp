#include <bits/stdc++.h>

using namespace std;

const int ALPHABETS = 26;
int toNumber(char c) { return c - 'A'; }

struct TrieNode {
    TrieNode *children[ALPHABETS];
    int terminal;
    int first;
    TrieNode() {
        terminal = -1;
        first = -1;
        memset(children, 0, sizeof(children));
    }
    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; ++i) {
            if (children[i])
                delete children[i];
        }
    }

    void insert(const char *key, int id) {
        if (first == -1)
            first = id;
        if (*key == 0)
            terminal = id;
        else {
            int next = toNumber(*key);
            if (children[next] == NULL) {
                children[next] = new TrieNode();
            }
            children[next]->insert(key + 1, id);
        }
    }

    TrieNode *find(const char *key) {
        if (*key == 0)
            return this;
        int next = toNumber(*key);
        if (children[next] == NULL)
            return NULL;
        return children[next]->find(key + 1);
    }

    int type(const char *key, int id) {
        if (*key == 0)
            return 0;
        if (first == id)
            return 1;
        int next = toNumber(*key);
        return 1 + children[next]->type(key + 1, id);
    }
};

int countKeys(TrieNode *trie, const char *word) {
    TrieNode *node = trie->find(word);
    if (node == NULL || node->terminal == -1) {
        return strlen(word);
    }
    return trie->type(word, node->terminal);
}

TrieNode *readInput(int words) {
    vector<pair<int, string>> input;
    for (int i = 0; i < words; ++i) {
        char buf[11];
        int freq;
        scanf("%s %d", buf, &freq);
        input.push_back({-freq, buf});
    }
    sort(input.begin(), input.end());
    TrieNode *trie = new TrieNode();
    for (int i = 0; i < input.size(); ++i) {
        trie->insert(input[i].second.c_str(), i);
    }
    trie->first = -1;
    return trie;
}

int main() {
    int C;
    cin >> C;
    while (C--) {
        int n, m;
        int result = 0;
        string tmp;
        cin >> n >> m;
        TrieNode *trie = readInput(n);
        for (int i = 0; i < m; i++) {
            cin >> tmp;
            result += countKeys(trie, tmp.c_str());
        }
        cout << result + m - 1 << "\n";
    }
}