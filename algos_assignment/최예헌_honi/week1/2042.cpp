#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define MAX 10002
#define INF 987654321

ll n,m,k;
ll arr[1000005] = {0,};
ll sumtree[2100005];

// 초기화
ll init(ll node, ll s, ll e){
    if (s == e)
        return sumtree[node] = arr[s];
    
    ll mid = (s+e)/2;
    return sumtree[node] = init(node*2,s,mid) + init(node*2+1,mid+1,e);
}

// 합 찾기
ll query(ll node, ll s, ll e, ll l, ll r){
    if (l > e || r < s)
        return 0;
    
    if (l <= s && e <= r)
        return sumtree[node];
    
    ll mid = (s+e)/2;
    return query(node*2,s,mid,l,r) + query(node*2+1,mid+1,e,l,r);
}

// 업데이트
void update(ll node, ll s, ll e, ll idx, ll val){
    if (idx > e || idx < s)
        return;
    
    if (s == e){
        if (idx == s)
            sumtree[node] = val;
        return;
    }
    
    ll mid = (s+e)/2;
    update(node*2, s, mid, idx, val);
    update(node*2+1, mid+1, e, idx, val);
    sumtree[node] = sumtree[node*2] + sumtree[node*2+1];
}

int main(){
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    
    ll a, b, c;
    
    cin>>n>>m>>k;
    for (int i=1; i<=n; i++)
        cin>>arr[i];
    
    init(1, 1, n);
    
    ll tmp = m+k;
    while (tmp--){
        cin>>a>>b>>c;
        
        if (a == 2)    // query
            cout<<query(1, 1, n, b, c)<<"\n";
        
        else if (a == 1)   // update
            update(1, 1, n, b, c);
    }
}
