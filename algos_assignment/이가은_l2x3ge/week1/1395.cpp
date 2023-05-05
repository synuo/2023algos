#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

ll arr[2000001] = { 0, }, lazy[1 << 22], tree[1 << 22];

void lazy_propagate(int node, int start, int end) {
	if (lazy[node] %2 == 0) return; // lazy가 짝수라면 반전해도 소용 없음
	if (left != right) {
		lazy[node * 2] += lazy[node];
		lazy[node * 2 + 1] += lazy[node];
	}
	// 전구 반전 = 전체 스위치 - 켜진 스위치
	tree[node] = (end - start + 1) - tree[node];
	lazy[node] = 0;
}

void update(int node, int start, int end, int left, int right) {
	lazy_propagate(node, start, end);
	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		lazy[node] += 1;
		lazy_propagate(node, start, end);
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, left, right);
	update(node * 2 + 1, mid + 1, end, left, right);
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

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		if (a == 0) {
			update(1, 1, n, b, c);
		}
		if (a == 1) {
			cout << query(1, 1, n, b, c) << "\n";
		}
	}

	return 0;
}
