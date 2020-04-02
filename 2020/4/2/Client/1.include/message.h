/*************************************************************************
	> File Name: message.h
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年04月01日 星期三 14时19分51秒
 ************************************************************************/

#ifndef _MESSAGE_H
#define _MESSAGE_H
typedef struct User {
    char name[256];
    pthread_t tid;
    int sockfd;
    struct User *next;
} User;

typedef struct Message {
    char name[256], target[256], file_path[256];
    int type;
    char data[1024];
} Message;
#endif
