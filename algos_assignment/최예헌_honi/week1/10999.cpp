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

ll n, m, k;
ll a, b, c, d;
ll arr[1000005];
ll tree[5000005], lazy[5000005] = {0,};

ll init(ll now,ll s,ll e){
    if (s == e)
        return tree[now] = arr[s];
    
    ll mid = (s+e)/2;
    return tree[now] = init(now*2, s, mid) + init(now*2+1, mid+1, e);
}

void propagate(ll now, ll s, ll e){
    if (!lazy[now])
        return;
    
    tree[now] += (e-s+1) * lazy[now];
    
    if (s != e){
        lazy[now*2] += lazy[now];
        lazy[now*2+1] += lazy[now];
    }
    lazy[now] = 0;
}

void update(ll now, ll s, ll e, ll l, ll r, ll val){
    propagate(now, s, e);
    
    if (l > e || r < s)
        return;
    
    if (l <= s && e <= r){
        tree[now] += (e-s+1) * val;
        
        if (s != e){
            lazy[now*2] += val;
            lazy[now*2+1] += val;
        }
        return;
    }
    
    ll mid = (s+e)/2;
    update(now*2, s, mid, l, r, val);
    update(now*2+1, mid+1, e, l, r, val);
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
    
    cin>>n>>m>>k;
    for (int i=0; i<n; i++)
        cin>>arr[i];
    
    init(1, 0, n-1);
    ll temp = m + k;
    while (temp--){
        cin>>a;
        
        if (a == 1){              //update
            cin>>b>>c>>d;
            update(1, 0, n-1, b-1, c-1, d);
        }
        
        else if (a == 2){         //query
            cin>>b>>c;
            cout<<query(1, 0, n-1, b-1, c-1)<<"\n";
        }
    }
}
