#include <bits/stdc++.h>

using namespace std;

struct RMQ {
    int n;
    vector<int> rangeMin;
    RMQ(vector<int> &array) {
        n = array.size();
        rangeMin.resize(4 * n);
        init(array, 0, n - 1, 1);
    }

    int init(const vector<int> &array, int left, int right, int node) {
        if (left == right) {
            rangeMin[node] = array[left];
            return array[left];
        }
        int mid = (left + right) / 2;
        return rangeMin[node] = min(init(array, left, mid, node * 2),
                                    init(array, mid + 1, right, node * 2 + 1));
    }

    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (nodeRight < left || right < nodeLeft)
            return INT_MAX;
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];

        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid),
                   query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }
    int query(int left, int right) { return query(left, right, 1, 0, n - 1); }

    int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        if (index < nodeLeft || nodeRight < index)
            return INT_MAX;
        if (nodeLeft == nodeRight) {
            rangeMin[node] = newValue;
            return rangeMin[node];
        }
        int mid = (nodeLeft + nodeRight) / 2;
        return min(update(index, newValue, node * 2, nodeLeft, mid),
                   update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
    }

    int update(int index, int newValue) {
        return update(index, newValue, 1, 0, n - 1);
    }
};

int C;
const int MAX_N = 100000;
int n;
vector<int> child[MAX_N];
int no2serial[MAX_N], serial2no[MAX_N];
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

void traverse(int here, int d, vector<int> &trip);
RMQ *prepareRMQ();
int distance(RMQ *rmq, int u, int v);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        for (int i = 0; i < n; ++i)
            child[i].clear();

        int q;
        cin >> n >> q;
        for (int i = 1; i < n; ++i) {
            int p;
            cin >> p;
            child[p].push_back(i);
        }
        RMQ *rmq = prepareRMQ();
        for (int i = 0; i < q; ++i) {
            int u, v;
            cin >> u >> v;
            cout << distance(rmq, u, v) << "\n";
        }
    }

    return 0;
}

void traverse(int here, int d, vector<int> &trip) {
    no2serial[here] = nextSerial;
    serial2no[nextSerial] = here;
    nextSerial++;

    depth[here] = d;
    locInTrip[here] = trip.size();
    trip.push_back(no2serial[here]);

    for (int i = 0; i < child[here].size(); ++i) {
        traverse(child[here][i], d + 1, trip);
        trip.push_back(no2serial[here]);
    }
}

RMQ *prepareRMQ() {
    nextSerial = 0;
    vector<int> trip;
    traverse(0, 0, trip);
    return new RMQ(trip);
}

int distance(RMQ *rmq, int u, int v) {
    int uSerial = locInTrip[u], vSerial = locInTrip[v];
    if (uSerial > vSerial)
        swap(uSerial, vSerial);
    int lcaNode = serial2no[rmq->query(uSerial, vSerial)];
    return depth[u] + depth[v] - 2 * depth[lcaNode];
}