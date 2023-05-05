#include <iostream>
#define ll long long
#define MAX 10000003
using namespace std;

ll N, M, K;
ll tree[MAX];
ll arr[MAX];

ll init(ll N, ll s, ll e) {
	if (s == e) return tree[N] = arr[s];
	ll mid = (s + e) / 2;
	return tree[N] = init(N * 2, s, mid) + init(N * 2 + 1, mid + 1, e);
}

void update(ll N, ll s, ll e, ll idx, ll val) {
	if (idx > e || idx < s) return;

	if (s == e) {
		if (idx == s) tree[N] = val;
		return;
	}

	ll mid = (s + e) / 2;
	update(N * 2, s, mid, idx, val);
	update(N * 2 + 1, mid + 1, e, idx, val);
	tree[N] = tree[N * 2] + tree[N * 2 + 1];
}

ll query(ll N, ll s, ll e, ll l, ll r) {
	if (l > e || r < s)return 0;
	if (l <= s && e <= r) return tree[N];

	ll mid = (s + e) / 2;
	return query(N * 2, s, mid, l, r) + query(N * 2 + 1, mid + 1, e, l, r);
}

int main() {
	cin >> N >> M >> K;
	for (ll i = 1; i <= N; i++) {
		cin >> arr[i];
	}
	// 세그먼트 트리 생성
	init(1, 1, N);

	while (M+K>0) {
		ll a; cin >> a;
		if (a == 1) { // 구간 값 업데이트
			ll b, c; cin >> b >> c;
			update(1, 1, N, b, c);
			M--;
		}
		else { // 구간 합 출력
			ll b, c; cin >> b >> c;
			cout << query(1, 1, N, b, c) << "\n";
			K--;
		}
	}

	return 0;
}
