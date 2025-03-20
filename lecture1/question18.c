#include <stdio.h>

// 数组大小设为100010，多开10个空间避免边界问题
int arr[100010];      // 原始数组
int n;               // 数组长度

// 计算一个数字的二进制表示中1的个数
int one_count(int num) {
    int count = 0;
    
    // 当num不为0时，继续处理
    while (num) {
        // 如果当前位是1，count加1
        if (num & 1) {
            count++;
        }
        // 右移一位
        num >>= 1;
    }
    
    return count;
}

int main() {
    // 读入n
    scanf("%d", &n);
    
    // 读入数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 处理每个数并输出结果
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");  // 在数字之间添加空格
        printf("%d", one_count(arr[i]));
    }
    printf("\n");
    
    return 0;
}
