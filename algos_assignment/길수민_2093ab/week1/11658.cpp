#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<pi, int> pii;
typedef pair<pi, pi> pipi;

const int MAX = 1030;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
ll two_bit[MAX][MAX];
int arr[MAX][MAX];
int N, M;

void update (int diff, int x, int y) {
    while (y <= N) {
        int row = x;
        while (row <= N) {
            two_bit[row][y] += diff;
            row += row & (-row);
        }
        y += y & (-y);
    }
}

ll query (int x, int y) {
    ll ret = 0;
    while (y > 0) {
        int row = x;
        while (row > 0) {
            ret += two_bit[row][y];
            row -= row & (-row);
        }
        y -= y & (-y);
    }
    return ret;
}

int main (void)
{
    ios_base::sync_with_stdio (false);
    cin.tie (NULL);
    cout.tie (NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
            update (arr[i][j], i, j);
        }
    }
    while (M--) {
        int w, x1, y1;
        cin >> w >> x1 >> y1;
        if (w) {
            int x2, y2;
            cin >> x2 >> y2;
            ll ans = query (x2, y2) + query (x1 - 1, y1 - 1);
            ans -= query (x1 - 1, y2) + query (x2, y1 - 1);
            cout << ans << "\n";
        } else {
            int c;
            cin >> c;
            update (c - arr[x1][y1], x1, y1);
            arr[x1][y1] = c;
        }
    }
    return 0;
}
