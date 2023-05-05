#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int n, h;
	int a[500001] = { 0, }; //석순
	int b[500001] = { 0, }; //종유석
	cin >> n >> h;
	for (int i = 0; i < n/2; i++) {
		int h1, h2;
		cin >> h1 >> h2;
		a[h1]++;
		b[h2]++;
	}
	for (int i = h; i >= 2; i--) {
		a[i - 1] += a[i];
		b[i - 1] += b[i];
	}
	vector<int> v;
	for (int i = 1; i <= h; i++)
		v.push_back(a[i] + b[h - i + 1]);
	sort(v.begin(), v.end());
	cout << v[0] << " ";
	for (int i = 1; i < h; i++) {
		if (v[i] != v[0] || i == h - 1) {
			cout << i;
			break;
		}
	}

	return 0;
}
