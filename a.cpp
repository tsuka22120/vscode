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

int N, M;
int M_G;
int M_H;
int G[28][28];
int H[28][28];
int A[8][8];
int main() {
    cin >> N;
    cin >> M_G;
    for(int i = 0;i < M_G;i++)for(int j = 0;j < M_G;j++)cin >>G[i][j];
    cin >> M_H;
    for(int i = 0;i < M_H;i++)for(int j = 0;j < M_H;j++)cin >>H[i][j];
    for(int i = 0;i < N - 1;i++)for(int j = 1;j < N;j++)cin >>A[i][j];
    