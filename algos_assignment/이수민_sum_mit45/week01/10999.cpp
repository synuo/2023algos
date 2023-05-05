//
//  10999.cpp
//  BOJ
//
//  Created by LeeSuMin on 2023/05/04.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define INF 1e13+9
#define ll long long
using namespace std;
 
ll N, M, K; // M 변경 일어나는 횟수, K 구간의 합을 구하는 횟수
ll arr[1000001];
//vector<ll> segmentTree;
ll segmentTree[5000005];
ll lazy[5000005]={0,};

ll make_segmentTree(ll node, ll start, ll end){
    if(start == end) return segmentTree[node] = arr[start];
    
    ll mid = (start+end)/2;
    ll left_result = make_segmentTree(node*2, start, mid);
    ll right_result = make_segmentTree(node*2+1, mid+1, end);
    segmentTree[node] = left_result + right_result;
    
    return segmentTree[node];
}

void lazy_update(ll node, ll start, ll end){
    if(!lazy[node]){
        return;
    }
    
    segmentTree[node] = segmentTree[node] + (end - start + 1) * lazy[node]; //업데이트 과정
    if (start != end){ //leaf node가 아닌 경우, lazy값을 자식들에게 전달
        lazy[node * 2] = lazy[node * 2] + lazy[node];
        lazy[node * 2 + 1] = lazy[node * 2 + 1] + lazy[node];
    }
    lazy[node] = 0; //업데이트 진행 후 다시 lazy=0
}

void update(ll node, ll start, ll end, ll left, ll right, ll value){
    lazy_update(node, start, end); //lazy의 값을 먼저 확인하고 해당 노트 업데이트
    
    if(left > end || right < start) return; //찾아야하는 구간(l~r)이 현재 구간(s~e)에 포함되지 않을 때
    
    if(left <= start && end <= right){ //찾아야하는 구간(l~r)내에 현재 구간(s~e)이 포함될 때

        segmentTree[node] = segmentTree[node] + (end-start+1)*value; //해당 오드까지만 업데이트
        if(start!=end){ //leafnode 아니라면, 자식 노드들은 업데이트 하지않고 lazy값만 표시
            lazy[node*2] = lazy[node*2]+value;
            lazy[node*2+1] = lazy[node*2+1]+value;
        }
        return;
    }
    
    //찾아야하는 구간(l~r)이 현재 구간(s~e)에 포함되거나, 부분적으로 겹치는 경우
    ll mid = (start+end)/2;
    update(node*2, start, mid, left, right, value);
    update(node*2+1, mid+1, end, left, right, value);
    segmentTree[node] = segmentTree[node*2] + segmentTree[node*2+1];
}

ll sum(ll node, ll start, ll end, ll left, ll right){
    lazy_update(node, start, end); //lazy값 업데이트
    if(left > end || right < start) return 0; //찾아야하는 구간(l~r)과 현재 구간(s~e)이 포함되지 않을때
    if(left <=start && end <= right) return segmentTree[node]; //찾아야하는 구간(l~r)내에 현재 구간(s~e)이 포함될 때
    
    //찾아야하는 구간(l~r)이 현재 구간(s~e)에 포함되거나, 부분적으로 겹치는 경우
    ll mid = (start+end)/2;
    ll left_result = sum(node*2, start, mid, left, right);
    ll right_result = sum(node*2+1, mid+1, end, left, right);
    return left_result + right_result;
}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;
    for(ll i=0; i<N; i++) cin >> arr[i];
    
    //ll tree_height = (int)ceil(log2(N));
    //ll tree_size = (1<<(tree_height+1));
    
    // segmentTree.resize(tree_size);
    make_segmentTree(1, 0, N-1);
    
    for(ll i=0; i<M+K; i++){
        ll a=0; cin >> a;
        ll b,c,d;
        if(a==1){
            cin >> b >> c >> d; //b번째 수부터 c번째 수에 d더하기
            update(1, 0, N-1, b-1, c-1, d);
        }
        else{
            cin >> b >> c; //b번째 수부터 c번째 수 합 구하기
            cout << sum(1,0,N-1,b-1,c-1) << "\n";
        }
    }
    
    return 0;
}
