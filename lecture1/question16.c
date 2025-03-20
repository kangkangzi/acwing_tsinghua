#include <stdio.h>

// 数组大小设为100010，多开10个空间避免边界问题
int A[100010];        // 第一个数组
int B[100010];        // 第二个数组
int n, m, x;         // n是A的长度，m是B的长度，x是目标值

int main() {
    // 读入n, m, x
    scanf("%d %d %d", &n, &m, &x);
    
    // 读入数组A
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    
    // 读入数组B
    for (int i = 0; i < m; i++) {
        scanf("%d", &B[i]);
    }
    
    // 双指针算法
    int left = 0;         // 指向数组A的指针
    int right = m - 1;    // 指向数组B的指针
    
    // 记录答案的位置
    int ans_i = 0, ans_j = 0;
    
    // 当两个指针都有效时继续搜索
    while (left < n && right >= 0) {
        long long sum = (long long)A[left] + B[right];  // 使用long long避免溢出
        
        if (sum == x) {
            // 找到答案
            ans_i = left;
            ans_j = right;
            break;
        } else if (sum > x) {
            // 和太大，需要减小，移动right指针
            right--;
        } else {
            // 和太小，需要增大，移动left指针
            left++;
        }
    }
    
    // 输出结果
    printf("%d %d\n", ans_i, ans_j);
    
    return 0;
}
