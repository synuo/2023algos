#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

ll arr[2000001], lazy[1 << 22], tree[1 << 22];

ll init(int node, int start, int end) {
	if (start == end) return tree[node] = arr[start];

	int mid = (start + end) / 2;
	ll left = init(node * 2, start, mid);
	ll right = init(node * 2 + 1, mid + 1, end);

	return tree[node] = left + right;
}

void lazy_propagate(int node, int start, int end) {
	if (lazy[node] == 0) return;
	if (left != right) {
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}
	tree[node] += lazy[node] * (end - start + 1);
	lazy[node] = 0;
}

void update(int node, int start, int end, int left, int right, ll val) {
	lazy_propagate(node, start, end);
	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		lazy[node] += val;
		lazy_propagate(node, start, end);
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, left, right, val);
	update(node * 2 + 1, mid + 1, end, left, right, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
	lazy_propagate(node, start, end);

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

	for (int i = 0; i < m + k; i++) {
		int a, b, c;
		ll d;
		cin >> a >> b >> c;

		if (a == 1) {
			cin >> d;
			update(1, 1, n, b, c, d);
		}
		if (a == 2) {
			cout << query(1, 1, n, b, c) << "\n";
		}
	}

	return 0;
}
