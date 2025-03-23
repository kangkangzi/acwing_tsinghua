#include <stdio.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 1000005

char P[MAX_N];    // 模式串
char S[MAX_M];    // 主串
int next[MAX_N];  // next数组

// 构建next数组
void get_next(char *p, int *next, int len) {
    next[0] = 0;
    int j = 0;
    for (int i = 1; i < len; i++) {
        while (j > 0 && p[i] != p[j]) {
            j = next[j - 1];    // 回退
        }
        if (p[i] == p[j]) {
            j++;
        }
        next[i] = j;
    }
}

// KMP匹配算法
void kmp_search(char *s, char *p, int s_len, int p_len) {
    get_next(p, next, p_len);
    
    int j = 0;  // 模式串的位置
    int first = 1;  // 用于控制输出格式
    
    // 遍历主串
    for (int i = 0; i < s_len; i++) {
        // 当字符不匹配时，模式串指针回退
        while (j > 0 && s[i] != p[j]) {
            j = next[j - 1];
        }
        
        // 当前字符匹配成功，模式串指针前进
        if (s[i] == p[j]) {
            j++;
        }
        
        // 如果完全匹配
        if (j == p_len) {
            if (first) {
                printf("%d", i - p_len + 1);
                first = 0;
            } else {
                printf(" %d", i - p_len + 1);
            }
            j = next[j - 1];  // 继续寻找下一个匹配
        }
    }
    printf("\n");
}

int main() {
    int N, M;
    
    // 读入模式串长度和模式串
    scanf("%d", &N);
    scanf("%s", P);
    
    // 读入主串长度和主串
    scanf("%d", &M);
    scanf("%s", S);
    
    // 执行KMP匹配
    kmp_search(S, P, M, N);
    
    return 0;
}
