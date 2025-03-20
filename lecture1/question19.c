#include <stdio.h>

// 定义存储位置和值的结构体
typedef struct {
    long long pos;  // 位置
    int val;       // 值
} Point;

// 数组大小设为100010，多开10个空间避免边界问题
Point points[100010];     // 存储位置和值的数组
long long sum[100010];    // 前缀和数组
int n, m;                // n是操作次数，m是询问次数

// 快速排序用的比较函数
void swap(Point *a, Point *b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序实现
void quickSort(Point arr[], int left, int right) {
    if (left >= right) return;
    
    int i = left - 1;
    int j = right + 1;
    Point pivot = arr[(left + right) >> 1];
    
    while (i < j) {
        do i++; while (arr[i].pos < pivot.pos);
        do j--; while (arr[j].pos > pivot.pos);
        if (i < j) swap(&arr[i], &arr[j]);
    }
    
    quickSort(arr, left, j);
    quickSort(arr, j + 1, right);
}

// 二分查找，找到第一个大于等于target的位置
int lower_bound(Point arr[], int len, long long target) {
    int left = 0, right = len;  // 修改：right初始值改为len
    while (left < right) {
        int mid = (left + right) >> 1;
        if (arr[mid].pos >= target) right = mid;
        else left = mid + 1;
    }
    return left;
}

// 二分查找，找到第一个大于target的位置
int upper_bound(Point arr[], int len, long long target) {
    int left = 0, right = len;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (arr[mid].pos > target) right = mid;
        else left = mid + 1;
    }
    return left;
}

int main() {
    // 读入n, m
    scanf("%d %d", &n, &m);
    
    // 读入n次操作
    for (int i = 0; i < n; i++) {
        scanf("%lld %d", &points[i].pos, &points[i].val);
    }
    
    // 对位置进行排序
    quickSort(points, 0, n - 1);
    
    // 计算前缀和
    if (n > 0) {  // 修改：添加空数组检查
        sum[0] = points[0].val;
        for (int i = 1; i < n; i++) {
            sum[i] = sum[i-1] + points[i].val;
        }
    }
    
    // 处理m次询问
    while (m--) {
        long long l, r;
        scanf("%lld %lld", &l, &r);
        
        // 找到区间边界
        int left = lower_bound(points, n, l);
        int right = upper_bound(points, n, r);
        
        // 计算区间和
        long long result = 0;
        if (left < n && right > left) {  // 修改：添加left < n的检查
            result = sum[right - 1];
            if (left > 0) result -= sum[left - 1];
        }
        
        printf("%lld\n", result);
    }
    
    return 0;
}
