/*************************************************************************
	> File Name: 1.ls.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月19日 星期四 18时57分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<dirent.h>
#include<math.h>
#define FILEMAX 1024
#define NAMEMAX 256

int flag_a, flag_l;

void size_window(char names[][NAMEMAX], int cnt, int *row, int *col) {
    struct winsize size;
    int len[cnt], max = 0, total = 0;
    memset(len, 0, sizeof(int) * cnt);
    if (isatty(STDOUT_FILENO) == 0) {
        exit(1);
    }
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0) {
        perror("ioctl");
        exit(1);
    }
    printf("window size row = %d, col = %d\n", size.ws_row, size.ws_col);
    for (int i = 0; i < cnt; i++) {
        len[i] = strlen(names[i]);
        if (max < len[i]) max = len[i];
        total += len[i] + 1;
    }
    if (max + 1 >= size.ws_col) {
        *row = cnt;
        *col = 1;
        return ;
    }
    if (total <= size.ws_col) {
        *row = 1;
        *col = cnt;
        return ;
    }
    int try_begin = 0;
    for (int i = 0, tmp = 0; i < cnt; i++) {
        tmp += len[i] + 1; 
        if (tmp >= size.ws_col) {
            try_begin = i;
            break;
        }
    }

    for (int i = try_begin; ; i--) {
        int *wide = (int *) malloc(sizeof(int) * i); 
        memset(wide, 0, sizeof(int) * i);
        *row = (int) ceil(cnt / i);
        int try_sum = 0;
        for (int x = 0; x < i; x++) {
            for (int y = x * (*row); y < (x + 1) * (*row) && y < cnt; y++) {
                if (wide[x] < len[y]) wide[x] = len[y];
            }
            try_sum += wide[x] + 1;
        }
        if (try_sum > size.ws_col) continue;
        if (try_sum <= size.ws_col) {
            *col = i;
            break;
        }
    }
}

void show_files(char filename[][NAMEMAX], int cnt, int row, int col) {
    int wide_file[cnt];
    memset(wide_file, 0, sizeof(int) * cnt);
    for (int i = 0; i < col; i++) {
        for (int j = (i * row); j < (i + 1) * row && j < cnt; j++) {
            if (wide_file[i] < strlen(filename[j])) wide_file[i] = strlen(filename[j]);
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = i; j < i + (row * col) && j < cnt; j += row) {
            int tmp = j / row;
            printf("%-*s", wide_file[tmp] + 1, filename[j]);
        }
        printf("\n");
    }
}

void do_stat(char *filename) {
    printf("Doing with %s status\n", filename);
}

int cmp(const void *_a, const void *_b) {
    char *a = (char *) _a;
    char *b = (char *) _b;
    return strcmp(a, b) > 0;    
}

void do_ls(char *dirname) {
    //printf("Doing with di %s\n", dirname);
    DIR *dirp = NULL;
    struct dirent *direntp;
    char names[FILEMAX][NAMEMAX] = {0};
    int cnt = 0;
    if ((dirp = opendir(dirname)) == NULL) {
        if (access(dirname, R_OK) == 0) {
            if (!flag_l) {
                printf("%s\n", dirname);
                return ;
            } else {
                do_stat(dirname);
                return ;
            }
        } else {
            perror(dirname);
            return ;
        }
    } else {
        printf("%s:\n", dirname);
        while (direntp = readdir(dirp)) {
            if (direntp->d_name[0] == '.' && !flag_a) continue;
            strcpy(names[cnt++], direntp->d_name);
        }
        qsort(names, cnt, NAMEMAX, cmp);
        if (flag_l) {
            for (int i = 0; i < cnt; i++) {
                do_stat(names[i]);
            }
        } else {
            printf("Print all file\n");
            int row, col;
            size_window(names, cnt, &row, &col);
            printf("row = %d, col = %d\n", row, col);
            show_files(names, cnt, row, col);
        }
    }
}

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "al")) != -1)  {
        switch (opt) {
            case 'a': flag_a = 1; break;
            case 'l': flag_l = 1; break;
            default : {
                fprintf(stderr, "Usage: %s [-al] [filename]", argv[0]);
                exit(1);
            }
        }
    }
    //printf("optind = %d\n", optind);
    argc -= (optind - 1);
    argv += (optind - 1);
    //printf("argc = %d, argv = %s\n", argc, *(argv + 1));
    if (argc == 1) do_ls(".");
    else {
        while (--argc) {
            do_ls(*(++argv));
        }
    }
    return 0;
}

