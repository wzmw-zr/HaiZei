/*************************************************************************
	> File Name: 7.HZOJ323.cpp
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年04月28日 星期二 17时33分19秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<algorithm>
using namespace std;
#define MAX_N 10000

struct data {
    int p, d;
} Data[MAX_N + 5];

struct UnionSet {
    int fa[MAX_N + 5];
    void init(int n) {
        for (int i = 0; i <= n; i++) fa[i] = i;
    }

    int get(int x) {
        return fa[x] = (x == fa[x] ? x : get(fa[x]));
    }

    void merge(int x, int y) {
        int a = get(x), b = get(y);
        fa[a] = b;
    }
};

UnionSet u;

int n;

int cmp(data a, data b) {
    return a.p > b.p;
}

int solve() {
    if (!(cin >> n)) return 0; 
    for (int i = 1; i <= n; i++) {
        cin >> Data[i].p >> Data[i].d;
    }
    u.init(MAX_N);
    sort(Data + 1, Data + n + 1, cmp);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int day = u.get(Data[i].d);
        if (day == 0) continue;
        ans += Data[i].p;
        u.merge(day, day - 1);
    }
    cout << ans << endl;
    return 1;
}


int main() {
    while (solve());
    return 0;
}
