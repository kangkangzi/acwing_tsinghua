#include <stdio.h>

// 数组大小设为100010，多开10个空间避免边界问题
int A[100010];        // 序列A
int B[100010];        // 序列B
int n, m;            // n是A的长度，m是B的长度

int main() {
    // 读入n, m
    scanf("%d %d", &n, &m);
    
    // 读入序列A
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    
    // 读入序列B
    for (int i = 0; i < m; i++) {
        scanf("%d", &B[i]);
    }
    
    // 双指针算法
    int pointer_a = 0;    // 指向序列A的指针
    int pointer_b = 0;    // 指向序列B的指针
    
    // 当两个指针都未到达末尾时继续搜索
    while (pointer_a < n && pointer_b < m) {
        // 如果当前元素相同，两个指针都向前移动
        if (A[pointer_a] == B[pointer_b]) {
            pointer_a++;
        }
        // 无论是否相同，B的指针都要向前移动
        pointer_b++;
    }
    
    // 判断结果
    // 如果pointer_a到达了n，说明A的所有元素都在B中找到了对应
    if (pointer_a == n) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}
