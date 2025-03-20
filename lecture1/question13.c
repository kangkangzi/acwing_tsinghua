#include <stdio.h>

// 数组大小设为100010，多开10个空间避免边界问题
int arr[100010];      // 原始数组
int diff[100010];     // 差分数组
int n, m;

// 计算差分数组
void calculate_diff() {
    // 第一个元素
    diff[0] = arr[0];
    
    // 其余元素
    for (int i = 1; i < n; i++) {
        diff[i] = arr[i] - arr[i-1];
    }
}

// 根据差分数组重建原始数组
void rebuild_array() {
    // 第一个元素
    arr[0] = diff[0];
    
    // 其余元素
    for (int i = 1; i < n; i++) {
        arr[i] = arr[i-1] + diff[i];
    }
}

int main() {
    // 读入n, m
    scanf("%d %d", &n, &m);
    
    // 读入原始数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 计算初始的差分数组
    calculate_diff();
    
    // 处理每个操作
    while (m--) {
        int l, r, c;
        scanf("%d %d %d", &l, &r, &c);
        
        // 将1-based索引转换为0-based
        l--; r--;
        
        // 在差分数组中进行修改
        diff[l] += c;        // 左边界加c
        if (r + 1 < n) {     // 右边界后一个位置减c（如果不越界）
            diff[r + 1] -= c;
        }
    }
    
    // 重建数组
    rebuild_array();
    
    // 输出最终数组
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
