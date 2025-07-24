#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG  //[]で配列外参照をするとエラーにしてくれる。上下のやつがないとTLEになるので注意
                        // ABC311Eのサンプル4みたいなデバック中のTLEは防げないので注意
#endif

#include <bits/stdc++.h>
using namespace std;
#include <algorithm>

#define PRINT_VAR(x)  // 変数名を出力

template <typename T>
using vc = vector<T>;  // prioriy_queueに必要なのでここにこれ書いてます
template <typename T>
using vv = vc<vc<T>>;

//-------------1.型系---------------
using ll = long long;
ll INF = 2e18;

using ld = long double;

template <class T>
using pq = priority_queue<T, vc<T>>;  // 大きい順
template <class T>
using pq_g = priority_queue<T, vc<T>, greater<T>>;  // 小さい順

//-------------2.配列系--------------
using vl = vc<ll>;
using vvl = vv<ll>;
using vvvl = vv<vl>;
using vvvvl = vv<vvl>;
using vs = vc<string>;
using vvs = vv<string>;

// b > c
// a > b

int main(){
    ll N;
    cin >> N;
    ll count = 0;
    for(ll c = 1;c <= N / 2;c++){
        for(ll b = 2;b <= N - 1;b++){
            for(ll a = 3;a <= N;a++){
                if(a - b == c)count++;
            }
        }
    }
    cout << count % 998244353  << endl;
    return 0;
}