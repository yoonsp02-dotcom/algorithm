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