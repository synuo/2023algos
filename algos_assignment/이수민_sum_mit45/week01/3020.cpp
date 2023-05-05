//
//  3020.cpp
//  BOJ
//
//  Created by LeeSuMin on 2023/05/04.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define INF 1e13+9;
using namespace std;
 
int N, H; //N 짝수
int top[500001];
int bottom[500001];
 
int main(){
    
    cin >> N >> H;
    int h;
    for(int i = 0; i < N; i++){
        cin >> h;
        if(i % 2 == 0) bottom[h]++; //석순
        else top[H - h + 1]++; //종유석
    }
    
    for(int i = 1; i <= H; i++){
        top[i] += top[i-1];
        bottom[H-i] += bottom[H-i+1];
    }
    
    long long ans = INF;
    int cnt = 0;
    for(int i = 1; i <= H; i++){
        if(top[i] + bottom[i] < ans){
            cnt = 1;
            ans = top[i] + bottom[i];
        }
        else if(top[i] + bottom[i] == ans){
            cnt++;
        }
    }
    
    cout << ans << " " << cnt;
    
    return 0;
}
