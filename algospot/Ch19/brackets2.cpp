#include <bits/stdc++.h>

using namespace std;

int C;

bool isMatched(const string &brackets);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> C;
    while (C--) {
        string brackets;
        cin >> brackets;
        if (isMatched(brackets))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}

bool isMatched(const string &brackets) {
    stack<char> openBrackets;
    for (int i = 0; i < brackets.size(); ++i) {
        char check = brackets[i];
        if (check == '(' || check == '{' || check == '[')
            openBrackets.push(check);

        else if (openBrackets.empty())
            return false;

        else if (check == ')' && openBrackets.top() == '(')
            openBrackets.pop();

        else if (check == '}' && openBrackets.top() == '{')
            openBrackets.pop();

        else if (check == ']' && openBrackets.top() == '[')
            openBrackets.pop();

        else
            return false;
    }
    return openBrackets.empty();
}