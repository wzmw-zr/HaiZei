/*************************************************************************
	> File Name: 2.color.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月18日 星期三 22时56分19秒
 ************************************************************************/

#include<stdio.h>

int main() {
    char c[100] = "Hello world!\n";
    printf("\033[31m%s\033[0m", c);
    printf("\n");
    return 0;
}
