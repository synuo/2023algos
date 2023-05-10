#include <iostream>

using namespace std;

int Find(string s, string goal) {
	int cnt = 0;
	for (int i = 0; i <= (int(s.size()) - 1); i++) {
		bool flag = true;
		for (int j = i; j <= (i + int(goal.size()) - 1); j++) {
			if (s[j] != goal[j - i]) {
				flag = false;
				break;
			}
		}
		if (flag)
			cnt++;
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	int maxi = 0;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int count = 0;
		count += Find(s, "for");
		count += Find(s, "while");
		maxi = max(maxi, count);
	}
	cout << maxi;
	return 0;
}