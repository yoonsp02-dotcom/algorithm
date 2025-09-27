#include <bits/stdc++.h>

using namespace std;

int N;
struct MyStack {
    int arr[10000];
    int count;
    MyStack() : count(0) {}
    void push(int val) {
        arr[count] = val;
        ++count;
    }
    void pop() {
        if (count == 0)
            cout << -1 << endl;
        else {
            count--;
            cout << arr[count] << endl;
        }
    }
    int size() {
        return count;
    }
    int empty() {
        if (count == 0) return 1;
        return 0;
    }
    int top() {
        if (count == 0) return -1;
        return arr[count-1];
    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    MyStack st;
    cin >> N;
    while (N--)
    {
        string command;
        cin >> command;
        if (command == "push") {
            int val;
            cin >> val;
            st.push(val);
        }
        else if (command == "pop") {
            st.pop();
        }
        else if (command == "size") {
            cout << st.size() << endl;
        }
        else if (command == "empty") {
            cout << st.empty() << endl;
        }
        else if (command == "top") {
            cout << st.top() << endl;
        }
    }

    return 0;
}