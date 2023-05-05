#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define MOD 1000000007
using namespace std;
typedef long long ll;

ll arr[1000001], tree[1<<21];

ll init(int node, int start, int end) {
	if (start == end) return tree[node] = arr[start];

	int mid = (start + end) / 2;
	ll left = init(node * 2, start, mid);
	ll right = init(node * 2 + 1, mid + 1, end);

	return tree[node] = left * right % MOD;
}

void update(int node, int start, int end, int index, ll val) {
	if (index < start || index > end) return;
	if (index == start && index == end) tree[node] = val;
	else {
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = tree[node * 2] * tree[node * 2 + 1] % MOD;
	}
}

ll query(int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 1;
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	ll Lquery = query(node * 2, start, mid, left, right);
	ll Rquery = query(node * 2 + 1, mid + 1, end, left, right);
	return Lquery * Rquery % MOD;
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
			arr[b] = c;
			update(1, 1, n, b, c);
		}
		if (a == 2) {
			cout << query(1, 1, n, b, c) % MOD << "\n";
		}
	}

	return 0;
}
