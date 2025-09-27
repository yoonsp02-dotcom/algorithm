#include <bits/stdc++.h>

using namespace std;
const int INF = 987654321;
const int recipe[5] = {8, 8, 4, 1, 9};
const int toping[4] = {1, 30, 25, 10};
int haveIngredients[5];
int haveToping[4];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int T;
    cin >> T;
    while (T--) {
        for (int i = 0; i < 5; ++i) 
            cin >> haveIngredients[i];
        for (int i = 0; i < 4; ++i)
            cin >> haveToping[i];
        int batter = 16;
        double coef = INF;
        for (int i = 0; i < 5; ++i) {
            coef = min(coef, haveIngredients[i] * 1.0 / recipe[i]);
        }
        batter *= coef;
        
        int pancake = 0;
        for (int i = 0; i < 4; ++i) {
            pancake += haveToping[i] / toping[i];
        }
        pancake = min(pancake, batter);
        cout << pancake << "\n";
    }




    return 0;
}