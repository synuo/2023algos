#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

ll arr[1000001], tree[1<<21];

ll init(int node, int start, int end) {
	if (start == end) return tree[node] = arr[start];

	int mid = (start + end) / 2;
	ll left = init(node * 2, start, mid);
	ll right = init(node * 2 + 1, mid + 1, end);

	return tree[node] = left + right;
}

void update(int node, int start, int end, int index, ll diff) {
	if (index < start || index > end) return;
	tree[node] = tree[node] + diff;

	if (start != end) {
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, diff);
		update(node * 2 + 1, mid + 1, end, index, diff);
	}
}

ll query(int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	ll Lquery = query(node * 2, start, mid, left, right);
	ll Rquery = query(node * 2 + 1, mid + 1, end, left, right);
	return Lquery + Rquery;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) 
		cin >> arr[i];
	
	init(1, 1, n);

	for (int i = 0; i < m+k; i++) {
		ll a, b, c;
		cin >> a >> b >> c;

		if (a == 1) {
			ll diff = c - arr[b];
			arr[b] = c;
			update(1, 1, n, b, diff);
		}
		if (a == 2) {
			cout << query(1, 1, n, b, c) << "\n";
		}
	}

	return 0;
}
