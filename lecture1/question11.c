#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int arr[100010];    // 原始数组
    long long pre[100010] = {0};  // 前缀和数组，使用long long避免溢出
    
    // 读入数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 计算前缀和
    pre[0] = arr[0];  // 第一个元素
    for (int i = 1; i < n; i++) {
        pre[i] = pre[i-1] + arr[i];
    }
    
    // 处理查询
    while (m--) {
        int l, r;
        scanf("%d %d", &l, &r);
        
        // 将输入的1-based索引转换为0-based
        l--;
        r--;
        
        // 计算区间和
        // 如果l为0，直接返回pre[r]
        // 否则返回pre[r] - pre[l-1]
        long long result;
        if (l == 0) {
            result = pre[r];
        } else {
            result = pre[r] - pre[l-1];
        }
        
        printf("%lld\n", result);
    }
    
    return 0;
}
