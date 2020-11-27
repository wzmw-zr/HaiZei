/*************************************************************************
	> File Name: 3.LeetCode118.cpp
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年11月27日 星期五 08时23分51秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
using namespace std;

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    for (int i = 1; i <= numRows; i++) ans.push_back(vector<int>(i, 1));
    for (int i = 1; i <= numRows; i++) {
        for (int j = 2; j < ans[i - 1].size(); j++) {
            ans[i - 1][j - 1] = ans[i - 2][j - 1] + ans[i - 2][j - 2];
        }
    }
    return ans;
}

int main() {
    return 0;
}
