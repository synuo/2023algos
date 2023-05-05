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

int main(){
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(false);
    
    int n, h, x;
    vector <int> bot, top;    // 석순, 종유석
    int resultVal = 202020;
    int resultCnt = 0;
    
    cin>>n>>h;
    for (int i=0; i<n; i++){
        cin>>x;
        if (i % 2 == 0)
            bot.push_back(x);
        else{
            top.push_back(x);
        }
    }
    sort(bot.begin(), bot.end());
    sort(top.begin(), top.end());
    
    for (int i=1; i<=h; i++){
        int cnt = 0;
        int tmp = 0;
        
        tmp = lower_bound(bot.begin(), bot.end(), i) - bot.begin();
        cnt += (n/2 - tmp);
        
        tmp = upper_bound(top.begin(), top.end(), h-i) - top.begin();
        cnt += (n/2 - tmp);
        
        if (cnt == resultVal)
            resultCnt++;
        
        else if (cnt < resultVal){
            resultVal = cnt;
            resultCnt = 1;
        }
    }
    cout<<resultVal<<" "<<resultCnt;
}
