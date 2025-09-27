#include <iostream>

using namespace std;

int main(void) {
    int a, b;
    cin >> a >> b;
    a = b - a;
    for (int i = b; i >= 1; --i) {
        if (a % i == 0 && b % i == 0) {
            a /= i; b /= i;
        }
    }
    cout << a << " " << b << "\n";

    return 0;
}