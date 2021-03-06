/*************************************************************************
	> File Name: 4.Luogu2865.cpp
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年07月01日 星期三 19时09分34秒
 ************************************************************************/

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
#define MAX_N 5000
#define MAX_R 100000

struct edge {
    int from, to, val, next;
};

edge edg[2 * MAX_R + 5];

int n, r, edg_cnt;
int head[MAX_N + 5], ans1[MAX_N + 5], ans2[MAX_N + 5], mark[MAX_N + 5];

void make_edge(int a, int b, int c) {
    edg[edg_cnt].from = a;
    edg[edg_cnt].to = b;
    edg[edg_cnt].val= c;
    edg[edg_cnt].next = head[a];
    head[a] = edg_cnt++;
}

int main() {
    memset(head, -1, sizeof(head));
    memset(ans1, 0x3f, sizeof(ans1));
    memset(ans2, 0x3f, sizeof(ans2));
    cin >> n >> r;
    for (int i = 0; i < r; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        make_edge(a, b, c);
        make_edge(b, a, c);
    }
    queue<int> que;
    que.push(1);
    ans1[1] = 0;
    mark[1] = 1;
    while (!que.empty()) {
        int t = que.front();
        que.pop();
        mark[t] = 0;
        for (int i = head[t]; i != -1; i = edg[i].next) {
            if (ans1[edg[i].to] > ans1[t] + edg[i].val) {
                ans1[edg[i].to] = ans1[t] + edg[i].val;
                if (mark[edg[i].to] == 0) {
                    mark[edg[i].to] = 1;
                    que.push(edg[i].to);
                }
            }
        }
    }

    que.push(n);
    ans2[n] = 0;
    mark[n] = 1;
    while (!que.empty()) {
        int t = que.front();
        que.pop();
        mark[t] = 0;
        for (int i = head[t]; i != -1; i = edg[i].next) {
            if (ans2[edg[i].to] > ans2[t] + edg[i].val) {
                ans2[edg[i].to] = ans2[t] + edg[i].val;
                if (mark[edg[i].to] == 0) {
                    mark[edg[i].to] = 1;
                    que.push(edg[i].to);
                }
            }
        }
    }
    int fin = 99999999;
    for (int i = 0; i < edg_cnt; i++) {
        int t = ans1[edg[i].from] + ans2[edg[i].to] + edg[i].val;
        if (fin > t && t != ans1[n]) {
            fin = t;
        }
    }
    cout << fin << endl;
    return 0;
}
