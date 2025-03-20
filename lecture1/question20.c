#include <stdio.h>

// 定义区间结构体
typedef struct {
    long long left;   // 左端点
    long long right;  // 右端点
} Interval;

// 数组大小设为100010，多开10个空间避免边界问题
Interval intervals[100010];
int n;  // 区间数量

// 快速排序用的比较函数
void swap(Interval *a, Interval *b) {
    Interval temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序实现
void quickSort(Interval arr[], int left, int right) {
    if (left >= right) return;
    
    int i = left - 1;
    int j = right + 1;
    Interval pivot = arr[(left + right) >> 1];
    
    while (i < j) {
        do i++; while (arr[i].left < pivot.left);
        do j--; while (arr[j].left > pivot.left);
        if (i < j) swap(&arr[i], &arr[j]);
    }
    
    quickSort(arr, left, j);
    quickSort(arr, j + 1, right);
}

int main() {
    // 读入区间数量
    scanf("%d", &n);
    
    // 读入所有区间
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &intervals[i].left, &intervals[i].right);
    }
    
    // 按左端点排序
    quickSort(intervals, 0, n - 1);
    
    int global_interval_count = 0;  // 合并后的区间数量
    long long current_right = -0x3f3f3f3f3f3f3f3f;  // 当前区间的右端点最大值
    
    // 遍历所有区间进行合并
    for (int i = 0; i < n; i++) {
        // 如果当前区间的左端点大于已有区间的最大右端点，说明需要开始一个新的区间
        if (intervals[i].left > current_right) {
            global_interval_count++;
            current_right = intervals[i].right;
        } else {
            // 否则更新当前区间的最大右端点
            if (intervals[i].right > current_right) {
                current_right = intervals[i].right;
            }
        }
    }
    
    // 输出结果
    printf("%d\n", global_interval_count);
    
    return 0;
}
