#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define P 131  // 使用较大的质数
#define M 1000000007

// 字符到索引的映射函数
int hash1(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return 26 + (c - 'A');
    if (c >= '0' && c <= '9') return 52 + (c - '0');
    return -1;
}

// 计算字符串的哈希值
long long hash2(long long* prefix, long long* pows, int left, int right) {
    if (left == 0) return prefix[right];
    return (prefix[right] - prefix[left - 1] * pows[right - left + 1] % M + M) % M;
}

// 比较两个子串是否相同
int compare(char* s, int start1, int start2, int length) {
    for (int i = 0; i < length; i++) {
        if (s[start1 + i] != s[start2 + i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    char s[MAX_N];
    scanf("%s", s);
    
    // 计算pow数组
    long long pows[MAX_N];
    pows[0] = 1;
    for (int i = 1; i <= n; i++) {
        pows[i] = (pows[i-1] * P) % M;
    }
    
    // 计算前缀数组，使用滚动哈希
    long long prefix[MAX_N];
    prefix[0] = (hash1(s[0]) + 1);  // 保证非零
    for (int i = 1; i < n; i++) {
        prefix[i] = (prefix[i-1] * P + (hash1(s[i]) + 1)) % M;
    }
    
    // 处理每个查询
    for (int i = 0; i < m; i++) {
        int l1, r1, l2, r2;
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        
        // 转换为0-based索引
        l1--; r1--; l2--; r2--;
        
        // 计算两个子串的哈希值
        long long h1 = hash2(prefix, pows, l1, r1);
        long long h2 = hash2(prefix, pows, l2, r2);
        
        // 如果哈希值相同，则字符串相同
        if (h1 == h2) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    
    return 0;
}
