/*************************************************************************
	> File Name: 3.Lougu4779.cpp
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年05月27日 星期三 18时41分20秒
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;

int n, m, s, ans[1005][1005];

int main() {
    memset(ans, 0x3f3f3f3f, sizeof(ans));
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        ans[a][b] = c;
    }
    for (int i = 1; i <= n; i++) ans[i][i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                ans[j][k] = min(ans[j][k], ans[j][i] + ans[i][k]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i != 1) cout << " ";
        cout << ans[s][i];
    }
    return 0;
}
