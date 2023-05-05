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

ll n, m;
ll a, b, c;
ll arr[100005];
ll tree[500005], lazy[500005] = {0,};

ll init(ll now,ll s,ll e){
    if (s == e)
        return tree[now] = 0;
    
    ll mid = (s+e)/2;
    return tree[now] = init(now*2, s, mid) + init(now*2+1, mid+1, e);
}

void propagate(ll now, ll s, ll e){
    if (lazy[now] % 2 == 0)
        return;
    
    tree[now] = (e-s+1) - tree[now];
    
    if (s != e){
        lazy[now*2] += lazy[now];
        lazy[now*2+1] += lazy[now];
    }
    lazy[now] = 0;
}

void update(ll now, ll s, ll e, ll l, ll r){
    propagate(now, s, e);
    
    if (l > e || r < s)
        return;
    
    if (l <= s && e <= r){
        tree[now] = (e-s+1) - tree[now];
        
        if (s != e){
            lazy[now*2]+=1;
            lazy[now*2+1]+=1;
        }
        return;
    }
    
    ll mid = (s+e)/2;
    update(now*2, s, mid, l, r);
    update(now*2+1, mid+1, e, l, r);
    tree[now] = tree[now*2] + tree[now*2+1];
}

ll query(ll now,ll s,ll e,ll l,ll r){
    propagate(now, s, e);
    if (l > e || r < s)
        return 0;
    
    if (l <= s && e <= r)
        return tree[now];
    
    ll mid = (s+e)/2;
    return query(now*2, s, mid, l, r) + query(now*2+1, mid+1, e, l, r);
}

int main(){
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    
    cin>>n>>m;
    init(1, 0, n-1);
    
    while (m--){
        cin>>a>>b>>c;
        
        if (a == 0)              //update
            update(1, 0, n-1, b-1, c-1);
        
        else         //query
            cout<<query(1, 0, n-1, b-1, c-1)<<"\n";
    }
}
