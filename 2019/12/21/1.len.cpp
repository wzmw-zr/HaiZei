/*************************************************************************
	> File Name: 1.len.cpp
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2019年12月21日 星期六 14时11分48秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<inttypes.h>
#define max_n 1000000
using namespace std;


int64_t get_len(int64_t n) {
    if (n == 1) return 1;
    if (n & 1) return get_len(3 * n + 1) + 1;
    return get_len(n / 2) + 1;
}


int main() {
    int64_t ans = 0, len = 0;
    for (int64_t i = 1; i <= max_n; i++) {
        int64_t temp = get_len(i);
        if(temp > len) {
            ans = i;
            len = temp;
        }
    }
    printf("%" PRId64 " %" PRId64 "\n", ans, len);
    return 0;
}
