#include <iostream>
#include <queue>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	priority_queue <int> pq;
	int N, candi, result = 0;
	cin >> N;
	cin >> candi;
	for (int i = 1; i < N; i++) {
		int k;
		cin >> k;
		pq.push(k);
	}
	while (!pq.empty()) {
		if (pq.top() < candi) {
			break;
		}
		int x = pq.top();
		pq.pop();
		x -= 1;
		candi += 1;
		result += 1;
		pq.push(x);
	}
	cout << result;
	return 0;
}

