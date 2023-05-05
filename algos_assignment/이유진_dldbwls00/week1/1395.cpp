#include<iostream>
#include<vector>
#include<cmath>

#define MAX 100010
using namespace std;

int n, m;
int Switch[MAX];
vector<int> segTree;
vector<int> lazy;
vector<pair<int, pair<int, int>>> cmd;

void lazyPropagation(int node, int start, int end){
    if (lazy[node] != 0){
        segTree[node] = (end - start + 1) - segTree[node];
        if (start != end){
            lazy[node * 2] = !lazy[node * 2];
            lazy[node * 2 + 1] = !lazy[node * 2 + 1];
        }
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r){ //스위치 상태를 반전
    lazyPropagation(node, start, end);
    if (r < start || l > end) 
        return;
    if (l <= start && end <= r){ //fully inclusive
        segTree[node] = (end - start + 1) - segTree[node];
        if (start != end){
            lazy[node * 2] = !lazy[node * 2];
            lazy[node * 2 + 1] = !lazy[node * 2 + 1];
        }
        return;
    }

    int mid = (start + end) / 2;
    update(node * 2, start, mid, l, r);
    update(node * 2 + 1, mid + 1, end, l, r);
    segTree[node] = segTree[node * 2] + segTree[node * 2 + 1];
}

int query(int node, int start, int end, int l, int r){ //켜져 있는 상태의 스위치 개수를 물음
    lazyPropagation(node, start, end);
    if (r < start || l > end) 
        return 0;
    if (l <= start && end <= r)  //fully inclusive
        return segTree[node];

    int mid = (start + end) / 2;
    return query(node * 2, start, mid, l, r) + query(node * 2 + 1, mid + 1, end, l, r);
}

int main(void){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        cmd.push_back(make_pair(a, make_pair(b, c)));
    }

    int treeHeight = (int)ceil(log2(n));
    int treeSize = 1 << (treeHeight + 1);
    segTree.resize(treeSize, 0);
    lazy.resize(treeSize);

    for (int i = 0; i < m; i++) {
        int command = cmd[i].first;
        if (command == 0) {
            int index = cmd[i].second.first - 1;
            int index2 = cmd[i].second.second - 1;
            update(1, 0, n - 1, index, index2);
            continue;
        }

        int index = cmd[i].second.first - 1;
        int index2 = cmd[i].second.second - 1;
        cout << query(1, 0, n - 1, index, index2) << "\n";
    }

    return 0;
}
