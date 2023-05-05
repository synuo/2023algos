//
//  11658.cpp
//  BOJ
//
//  Created by LeeSuMin on 2023/05/04.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;

ll N,M;
ll arr[1025][1025];
ll tree[1025][1025];

ll sum(ll r, ll c){
    ll result = 0;
    for(ll i=r; i>0; i -= (i & -i))
        for(ll j=c; j>0; j -= (j & -j))
            result += tree[i][j];
    return result;
}

void update(ll r, ll c, ll value){
    for(ll i=r; i<=N; i+=(i & -i))
        for(ll j=c; j<=N; j += (j & -j))
            tree[i][j] += value;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> M;
    
    for(ll i=1; i<=N; ++i){
        for(ll j=1; j<=N; ++j){
            cin >> arr[i][j];
            update(i,j,arr[i][j]);
        }
    }
    
    ll w,r1,c1,r2,c2,num;
    while(M--){
        cin >> w;
        if(w==0){
            cin >> r1 >> c1 >> num;
            update(r1, c1, num-arr[r1][c1]);
            arr[r1][c1] = num;
        }
        else if(w==1){
            cin >> r1 >> c1 >> r2 >> c2;
            cout << sum(r2,c2)-sum(r2, c1-1)-sum(r1-1, c2) + sum(r1-1, c1-1) << "\n";
        }
        
    }
    
    return 0;
}
