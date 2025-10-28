#include <bits/stdc++.h>

using namespace std;

int C;
int adj[26][26];
vector<int> wordsIdx[26][26];
int indegree[26], outdegree[26];

void makeGraph(const vector<string> &words);
void getEulerCircuit(int here, vector<int> &circuit);
vector<int> getEulerTrailOrCircuit();
bool checkEuler();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        int n;
        cin >> n;
        vector<string> words(n);
        for (int i = 0; i < n; ++i)
            cin >> words[i];
        makeGraph(words);
        if (!checkEuler()) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        vector<int> circuit;
        circuit = getEulerTrailOrCircuit();
        reverse(circuit.begin(), circuit.end());
        if (circuit.size() != words.size() + 1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        for (int i = 1; i < circuit.size(); ++i) {
            int a = circuit[i - 1], b = circuit[i];
            // cout << a << " to " << b << endl;
            int idx = wordsIdx[a][b].back();
            cout << words[i] << " ";
            wordsIdx[a][b].pop_back();
        }
        cout << "\n";
    }

    return 0;
}

void makeGraph(const vector<string> &words) {
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j)
            wordsIdx[i][j].clear();
    memset(adj, 0, sizeof(adj));
    memset(indegree, 0, sizeof(indegree));
    memset(outdegree, 0, sizeof(outdegree));

    for (int i = 0; i < words.size(); ++i) {
        int l = words[i].size();
        int f = words[i][0] - 'a';
        int e = words[i][l - 1] - 'a';
        adj[f][e]++;
        wordsIdx[f][e].push_back(i);
        indegree[e]++;
        outdegree[f]++;
    }
}

void getEulerCircuit(int here, vector<int> &circuit) {
    for (int there = 0; there < 26; ++there) {
        while (adj[here][there] > 0) {
            adj[here][there]--;
            getEulerCircuit(there, circuit);
        }
    }
    circuit.push_back(here);
}

vector<int> getEulerTrailOrCircuit() {
    vector<int> circuit;
    for (int i = 0; i < 26; ++i) {
        if (indegree[i] + 1 == outdegree[i]) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }

    for (int i = 0; i < 26; ++i) {
        if (outdegree[i]) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }

    return circuit;
}

bool checkEuler() {
    int plus1 = 0, minus1 = 0;
    for (int i = 0; i < 26; ++i) {
        int delta = indegree[i] - outdegree[i];
        if (delta == 1)
            plus1++;
        if (delta == -1)
            minus1++;
    }
    return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}