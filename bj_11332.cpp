#include <iostream>
#include <cmath>
#define MAXI 100000000

using namespace std;

double log_f(double n);

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int C; cin >> C;

    while (C--) {
        string S; double N, T, L;
        cin >> S >> N >> T >> L;

        L *= MAXI;
        L /= T;

        bool isPossible = true;
        if (S == "O(N)" && N > L) { isPossible = false; }
        if (S == "O(N^2)" && N * N > L) { isPossible = false; }
        if (S == "O(N^3)" && N * N * N > L) { isPossible = false; }
        if (S == "O(2^N)" && N > log2(L)) { isPossible = false; }
        if (S == "O(N!)" && N > log_f(L)) { isPossible = false; }

        cout << ((isPossible) ? "May Pass." : "TLE!") << "\n";
    }
}

double log_f(double n)
{
    int i = 1; double v = 1;
    while ((v *= ++i) <= n);
    return i - 1;
}